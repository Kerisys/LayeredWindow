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
using System.Threading;

namespace ScreenCapture
{
    public partial class ScreenCapture : Form
    {
        private bool isRun;

        private Process CMD;


        public ScreenCapture()
        {
            InitializeComponent();

            CMD = new Process();
            ProcessStartInfo info;
            info = new ProcessStartInfo("cmd.exe");

            info.WindowStyle = ProcessWindowStyle.Hidden;
            info.CreateNoWindow = true;

            info.UseShellExecute = false;    //운영체제 쉘 사용안함
            info.WorkingDirectory = @"D:\Program Files\android-sdk_r24.4.1-windows\platform-tools\";
            info.RedirectStandardInput = true;
            info.RedirectStandardOutput = true;

            CMD.StartInfo = info;
            CMD.EnableRaisingEvents = false;
     
        }

        ~ScreenCapture()
        {
            captureThread.Join();
        }

        private Thread captureThread;

        public void CaptureRun()
        {
            
            while (isRun)
            {
                StreamWriter Writer;

                CMD.Start();
                Writer = CMD.StandardInput;
                Writer.AutoFlush = true;


                if (picture.Image != null) picture.Image.Dispose();

                Writer.WriteLine("adb shell screencap -p /sdcard/screencap.png");
                Writer.WriteLine("adb pull /sdcard/screencap.png");
                Writer.WriteLine("adb rm /sdcard/screencap.png");
                Writer.Close();

                CMD.WaitForExit();
                CMD.Close();
                if (File.Exists(@"D:\Program Files\android-sdk_r24.4.1-windows\platform-tools\screencap.png"))
                {
                    using (Image img = Image.FromFile(@"D:\Program Files\android-sdk_r24.4.1-windows\platform-tools\screencap.png"))
                    {
                        picture.Image = (Image)img.Clone();
                        picture.Update();
                    }
                }
                
                Thread.Sleep(10);
            }
        }

        private void button1_Click(object sender, EventArgs e)
        {
            if (captureThread == null)
            {
                captureThread = new Thread(CaptureRun);
            }
            isRun = true;
            captureThread.Start();
        }

        private void button2_Click(object sender, EventArgs e)
        {
            isRun = false;
            captureThread.Join();
        }
    }
}
