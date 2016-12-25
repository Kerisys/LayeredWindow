namespace AbyssRium_Macro_Csharp_
{
    partial class ADB_Macro
    {
        /// <summary>
        /// 필수 디자이너 변수입니다.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// 사용 중인 모든 리소스를 정리합니다.
        /// </summary>
        /// <param name="disposing">관리되는 리소스를 삭제해야 하면 true이고, 그렇지 않으면 false입니다.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows Form 디자이너에서 생성한 코드

        /// <summary>
        /// 디자이너 지원에 필요한 메서드입니다. 
        /// 이 메서드의 내용을 코드 편집기로 수정하지 마세요.
        /// </summary>
        private void InitializeComponent()
        {
            this.label1 = new System.Windows.Forms.Label();
            this.tPath = new System.Windows.Forms.TextBox();
            this.btnPath = new System.Windows.Forms.Button();
            this.btnFindDevices = new System.Windows.Forms.Button();
            this.cmbDevices = new System.Windows.Forms.ComboBox();
            this.tResult = new System.Windows.Forms.TextBox();
            this.btnFindMonkey = new System.Windows.Forms.Button();
            this.cmbMonkey = new System.Windows.Forms.ComboBox();
            this.btnKillMonkey = new System.Windows.Forms.Button();
            this.btnStart = new System.Windows.Forms.Button();
            this.SuspendLayout();
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Location = new System.Drawing.Point(13, 13);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(65, 12);
            this.label1.TabIndex = 0;
            this.label1.Text = "ADB 경로 :";
            // 
            // tPath
            // 
            this.tPath.Location = new System.Drawing.Point(84, 10);
            this.tPath.Name = "tPath";
            this.tPath.Size = new System.Drawing.Size(303, 21);
            this.tPath.TabIndex = 1;
            this.tPath.Text = "adb.exe";
            // 
            // btnPath
            // 
            this.btnPath.Location = new System.Drawing.Point(393, 8);
            this.btnPath.Name = "btnPath";
            this.btnPath.Size = new System.Drawing.Size(75, 23);
            this.btnPath.TabIndex = 2;
            this.btnPath.Text = "찾아보기";
            this.btnPath.UseVisualStyleBackColor = true;
            this.btnPath.Click += new System.EventHandler(this.btnPath_Click);
            // 
            // btnFindDevices
            // 
            this.btnFindDevices.Location = new System.Drawing.Point(15, 37);
            this.btnFindDevices.Name = "btnFindDevices";
            this.btnFindDevices.Size = new System.Drawing.Size(104, 23);
            this.btnFindDevices.TabIndex = 3;
            this.btnFindDevices.Text = "디바이스 찾기";
            this.btnFindDevices.UseVisualStyleBackColor = true;
            this.btnFindDevices.Click += new System.EventHandler(this.btnFindDevices_Click);
            // 
            // cmbDevices
            // 
            this.cmbDevices.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.cmbDevices.Location = new System.Drawing.Point(125, 40);
            this.cmbDevices.Name = "cmbDevices";
            this.cmbDevices.Size = new System.Drawing.Size(183, 20);
            this.cmbDevices.TabIndex = 4;
            // 
            // tResult
            // 
            this.tResult.Location = new System.Drawing.Point(15, 247);
            this.tResult.Multiline = true;
            this.tResult.Name = "tResult";
            this.tResult.ScrollBars = System.Windows.Forms.ScrollBars.Both;
            this.tResult.Size = new System.Drawing.Size(453, 183);
            this.tResult.TabIndex = 5;
            this.tResult.WordWrap = false;
            // 
            // btnFindMonkey
            // 
            this.btnFindMonkey.Location = new System.Drawing.Point(15, 66);
            this.btnFindMonkey.Name = "btnFindMonkey";
            this.btnFindMonkey.Size = new System.Drawing.Size(104, 23);
            this.btnFindMonkey.TabIndex = 6;
            this.btnFindMonkey.Text = "Monkey 찾기";
            this.btnFindMonkey.UseVisualStyleBackColor = true;
            this.btnFindMonkey.Click += new System.EventHandler(this.btnFindMonkey_Click);
            // 
            // cmbMonkey
            // 
            this.cmbMonkey.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.cmbMonkey.FormattingEnabled = true;
            this.cmbMonkey.Location = new System.Drawing.Point(125, 68);
            this.cmbMonkey.Name = "cmbMonkey";
            this.cmbMonkey.Size = new System.Drawing.Size(183, 20);
            this.cmbMonkey.TabIndex = 7;
            // 
            // btnKillMonkey
            // 
            this.btnKillMonkey.Enabled = false;
            this.btnKillMonkey.Location = new System.Drawing.Point(314, 66);
            this.btnKillMonkey.Name = "btnKillMonkey";
            this.btnKillMonkey.Size = new System.Drawing.Size(89, 23);
            this.btnKillMonkey.TabIndex = 8;
            this.btnKillMonkey.Text = "Kill Monkey";
            this.btnKillMonkey.UseVisualStyleBackColor = true;
            this.btnKillMonkey.Click += new System.EventHandler(this.btnKillMonkey_Click);
            // 
            // btnStart
            // 
            this.btnStart.Location = new System.Drawing.Point(314, 38);
            this.btnStart.Name = "btnStart";
            this.btnStart.Size = new System.Drawing.Size(89, 23);
            this.btnStart.TabIndex = 9;
            this.btnStart.Text = "Start Monkey";
            this.btnStart.UseVisualStyleBackColor = true;
            this.btnStart.Click += new System.EventHandler(this.btnStart_Click);
            // 
            // ADB_Macro
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(7F, 12F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(482, 492);
            this.Controls.Add(this.btnStart);
            this.Controls.Add(this.btnKillMonkey);
            this.Controls.Add(this.cmbMonkey);
            this.Controls.Add(this.btnFindMonkey);
            this.Controls.Add(this.tResult);
            this.Controls.Add(this.cmbDevices);
            this.Controls.Add(this.btnFindDevices);
            this.Controls.Add(this.btnPath);
            this.Controls.Add(this.tPath);
            this.Controls.Add(this.label1);
            this.Name = "ADB_Macro";
            this.Text = "어비스리움 매크로";
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.TextBox tPath;
        private System.Windows.Forms.Button btnPath;
        private System.Windows.Forms.Button btnFindDevices;
        private System.Windows.Forms.ComboBox cmbDevices;
        private System.Windows.Forms.TextBox tResult;
        private System.Windows.Forms.Button btnFindMonkey;
        private System.Windows.Forms.ComboBox cmbMonkey;
        private System.Windows.Forms.Button btnKillMonkey;
        private System.Windows.Forms.Button btnStart;
    }
}

