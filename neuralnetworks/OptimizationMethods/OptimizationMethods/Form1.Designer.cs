namespace OptimizationMethods
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
            System.Windows.Forms.DataVisualization.Charting.ChartArea chartArea1 = new System.Windows.Forms.DataVisualization.Charting.ChartArea();
            System.Windows.Forms.DataVisualization.Charting.Legend legend1 = new System.Windows.Forms.DataVisualization.Charting.Legend();
            System.Windows.Forms.DataVisualization.Charting.Series series1 = new System.Windows.Forms.DataVisualization.Charting.Series();
            this.main_chart = new System.Windows.Forms.DataVisualization.Charting.Chart();
            this.button_1 = new System.Windows.Forms.Button();
            ((System.ComponentModel.ISupportInitialize)(this.main_chart)).BeginInit();
            this.SuspendLayout();
            // 
            // main_chart
            // 
            chartArea1.Name = "ChartArea1";
            this.main_chart.ChartAreas.Add(chartArea1);
            legend1.Name = "Legend1";
            this.main_chart.Legends.Add(legend1);
            this.main_chart.Location = new System.Drawing.Point(743, 12);
            this.main_chart.Name = "main_chart";
            series1.ChartArea = "ChartArea1";
            series1.Legend = "Legend1";
            series1.Name = "Series1";
            this.main_chart.Series.Add(series1);
            this.main_chart.Size = new System.Drawing.Size(744, 575);
            this.main_chart.TabIndex = 0;
            this.main_chart.Text = "chart1";
            // 
            // button_1
            // 
            this.button_1.Location = new System.Drawing.Point(12, 12);
            this.button_1.Name = "button_1";
            this.button_1.Size = new System.Drawing.Size(181, 52);
            this.button_1.TabIndex = 1;
            this.button_1.Text = "Обновить";
            this.button_1.UseVisualStyleBackColor = true;
            this.button_1.Click += new System.EventHandler(this.button_1_Click);
            // 
            // FormMain
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(11F, 24F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(1499, 964);
            this.Controls.Add(this.button_1);
            this.Controls.Add(this.main_chart);
            this.Name = "FormMain";
            this.Text = "Form1";
            this.Load += new System.EventHandler(this.FormMain_Load);
            ((System.ComponentModel.ISupportInitialize)(this.main_chart)).EndInit();
            this.ResumeLayout(false);

        }

        #endregion

        private System.Windows.Forms.DataVisualization.Charting.Chart main_chart;
        private System.Windows.Forms.Button button_1;
    }
}

