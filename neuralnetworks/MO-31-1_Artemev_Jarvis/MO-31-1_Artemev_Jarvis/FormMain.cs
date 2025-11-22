using System;
using System.Collections.Generic;
using System.Drawing;
using System.Linq;
using System.Windows.Forms;
using System.IO;
using MO_31_1_Artemev_Jarvis.NeuroNet;
using System.Threading.Tasks;

namespace MO_31_1_Artemev_Jarvis
{
    public partial class FormMain : Form
    {
        private double[] m_inputPixels;
        private Network network;

        private List<Button> m_usedButtons = new List<Button>();

        public FormMain()
        {
            m_inputPixels = new double[15];
            network = new Network();

            network.OnE_Error += OnE_Error;
            network.OnTaskStart += OnTrainStart;
            network.OnTaskEnd += OnTrainEnd;

            InitializeComponent();
        }

        private void OnE_Error(double e)
        {
            chart_Eavr.Series[0].Points.AddY(e);
            Console.WriteLine($"[{chart_Eavr.Series[0].Points.Count}] e: {e}");
        }

        private void OnTrainStart()
        {
            SetControlsEnabled(false);
        }

        private void OnTrainEnd(NetworkMode mode)
        {
            SetControlsEnabled(true);
            if (mode == NetworkMode.Train)
            {
                MessageBox.Show("Обучение успешно завершено.", "информация", MessageBoxButtons.OK, MessageBoxIcon.Information);
            }
        }

        private void SetControlsEnabled(bool enabled)
        {
            foreach (Control control in Controls)
            {
                if (control is Button)
                {
                    control.Enabled = enabled;
                }
            }
        }

        private void OnPixelButtonClick(object sender, EventArgs e)
        {
            Button button = (Button)sender;
            if (button.BackColor == Color.White)
            {
                button.BackColor = Color.Black;
                m_inputPixels[button.TabIndex] = 1d;
                m_usedButtons.Add(button);
            }
            else
            {
                button.BackColor = Color.White;
                m_inputPixels[button.TabIndex] = 0d;
                m_usedButtons.Remove(button);
            }
        }

        private void button_trainClick(object sender, EventArgs e)
        {
            Task task = network.TrainAsync();
        }

        private void button_test_Click(object sender, EventArgs e)
        {
            Task task = network.TestAsync(10);
        }

        //сохранить в файл обучающий пример 
        private void button_saveTrainClick(object sender, EventArgs e)
        {
            button_saveTrain.BackColor = SaveExample(AppDomain.CurrentDomain.BaseDirectory + "train.txt") ? Color.Lime : Color.IndianRed;
        }

        //сохранить в файл Тестовый пример 
        private void button_saveTestClick(object sender, EventArgs e)
        {
            button_saveTest.BackColor = SaveExample(AppDomain.CurrentDomain.BaseDirectory + "test.txt") ? Color.Lime : Color.IndianRed;
        }

        private bool SaveExample(string path)
        {
            if (string.IsNullOrEmpty(NecessaryOutput.Text))
            {
                return false;
            }

            string tmpStr = NecessaryOutput.Text;

            for (int i = 0; i < m_inputPixels.Length; i++)
            {
                tmpStr += " " + m_inputPixels[i].ToString();
                m_inputPixels[i] = 0;
            }
            tmpStr += "\n";
            File.AppendAllText(path, tmpStr);

            NecessaryOutput.Text = "";

            foreach (Button button in m_usedButtons)
            {
                button.BackColor = Color.White;
            }

            return true;
        }

        // Обработчик события клика кнопки "Распознать"
        private void button_recognizeClick(object sender, EventArgs e)
        {
            network.ForwardPass(m_inputPixels);
            label_output.Text = network.Fact.ToList().IndexOf(network.Fact.Max()).ToString();
            label_probability.Text = (100 * network.Fact.Max()).ToString("0.00") + "%";
        }

        private void chart_Eavr_Click(object sender, EventArgs e)
        {

        }

        private void NecessaryOutput_TextChanged(object sender, EventArgs e)
        {
            if (NecessaryOutput.Text.Length > 1)
            {
                NecessaryOutput.Text = NecessaryOutput.Text[0].ToString();
            }
            if (NecessaryOutput.Text.Length == 0 || NecessaryOutput.Text[0] < '0' || NecessaryOutput.Text[0] > '9')
            {
                NecessaryOutput.Text = "";
                return;
            }
        }
    }
}
