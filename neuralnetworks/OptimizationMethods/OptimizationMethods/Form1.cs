using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace OptimizationMethods
{
    public partial class FormMain : Form
    {
        public FormMain()
        {
            InitializeComponent();
        }

        private void FormMain_Load(object sender, EventArgs e)
        {

        }

        private void Lab_1()
        {

        }

        private void DrawChart(double[] points)
        {
            foreach (int p in points)
            {
                main_chart.Series[1].Points.Add(p);
            }

            main_chart.Update();
        }

        private void button_1_Click(object sender, EventArgs e)
        {

        }
    }
}
