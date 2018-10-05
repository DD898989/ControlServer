using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;
using System.Runtime.InteropServices;
using System.IO;
using Enum_;
using System.Threading;
using System.Diagnostics;

namespace UI
{
    public partial class Form1 : Form
    {
        public Form1()
        {
            InitializeComponent();
        }

        delegate void StringArgReturningVoidDelegate(string text);
        public void SetText(string text)
        {
            if (this.textBox1.InvokeRequired)
            {
                StringArgReturningVoidDelegate d = new StringArgReturningVoidDelegate(SetText);
                this.Invoke(d, new object[] { text });
            }
            else
            {
                this.textBox1.Items.Add(text);
            }
        }

        private void button5_Click(object sender, EventArgs e)
        {
            p.log("module a seq 1 button clicked");
            p.WP(IP.Sys_M_Module_A_Simple_Cmds, (int)Enum_.cas.Seq_Start);
        }

        private void button2_Click(object sender, EventArgs e)
        {
            p.log("module a seq 2 button clicked");
            p.WP(IP.Sys_M_Module_A_Complex_Cmds, (int)Enum_.cas.Seq_Start);
        }

        private void button3_Click(object sender, EventArgs e)
        {
            p.log("module b seq 1 button clicked");
            p.WP(IP.Sys_M_Module_B_Simple_Cmds, (int)Enum_.cas.Seq_Start);
        }

        private void button1_Click(object sender, EventArgs e)
        {
            p.log("module b seq 2 button clicked");
            p.WP(IP.Sys_M_Module_B_Complex_Cmds, (int)Enum_.cas.Seq_Start);
        }
    }
}
