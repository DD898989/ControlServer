using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.IO;
using Enum_;

namespace Enum_H_Factory
{
    class Program
    {
        static void Main(string[] args)
        {
            string sPath_CS = System.IO.Path.GetFullPath(System.IO.Path.Combine(Environment.CurrentDirectory.ToString(), @"..\..\..") + @"\Enum\Enum.cs");
            string sAllText = "";
            if (File.Exists(sPath_CS))
            {
                sAllText += "\n\n\n\n#ifndef __Enum_H__\n#define __Enum_H__ 1\n#include \"..\\Enum\\Enum.cs\"\n\n\n\n\n\n\n";

                //EnumForEach<Enum_.cas.Method>(ref sAllText);
                //EnumForEach<Enum_.cas.Module_ABase>(ref sAllText);
                //EnumForEach<Enum_.cas.Module_A.Cmd_1ThenCmd_2>(ref sAllText);
                //EnumForEach<Enum_.cas.Module_A.Complex_Cmds>(ref sAllText);
                //EnumForEach<Enum_.cas.Module_BBase>(ref sAllText);
                //EnumForEach<Enum_.cas.Module_B.Cmd_1ThenCmd_2>(ref sAllText);
                //EnumForEach<Enum_.cas.Module_B.Complex_Cmds>(ref sAllText);
                EnumForEach<cas>(ref sAllText);
                EnumForEach<CS>(ref sAllText);
                EnumForEach<IP>(ref sAllText);

                sAllText += "#endif";
            }

            string sDir_Header = System.IO.Path.GetFullPath(System.IO.Path.Combine(Environment.CurrentDirectory.ToString(), @"..\..\.."));
            string sPath_Header = System.IO.Path.GetFullPath(System.IO.Path.Combine(Environment.CurrentDirectory.ToString(), @"..\..\..") + @"\SYS\Enum.h");

            if (Directory.Exists(sDir_Header))
            {
                File.WriteAllText(sPath_Header, sAllText);
            }
        }

        public static void EnumForEach<EN>(ref string sAllText)
        {
            if (!typeof(EN).IsEnum)
                throw new ArgumentException("Generic argument type must be an Enum.");

            string sTemp = "";
            bool bFirstTime = true;

            foreach (EN en in Enum.GetValues(typeof(EN)))
            {
                if (bFirstTime)
                {
                    sAllText += "inline const char* p(";
                    sAllText += "TempTextForReplace";
                    sAllText += " v)\n{\n    switch (v)\n    {\n";
                }
                sTemp = en.GetType().Namespace + "::" + en.GetType().Name + "::" + en.ToString();
                sTemp = sTemp.Replace(".", "::");
                sTemp = sTemp.Replace("Enum_::", "");
                sAllText += "        case " + sTemp + ":  " + "return \"" + sTemp + "\";\n";

                bFirstTime = false;
            }

            if (bFirstTime == false)
            { 
                sAllText = sAllText.Replace("TempTextForReplace", sTemp.Substring(0, sTemp.LastIndexOf("::")));
                sAllText += "\t\tdefault:\n\t\t\treturn \"ERROR: WRONG CASE IN Enum.h\";\n";
                sAllText += "    }\n}\n\n";
            }
        }
    }
}
