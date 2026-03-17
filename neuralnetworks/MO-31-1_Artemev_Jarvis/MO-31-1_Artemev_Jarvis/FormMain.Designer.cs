namespace MO_31_1_Artemev_Jarvis
{
    partial class FormMain
    {
        /// <summary>
        /// Обязательная переменная конструктора.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// Освободить все используемые ресурсы.
        /// </summary>
        /// <param name="disposing">истинно, если управляемый ресурс должен быть удален; иначе ложно.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Код, автоматически созданный конструктором форм Windows

        /// <summary>
        /// Требуемый метод для поддержки конструктора — не изменяйте 
        /// содержимое этого метода с помощью редактора кода.
        /// </summary>
        private void InitializeComponent()
        {
            this.components = new System.ComponentModel.Container();
            System.Windows.Forms.DataVisualization.Charting.ChartArea chartArea1 = new System.Windows.Forms.DataVisualization.Charting.ChartArea();
            System.Windows.Forms.DataVisualization.Charting.Legend legend1 = new System.Windows.Forms.DataVisualization.Charting.Legend();
            System.Windows.Forms.DataVisualization.Charting.Series series1 = new System.Windows.Forms.DataVisualization.Charting.Series();
            System.Windows.Forms.DataVisualization.Charting.Series series2 = new System.Windows.Forms.DataVisualization.Charting.Series();
            this.button1 = new System.Windows.Forms.Button();
            this.button2 = new System.Windows.Forms.Button();
            this.button3 = new System.Windows.Forms.Button();
            this.button4 = new System.Windows.Forms.Button();
            this.button5 = new System.Windows.Forms.Button();
            this.button6 = new System.Windows.Forms.Button();
            this.button7 = new System.Windows.Forms.Button();
            this.button8 = new System.Windows.Forms.Button();
            this.button9 = new System.Windows.Forms.Button();
            this.button10 = new System.Windows.Forms.Button();
            this.button11 = new System.Windows.Forms.Button();
            this.button12 = new System.Windows.Forms.Button();
            this.button13 = new System.Windows.Forms.Button();
            this.button14 = new System.Windows.Forms.Button();
            this.button15 = new System.Windows.Forms.Button();
            this.button_train = new System.Windows.Forms.Button();
            this.button_recognize = new System.Windows.Forms.Button();
            this.chart_Eavr = new System.Windows.Forms.DataVisualization.Charting.Chart();
            this.label_output = new System.Windows.Forms.Label();
            this.label_probability = new System.Windows.Forms.Label();
            this.button_saveTrain = new System.Windows.Forms.Button();
            this.button_saveTest = new System.Windows.Forms.Button();
            this.NecessaryOutput = new System.Windows.Forms.TextBox();
            this.contextMenuStrip1 = new System.Windows.Forms.ContextMenuStrip(this.components);
            this.button_test = new System.Windows.Forms.Button();
            this.button_kill = new System.Windows.Forms.Button();
            ((System.ComponentModel.ISupportInitialize)(this.chart_Eavr)).BeginInit();
            this.SuspendLayout();
            // 
            // button1
            // 
            this.button1.BackColor = System.Drawing.Color.White;
            this.button1.FlatStyle = System.Windows.Forms.FlatStyle.Flat;
            this.button1.Location = new System.Drawing.Point(38, 32);
            this.button1.Name = "button1";
            this.button1.Size = new System.Drawing.Size(120, 120);
            this.button1.TabIndex = 0;
            this.button1.UseVisualStyleBackColor = false;
            this.button1.Click += new System.EventHandler(this.OnPixelButtonClick);
            // 
            // button2
            // 
            this.button2.BackColor = System.Drawing.Color.White;
            this.button2.FlatStyle = System.Windows.Forms.FlatStyle.Flat;
            this.button2.Location = new System.Drawing.Point(164, 32);
            this.button2.Name = "button2";
            this.button2.Size = new System.Drawing.Size(120, 120);
            this.button2.TabIndex = 1;
            this.button2.UseVisualStyleBackColor = false;
            this.button2.Click += new System.EventHandler(this.OnPixelButtonClick);
            // 
            // button3
            // 
            this.button3.BackColor = System.Drawing.Color.White;
            this.button3.FlatStyle = System.Windows.Forms.FlatStyle.Flat;
            this.button3.Location = new System.Drawing.Point(290, 32);
            this.button3.Name = "button3";
            this.button3.Size = new System.Drawing.Size(120, 120);
            this.button3.TabIndex = 2;
            this.button3.UseVisualStyleBackColor = false;
            this.button3.Click += new System.EventHandler(this.OnPixelButtonClick);
            // 
            // button4
            // 
            this.button4.BackColor = System.Drawing.Color.White;
            this.button4.FlatStyle = System.Windows.Forms.FlatStyle.Flat;
            this.button4.Location = new System.Drawing.Point(38, 158);
            this.button4.Name = "button4";
            this.button4.Size = new System.Drawing.Size(120, 120);
            this.button4.TabIndex = 3;
            this.button4.UseVisualStyleBackColor = false;
            this.button4.Click += new System.EventHandler(this.OnPixelButtonClick);
            // 
            // button5
            // 
            this.button5.BackColor = System.Drawing.Color.White;
            this.button5.FlatStyle = System.Windows.Forms.FlatStyle.Flat;
            this.button5.Location = new System.Drawing.Point(164, 158);
            this.button5.Name = "button5";
            this.button5.Size = new System.Drawing.Size(120, 120);
            this.button5.TabIndex = 4;
            this.button5.UseVisualStyleBackColor = false;
            this.button5.Click += new System.EventHandler(this.OnPixelButtonClick);
            // 
            // button6
            // 
            this.button6.BackColor = System.Drawing.Color.White;
            this.button6.FlatStyle = System.Windows.Forms.FlatStyle.Flat;
            this.button6.Location = new System.Drawing.Point(290, 158);
            this.button6.Name = "button6";
            this.button6.Size = new System.Drawing.Size(120, 120);
            this.button6.TabIndex = 5;
            this.button6.UseVisualStyleBackColor = false;
            this.button6.Click += new System.EventHandler(this.OnPixelButtonClick);
            // 
            // button7
            // 
            this.button7.BackColor = System.Drawing.Color.White;
            this.button7.FlatStyle = System.Windows.Forms.FlatStyle.Flat;
            this.button7.Location = new System.Drawing.Point(38, 284);
            this.button7.Name = "button7";
            this.button7.Size = new System.Drawing.Size(120, 120);
            this.button7.TabIndex = 6;
            this.button7.UseVisualStyleBackColor = false;
            this.button7.Click += new System.EventHandler(this.OnPixelButtonClick);
            // 
            // button8
            // 
            this.button8.BackColor = System.Drawing.Color.White;
            this.button8.FlatStyle = System.Windows.Forms.FlatStyle.Flat;
            this.button8.Location = new System.Drawing.Point(164, 284);
            this.button8.Name = "button8";
            this.button8.Size = new System.Drawing.Size(120, 120);
            this.button8.TabIndex = 7;
            this.button8.UseVisualStyleBackColor = false;
            this.button8.Click += new System.EventHandler(this.OnPixelButtonClick);
            // 
            // button9
            // 
            this.button9.BackColor = System.Drawing.Color.White;
            this.button9.FlatStyle = System.Windows.Forms.FlatStyle.Flat;
            this.button9.Location = new System.Drawing.Point(290, 284);
            this.button9.Name = "button9";
            this.button9.Size = new System.Drawing.Size(120, 120);
            this.button9.TabIndex = 8;
            this.button9.UseVisualStyleBackColor = false;
            this.button9.Click += new System.EventHandler(this.OnPixelButtonClick);
            // 
            // button10
            // 
            this.button10.BackColor = System.Drawing.Color.White;
            this.button10.FlatStyle = System.Windows.Forms.FlatStyle.Flat;
            this.button10.Location = new System.Drawing.Point(38, 410);
            this.button10.Name = "button10";
            this.button10.Size = new System.Drawing.Size(120, 120);
            this.button10.TabIndex = 9;
            this.button10.UseVisualStyleBackColor = false;
            this.button10.Click += new System.EventHandler(this.OnPixelButtonClick);
            // 
            // button11
            // 
            this.button11.BackColor = System.Drawing.Color.White;
            this.button11.FlatStyle = System.Windows.Forms.FlatStyle.Flat;
            this.button11.Location = new System.Drawing.Point(164, 410);
            this.button11.Name = "button11";
            this.button11.Size = new System.Drawing.Size(120, 120);
            this.button11.TabIndex = 10;
            this.button11.UseVisualStyleBackColor = false;
            this.button11.Click += new System.EventHandler(this.OnPixelButtonClick);
            // 
            // button12
            // 
            this.button12.BackColor = System.Drawing.Color.White;
            this.button12.FlatStyle = System.Windows.Forms.FlatStyle.Flat;
            this.button12.Location = new System.Drawing.Point(290, 410);
            this.button12.Name = "button12";
            this.button12.Size = new System.Drawing.Size(120, 120);
            this.button12.TabIndex = 11;
            this.button12.UseVisualStyleBackColor = false;
            this.button12.Click += new System.EventHandler(this.OnPixelButtonClick);
            // 
            // button13
            // 
            this.button13.BackColor = System.Drawing.Color.White;
            this.button13.FlatStyle = System.Windows.Forms.FlatStyle.Flat;
            this.button13.Location = new System.Drawing.Point(38, 536);
            this.button13.Name = "button13";
            this.button13.Size = new System.Drawing.Size(120, 120);
            this.button13.TabIndex = 12;
            this.button13.UseVisualStyleBackColor = false;
            this.button13.Click += new System.EventHandler(this.OnPixelButtonClick);
            // 
            // button14
            // 
            this.button14.BackColor = System.Drawing.Color.White;
            this.button14.FlatStyle = System.Windows.Forms.FlatStyle.Flat;
            this.button14.Location = new System.Drawing.Point(164, 536);
            this.button14.Name = "button14";
            this.button14.Size = new System.Drawing.Size(120, 120);
            this.button14.TabIndex = 13;
            this.button14.UseVisualStyleBackColor = false;
            this.button14.Click += new System.EventHandler(this.OnPixelButtonClick);
            // 
            // button15
            // 
            this.button15.BackColor = System.Drawing.Color.White;
            this.button15.FlatStyle = System.Windows.Forms.FlatStyle.Flat;
            this.button15.Location = new System.Drawing.Point(290, 536);
            this.button15.Name = "button15";
            this.button15.Size = new System.Drawing.Size(120, 120);
            this.button15.TabIndex = 14;
            this.button15.UseVisualStyleBackColor = false;
            this.button15.Click += new System.EventHandler(this.OnPixelButtonClick);
            // 
            // button_train
            // 
            this.button_train.Location = new System.Drawing.Point(428, 101);
            this.button_train.Name = "button_train";
            this.button_train.Size = new System.Drawing.Size(192, 63);
            this.button_train.TabIndex = 16;
            this.button_train.Text = "Обучить";
            this.button_train.UseVisualStyleBackColor = true;
            this.button_train.Click += new System.EventHandler(this.button_trainClick);
            // 
            // button_recognize
            // 
            this.button_recognize.Location = new System.Drawing.Point(428, 32);
            this.button_recognize.Name = "button_recognize";
            this.button_recognize.Size = new System.Drawing.Size(192, 63);
            this.button_recognize.TabIndex = 18;
            this.button_recognize.Text = "Распознать";
            this.button_recognize.UseVisualStyleBackColor = true;
            this.button_recognize.Click += new System.EventHandler(this.button_recognizeClick);
            // 
            // chart_Eavr
            // 
            chartArea1.CursorX.Interval = 0D;
            chartArea1.CursorX.IntervalType = System.Windows.Forms.DataVisualization.Charting.DateTimeIntervalType.Number;
            chartArea1.CursorY.Interval = 0D;
            chartArea1.Name = "ChartArea1";
            this.chart_Eavr.ChartAreas.Add(chartArea1);
            legend1.Enabled = false;
            legend1.Font = new System.Drawing.Font("Microsoft Sans Serif", 9.857143F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            legend1.IsTextAutoFit = false;
            legend1.Name = "Titles";
            this.chart_Eavr.Legends.Add(legend1);
            this.chart_Eavr.Location = new System.Drawing.Point(626, 32);
            this.chart_Eavr.Name = "chart_Eavr";
            this.chart_Eavr.RightToLeft = System.Windows.Forms.RightToLeft.No;
            series1.BorderWidth = 3;
            series1.ChartArea = "ChartArea1";
            series1.ChartType = System.Windows.Forms.DataVisualization.Charting.SeriesChartType.Line;
            series1.Color = System.Drawing.Color.FromArgb(((int)(((byte)(0)))), ((int)(((byte)(0)))), ((int)(((byte)(192)))));
            series1.IsVisibleInLegend = false;
            series1.Legend = "Titles";
            series1.Name = "Series1";
            series2.BorderWidth = 3;
            series2.ChartArea = "ChartArea1";
            series2.ChartType = System.Windows.Forms.DataVisualization.Charting.SeriesChartType.Line;
            series2.Color = System.Drawing.Color.FromArgb(((int)(((byte)(192)))), ((int)(((byte)(64)))), ((int)(((byte)(0)))));
            series2.Legend = "Titles";
            series2.Name = "Series2";
            series2.YAxisType = System.Windows.Forms.DataVisualization.Charting.AxisType.Secondary;
            this.chart_Eavr.Series.Add(series1);
            this.chart_Eavr.Series.Add(series2);
            this.chart_Eavr.Size = new System.Drawing.Size(817, 624);
            this.chart_Eavr.TabIndex = 19;
            this.chart_Eavr.Text = "chart1";
            this.chart_Eavr.Click += new System.EventHandler(this.chart_Eavr_Click);
            // 
            // label_output
            // 
            this.label_output.AutoSize = true;
            this.label_output.Font = new System.Drawing.Font("Microsoft Sans Serif", 14.14286F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.label_output.Location = new System.Drawing.Point(621, 713);
            this.label_output.Name = "label_output";
            this.label_output.Size = new System.Drawing.Size(121, 39);
            this.label_output.TabIndex = 20;
            this.label_output.Text = "Вывод";
            // 
            // label_probability
            // 
            this.label_probability.AutoSize = true;
            this.label_probability.Font = new System.Drawing.Font("Microsoft Sans Serif", 14.14286F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.label_probability.Location = new System.Drawing.Point(799, 713);
            this.label_probability.Name = "label_probability";
            this.label_probability.Size = new System.Drawing.Size(220, 39);
            this.label_probability.TabIndex = 21;
            this.label_probability.Text = "Вероятность";
            // 
            // button_saveTrain
            // 
            this.button_saveTrain.BackColor = System.Drawing.SystemColors.ControlLightLight;
            this.button_saveTrain.Location = new System.Drawing.Point(428, 523);
            this.button_saveTrain.Name = "button_saveTrain";
            this.button_saveTrain.Size = new System.Drawing.Size(192, 63);
            this.button_saveTrain.TabIndex = 23;
            this.button_saveTrain.Text = "Сохранить обучение";
            this.button_saveTrain.UseVisualStyleBackColor = false;
            this.button_saveTrain.Click += new System.EventHandler(this.button_saveTrainClick);
            // 
            // button_saveTest
            // 
            this.button_saveTest.Location = new System.Drawing.Point(428, 592);
            this.button_saveTest.Name = "button_saveTest";
            this.button_saveTest.Size = new System.Drawing.Size(192, 63);
            this.button_saveTest.TabIndex = 22;
            this.button_saveTest.Text = "Сохранить тест";
            this.button_saveTest.UseVisualStyleBackColor = true;
            this.button_saveTest.Click += new System.EventHandler(this.button_saveTestClick);
            // 
            // NecessaryOutput
            // 
            this.NecessaryOutput.BackColor = System.Drawing.SystemColors.Info;
            this.NecessaryOutput.Font = new System.Drawing.Font("Microsoft Sans Serif", 15.85714F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.NecessaryOutput.Location = new System.Drawing.Point(38, 694);
            this.NecessaryOutput.Name = "NecessaryOutput";
            this.NecessaryOutput.Size = new System.Drawing.Size(166, 49);
            this.NecessaryOutput.TabIndex = 24;
            this.NecessaryOutput.TextAlign = System.Windows.Forms.HorizontalAlignment.Center;
            this.NecessaryOutput.TextChanged += new System.EventHandler(this.NecessaryOutput_TextChanged);
            // 
            // contextMenuStrip1
            // 
            this.contextMenuStrip1.ImageScalingSize = new System.Drawing.Size(28, 28);
            this.contextMenuStrip1.Name = "contextMenuStrip1";
            this.contextMenuStrip1.Size = new System.Drawing.Size(61, 4);
            // 
            // button_test
            // 
            this.button_test.Location = new System.Drawing.Point(428, 170);
            this.button_test.Name = "button_test";
            this.button_test.Size = new System.Drawing.Size(192, 63);
            this.button_test.TabIndex = 25;
            this.button_test.Text = "Тестировать";
            this.button_test.UseVisualStyleBackColor = true;
            this.button_test.Click += new System.EventHandler(this.button_test_Click);
            // 
            // button_kill
            // 
            this.button_kill.BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(255)))), ((int)(((byte)(128)))), ((int)(((byte)(128)))));
            this.button_kill.Location = new System.Drawing.Point(1251, 694);
            this.button_kill.Name = "button_kill";
            this.button_kill.Size = new System.Drawing.Size(192, 63);
            this.button_kill.TabIndex = 26;
            this.button_kill.Text = "Уничтожить";
            this.button_kill.UseVisualStyleBackColor = false;
            this.button_kill.Click += new System.EventHandler(this.button_KillClick);
            // 
            // FormMain
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(11F, 24F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(1536, 889);
            this.Controls.Add(this.button_kill);
            this.Controls.Add(this.button_test);
            this.Controls.Add(this.NecessaryOutput);
            this.Controls.Add(this.button_saveTrain);
            this.Controls.Add(this.button_saveTest);
            this.Controls.Add(this.label_probability);
            this.Controls.Add(this.label_output);
            this.Controls.Add(this.chart_Eavr);
            this.Controls.Add(this.button_recognize);
            this.Controls.Add(this.button_train);
            this.Controls.Add(this.button15);
            this.Controls.Add(this.button14);
            this.Controls.Add(this.button13);
            this.Controls.Add(this.button12);
            this.Controls.Add(this.button11);
            this.Controls.Add(this.button10);
            this.Controls.Add(this.button9);
            this.Controls.Add(this.button8);
            this.Controls.Add(this.button7);
            this.Controls.Add(this.button6);
            this.Controls.Add(this.button5);
            this.Controls.Add(this.button4);
            this.Controls.Add(this.button3);
            this.Controls.Add(this.button2);
            this.Controls.Add(this.button1);
            this.Name = "FormMain";
            this.Text = "Jarvis";
            ((System.ComponentModel.ISupportInitialize)(this.chart_Eavr)).EndInit();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.Button button1;
        private System.Windows.Forms.Button button2;
        private System.Windows.Forms.Button button3;
        private System.Windows.Forms.Button button4;
        private System.Windows.Forms.Button button5;
        private System.Windows.Forms.Button button6;
        private System.Windows.Forms.Button button7;
        private System.Windows.Forms.Button button8;
        private System.Windows.Forms.Button button9;
        private System.Windows.Forms.Button button10;
        private System.Windows.Forms.Button button11;
        private System.Windows.Forms.Button button12;
        private System.Windows.Forms.Button button13;
        private System.Windows.Forms.Button button14;
        private System.Windows.Forms.Button button15;
        private System.Windows.Forms.Button button_train;
        private System.Windows.Forms.Button button_recognize;
        private System.Windows.Forms.DataVisualization.Charting.Chart chart_Eavr;
        private System.Windows.Forms.Label label_output;
        private System.Windows.Forms.Label label_probability;
        private System.Windows.Forms.Button button_saveTrain;
        private System.Windows.Forms.Button button_saveTest;
        private System.Windows.Forms.TextBox NecessaryOutput;
        private System.Windows.Forms.ContextMenuStrip contextMenuStrip1;
        private System.Windows.Forms.Button button_test;
        private System.Windows.Forms.Button button_kill;
    }
}

