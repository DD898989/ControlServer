using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using Enum_;

namespace UI
{
    class Server_Module_B
    {
        static string _sLog = new System.Diagnostics.StackTrace(true).GetFrame(0).GetFileName().Substring(new System.Diagnostics.StackTrace(true).GetFrame(0).GetFileName().LastIndexOf('\\') + 1) + ":  ";

        [System.Runtime.CompilerServices.MethodImpl(System.Runtime.CompilerServices.MethodImplOptions.Synchronized)]
        public static int RecieveCommand(int command)
        {
            switch (command)
            {
                case (int)CS.CS_Module_B_Cmd_1:
                    p.log(_sLog + "Cmd_1");
                    System.Threading.Thread.Sleep(1000);
                    return (int)CS.CS_OK;

                case (int)CS.CS_Module_B_Cmd_2:
                    p.log(_sLog + "Cmd_2");
                    System.Threading.Thread.Sleep(1000);
                    return (int)CS.CS_OK;

                case (int)CS.CS_Module_B_Cmd_3:
                    p.log(_sLog + "Cmd_3");
                    System.Threading.Thread.Sleep(1000);
                    return (int)CS.CS_OK;

                case (int)CS.CS_Module_B_Cmd_4:
                    p.log(_sLog + "Cmd_4");
                    System.Threading.Thread.Sleep(1000);
                    return (int)CS.CS_OK;

                case (int)CS.CS_Module_B_Cmd_5:
                    p.log(_sLog + "Cmd_5");
                    System.Threading.Thread.Sleep(1000);
                    return (int)CS.CS_OK;

                case (int)CS.CS_Module_B_Cmd_6:
                    p.log(_sLog + "Cmd_6");
                    System.Threading.Thread.Sleep(1000);
                    return (int)CS.CS_OK;

                default:
                    return 0;  //wrong command
            }
        }
    }
}
