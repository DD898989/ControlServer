using System;
using System.Collections.Generic;
using System.Linq;
using System.Windows.Forms;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Text;
using System.Runtime.InteropServices;
using System.IO;
using Enum_;
using System.Threading;
using System.Diagnostics;
using System.IO.MemoryMappedFiles;
using System.IO.Pipes;

namespace UI
{
    static class p  //program
    {
        // constant
        const int INT_SIZE = 4;
        const int LOG_TIME_STRING_LENGTH = 12;  //ex:  "mm:ss.sss" length = 9

        //memory pool
        static private object _lockMemoryPool = new object();
        static private MemoryMappedViewStream _mmfvs;
        static private byte[] _intBuf = new byte[(int)IP.IntegerDataPoolMaxBoundary * INT_SIZE];

        //static pool
        static private object _lockStaticPool = new object();
        static private FileInfo _fi_SYS_handle;
        static private FileInfo _fi_UI_handle;
        const string ROOT_PATH = @"D:\ControlServer\";
        const string UI_PATH = ROOT_PATH + "Query_Static_Pool_UI_hanle";
        const string SYS_PATH = ROOT_PATH + "Query_Static_Pool_SYS_hanle";
        const string STATIC_POOL_PATH = ROOT_PATH + "Static_Pool";

        //control server
        static object[] ControlServerLock = new object[(int)IP.ControlServer_End];
        static Func<int, int>[] ServerModuleDotRecieveCommand = new Func<int, int>[(int)IP.ControlServer_End];
        static public void CheckControlServerCommand(
            IP CS_XXX,
            IP CS_XXX_AutoUnlock,
            object ServerXXXLock,
            Func<int, int> ServerModuleDotRecieveCommand
            )
        {
            CS Cmd_ = (CS)p.RP(CS_XXX);
            if (Cmd_ > CS.CS_Basic_State_End)
            {
                CS Cmd = Cmd_;
                p.log("Server: " + CS_XXX + " command:  " + Cmd + "   Received");
                p.WP(CS_XXX, (int)CS.CS_Lock);
                int auto_unlock = p.RP(CS_XXX_AutoUnlock);
                p.WP(CS_XXX_AutoUnlock, 0); //default setting: do not auto unlock

                new System.Threading.Thread(() =>
                {
                    lock (ServerXXXLock)// make sure only one cmd for a single module at a time
                    {
                        p.log("Server: " + CS_XXX + " command:  " + Cmd + "   Ready to send");

                        CS Result = (CS)ServerModuleDotRecieveCommand((int)Cmd);
                        if (Result == CS.CS_NG)
                        {
                            p.log("Server: " + CS_XXX + " command:  " + Cmd + "   Seq_NNNNNNNNGGGGGGGG");
                        }
                        else if (Result == CS.CS_OK)
                        {
                            p.log("Server: " + CS_XXX + " command:  " + Cmd + "   OK");
                        }

                        p.WP(CS_XXX, (int)Result);

                        if (auto_unlock == 1)
                        {
                            p.log("Auto Unlock!");
                            p.WP(CS_XXX, (int)CS.CS_Unlock);
                        }
                    }
                }).Start();
            }
        }

        //UI log
        public static void log(string s)  
        {
            while (true)
            {
                Console.WriteLine(DateTime.Now.ToString("HH:mm:ss.fff") + " [U I] " + s);
                    break;
            }
        }

        //write memory pool
        static public void WP(IP location, int nWriteData)
        {
            lock (_lockMemoryPool)
            {
                while (true)
                {
                    _mmfvs.Seek((int)location * INT_SIZE, SeekOrigin.Begin);
                    _mmfvs.Write(BitConverter.GetBytes(nWriteData), 0, INT_SIZE);
                    return;
                }
            }
        }

        //read memory pool
        static public int RP(IP location)
        {
            lock (_lockMemoryPool) 
            {
                _mmfvs.Seek((int)location * INT_SIZE, SeekOrigin.Begin);
                _mmfvs.Read(_intBuf, 0, INT_SIZE);
                return BitConverter.ToInt32(_intBuf, 0);
            }
        }

        //write static pool
        static public void WSP(IP location, int nWriteData) 
        {
            int nLoc = INT_SIZE * (int)location;
            bool bDoneWrite = false;

            lock (_lockStaticPool)
            {
                while (true)
                {
                    _fi_UI_handle.Attributes = _fi_UI_handle.Attributes & ~FileAttributes.Hidden;

                    _fi_SYS_handle.Refresh();
                    if (_fi_SYS_handle.Attributes.HasFlag(FileAttributes.Hidden)) 
                    {
                        using (BinaryWriter writer = new BinaryWriter(new FileStream(STATIC_POOL_PATH, FileMode.Open, FileAccess.Write, FileShare.ReadWrite)))
                        {
                            writer.Seek(nLoc, SeekOrigin.Begin); 
                            writer.Write(nWriteData);
                        }
                        bDoneWrite = true;
                    }
                    File.SetAttributes(UI_PATH, File.GetAttributes(UI_PATH) | FileAttributes.Hidden);
                    if (bDoneWrite)
                        break;
                }
            }
        }

        //read static pool
        static public int RSP(IP location)
        {
            byte[] buf = new byte[INT_SIZE];
            int nLoc = INT_SIZE * (int)location;
            using (BinaryReader reader = new BinaryReader(new FileStream(STATIC_POOL_PATH, FileMode.Open, FileAccess.Read, FileShare.ReadWrite)))
            {
                reader.BaseStream.Seek(nLoc, SeekOrigin.Begin);
                reader.Read(buf, 0, INT_SIZE);
            }
            return BitConverter.ToInt32(buf, 0);
        }

        [STAThread]
        static void Main(string[] arg)
        {
            #region UI start
            Console.WriteLine(DateTime.Now.ToString("HH:mm:ss.fff  ") + "UI Main()");
            if (arg.Length == 0) //UI is start project
            {
                ProcessStartInfo startInfo = new ProcessStartInfo(ROOT_PATH + "SYS.exe");
                startInfo.WorkingDirectory = ROOT_PATH; startInfo.Arguments = "UI call SYS";
                Console.WriteLine(DateTime.Now.ToString("HH:mm:ss.fff  ") + "UI call SYS");
                Process.Start(startInfo);
            }
            else                 //UI is called by SYS
            {
                Console.Write(DateTime.Now.ToString("HH:mm:ss.fff  ") + "Main arg:  ");
                for (int i = 0; i < arg.Length; i++)
                    Console.Write(arg[i] + " ");
                Console.WriteLine("");
            }
            #endregion

            #region static pool init
            _fi_UI_handle = new FileInfo(UI_PATH);
            _fi_SYS_handle = new FileInfo(SYS_PATH);
            #endregion

            #region memory pool init
            while (true)
            {
                try
                {
                    _mmfvs = MemoryMappedFile.OpenExisting("MySharedMemory").CreateViewStream();
                    Console.WriteLine(DateTime.Now.ToString("HH:mm:ss.fff  ") + "Successed connecting to Shared Memory");
                    break;
                }
                catch
                {
                }
            }
            #endregion

            #region control server init
            //-------------------------------
            ServerModuleDotRecieveCommand[(int)IP.CS_Module_A] = Server_Module_A.RecieveCommand;
            ServerModuleDotRecieveCommand[(int)IP.CS_Module_B] = Server_Module_B.RecieveCommand;
            //-------------------------------
            for (int i = 0; i < ControlServerLock.Length; i++) ControlServerLock[i] = new object();
            Console.WriteLine(DateTime.Now.ToString("HH:mm:ss.fff  ") + "Finish Init Control Server");
            new System.Threading.Thread(() =>
            {
                while (true)
                {
                    using (NamedPipeServerStream pipeStream = new NamedPipeServerStream("ControlServerCmdPipe"))
                    {
                        pipeStream.WaitForConnection();
                        System.IO.BinaryReader br = new BinaryReader(pipeStream);
                        int tmp = br.ReadInt16();

                        CheckControlServerCommand(        // always loop check whether receive control server command(ModuleA、ModuleB、...)
                        (IP)tmp,
                        (IP)tmp + 1,
                        ControlServerLock[tmp],
                        ServerModuleDotRecieveCommand[tmp]
                        );
                    }
                }
            }).Start();
            #endregion

            #region init form
            Form1 myForm = new Form1();
            new System.Threading.Thread(() =>
            {
                while (true)
                {
                    using (NamedPipeServerStream pipeStream = new NamedPipeServerStream("mypipe"))
                    {
                        pipeStream.WaitForConnection();
                        StreamReader sr = new StreamReader(pipeStream);
                        string tmp;
                        while ((tmp = sr.ReadLine()) != null)
                        {
                            if (!tmp.Contains("MSG2USER"))
                                Console.WriteLine(tmp);
                            else
                            {
                                string tmp_ = tmp.Replace("MSG2USER", "");
                                Console.WriteLine(tmp_);
                                myForm.SetText(tmp_);

                            }
                        }
                    }
                }
            }).Start();
            Application.EnableVisualStyles();
            //Application.SetCompatibleTextRenderingDefault(false);
            Application.Run(myForm);
            //Application.Run(new Form1());
            #endregion
        }
    }
}
