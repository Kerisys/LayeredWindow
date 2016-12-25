using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.Diagnostics;
using System.IO;

namespace AbyssRium_Macro_Csharp_
{
    public partial class ADB_Macro : Form
    {

        private OpenFileDialog OFD;
        private Process CMD;

        private StreamWriter Writer;
        private StreamReader Reader;
        private StreamReader Error;

        public ADB_Macro()
        {
            InitializeComponent();

            OFD = new OpenFileDialog();
            OFD.DefaultExt = "*.exe"; // 기본 확장자
            OFD.Filter = "실행 파일(*.exe)|*.exe"; // 확장자 필터
            //OFD.InitialDirectory = Application.StartupPath;   // 초기 디렉토리
            OFD.RestoreDirectory = false;              // 닫을 때 디렉토리 유지

            tPath.Text = "D:\\Program Files\\android-sdk_r24.4.1-windows\\platform-tools\\adb.exe";

            CMD = new Process();
            ProcessStartInfo info;
            info = new ProcessStartInfo("cmd.exe");

            info.WindowStyle = ProcessWindowStyle.Hidden;
            info.CreateNoWindow = true;

            info.UseShellExecute = false;    //운영체제 쉘 사용안함
            info.RedirectStandardInput = true;
            info.RedirectStandardOutput = true;
            info.RedirectStandardError = true;
            
            CMD.StartInfo = info;
            CMD.EnableRaisingEvents = false;
        }

        private void btnPath_Click(object sender, EventArgs e)
        {
            OFD.InitialDirectory = tPath.Text;
            if(OFD.ShowDialog() == DialogResult.OK)
            {
                tPath.Text = OFD.FileName;
            }
        }

        private void btnFindDevices_Click(object sender, EventArgs e)
        {
            string path, exe;
            int nameIndex = tPath.Text.LastIndexOf("\\")+1;
            path = tPath.Text.Substring(0, nameIndex);
            exe = tPath.Text.Substring(nameIndex);

            CMD.StartInfo.WorkingDirectory = path;
            CMD.Start();

            Writer = CMD.StandardInput;
            Writer.AutoFlush = true;
            Reader = CMD.StandardOutput;
            Error = CMD.StandardError;

            Writer.WriteLine("echo off");

            string command = exe + " get-serialno";
            Writer.WriteLine(command);
            Writer.Close();

            while (Reader.ReadLine() != command) ;


            string ReadText = Error.ReadToEnd();
            
            if (ReadText == string.Empty)
            {
                ReadText = Reader.ReadToEnd();
                cmbDevices.Items.Clear();
                string[] result = ReadText.Split(new string[] { Environment.NewLine }, StringSplitOptions.RemoveEmptyEntries);
                cmbDevices.Items.AddRange(result);
            }
            else
            {
                tResult.Text = ReadText;
            }

            CMD.WaitForExit();
            CMD.Close();
        }

        private void btnFindMonkey_Click(object sender, EventArgs e)
        {
            string path, exe, temp;
            int nameIndex = tPath.Text.LastIndexOf("\\") + 1;
            path = tPath.Text.Substring(0, nameIndex);
            exe = tPath.Text.Substring(nameIndex);

            if (cmbDevices.SelectedIndex >= 0) exe += " -s " + cmbDevices.SelectedItem.ToString();

            //temp = "temp";
            {
                int index = 0;
                string tmp = temp= "temp";
                while (File.Exists(tmp))
                {   
                    tmp = temp + index.ToString();
                    index++;
                }
                temp = tmp;
            }

            CMD.StartInfo.WorkingDirectory = path;
            CMD.Start();

            Writer = CMD.StandardInput;
            Writer.AutoFlush = true;
            Reader = CMD.StandardOutput;
            Error = CMD.StandardError;

            Writer.WriteLine("echo off");

            string command = exe + " shell ps > " + temp;
            Writer.WriteLine(command);
            Writer.Close();

            tResult.Text = Reader.ReadToEnd() + Error.ReadToEnd();

            CMD.WaitForExit();
            CMD.Close();

            temp = path + temp;
            using (StreamReader reader = new StreamReader(temp))
            {
                string readData = string.Empty;

                cmbMonkey.Items.Clear();
                while (!reader.EndOfStream)
                {
                    readData = reader.ReadLine();
                    if (readData.Contains("monkey"))
                    {
                        string[] result = readData.Split(new string[] { " ", "\t"}, StringSplitOptions.RemoveEmptyEntries);
                        cmbMonkey.Items.Add(result[1]);
                        tResult.Text += readData + Environment.NewLine;
                    }
                    
                }
            }
            File.Delete(temp);

            btnKillMonkey.Enabled = cmbMonkey.Items.Count > 0;
        }

        private void btnKillMonkey_Click(object sender, EventArgs e)
        {
            if (cmbMonkey.Items.Count < 1) return;
            //if (cmbMonkey.SelectedIndex < 0) return;
            
            string path, exe, PID;
            int nameIndex = tPath.Text.LastIndexOf("\\") + 1;
            path = tPath.Text.Substring(0, nameIndex);
            exe = tPath.Text.Substring(nameIndex);

            if (cmbDevices.SelectedIndex >= 0) exe += " -s " + cmbDevices.SelectedItem.ToString();
            
            CMD.StartInfo.WorkingDirectory = path;
            CMD.Start();

            Writer = CMD.StandardInput;
            Writer.AutoFlush = true;
            Reader = CMD.StandardOutput;
            Error = CMD.StandardError;
            
            foreach (Object item in cmbMonkey.Items)
            {
                PID = item.ToString();
                Writer.WriteLine(exe + " shell kill " + PID);
            }
            Writer.Close();
            tResult.Text = Reader.ReadToEnd();
            CMD.WaitForExit();
            CMD.Close();

            cmbMonkey.Items.Remove(cmbMonkey.SelectedItem);
            btnKillMonkey.Enabled = cmbMonkey.Items.Count > 0;
        }

        private void btnStart_Click(object sender, EventArgs e)
        {
            string path, exe;
            int nameIndex = tPath.Text.LastIndexOf("\\") + 1;
            path = tPath.Text.Substring(0, nameIndex);
            exe = tPath.Text.Substring(nameIndex);

            if (cmbDevices.SelectedIndex >= 0) exe += " -s " + cmbDevices.SelectedItem.ToString();

            CMD.StartInfo.WorkingDirectory = path;
            CMD.Start();

            Writer = CMD.StandardInput;
            Writer.AutoFlush = true;
            Reader = CMD.StandardOutput;
            Error = CMD.StandardError;

            Task.Factory.StartNew(() => {
                string command = exe + " shell monkey -f /sdcard/monkey.txt 60000";
                Writer.WriteLine(command);
                tResult.Text = Reader.ReadToEnd() + Error.ReadToEnd();

                CMD.WaitForExit();
                CMD.Close();
            });

            //string command = exe + " shell monkey -f /sdcard/monkey.txt 60000";
            //Task task =  Writer.WriteLineAsync(command);
            //task.Start();
            //Writer.WriteLine(@"^C");
            //task.Wait();
            //Writer.Close();

            //tResult.Text = Reader.ReadToEnd() + Error.ReadToEnd() ;

            //CMD.WaitForExit();
            //CMD.Close();

            //btnFindMonkey_Click(sender, e);
        }
    }
}
