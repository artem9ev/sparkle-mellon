using System;
using System.IO;
using System.Windows.Forms;

namespace MO_31_1_Artemev_Jarvis.NeuroNet
{
    abstract class Layer
    {
        private string pathDirWeights;
        private string pathFileWeights;

        protected string name;

        protected int numOfNeurons;
        protected int numOfPrevNeurons;

        protected const double learningRate = 0.13d; // 0.065
        protected const double momentum = 0.1d; // 0.6

        protected double[,] lastDeltaWeights;

        protected Neuron[] neurons;

        public Neuron[] Neurons { get { return neurons; } set { neurons = value; } }

        public double[] Data
        {
            set
            {
                for (int i = 0; i < numOfNeurons; i++)
                {
                    Neurons[i].Activator(value);
                }
            }
        }

        protected Layer(int non, int nopn, NeuronType nt, string name)
        {
            numOfNeurons = non;
            numOfPrevNeurons = nopn;
            Neurons = new Neuron[non];
            this.name = name;

            pathDirWeights = AppDomain.CurrentDomain.BaseDirectory + "memory\\";
            pathFileWeights = pathDirWeights + this.name + "_memory.csv";

            double[,] Weights;

            if (File.Exists(pathFileWeights))
            {
                Weights = WeightInit(MemoryMode.GET, pathFileWeights);
            }
            else
            {
                Directory.CreateDirectory(pathDirWeights);
                Weights = WeightInit(MemoryMode.INIT, pathFileWeights);
            }

            lastDeltaWeights = new double[non, nopn + 1];

            for (int i = 0; i < non; i++)
            {
                double[] tmp_weights = new double[nopn + 1];
                for (int j = 0; j < nopn + 1; j++)
                {
                    tmp_weights[j] = Weights[i, j];
                }
                Neurons[i] = new Neuron(tmp_weights, nt);
            }
        }

        public double[,] WeightInit(MemoryMode mode, string path)
        {
            char[] delim = new char[] { ';', ' ' };
            string[] tmpStrWeights;
            double[,] weights = new double[numOfNeurons, numOfPrevNeurons + 1];

            switch (mode)
            {
                case MemoryMode.GET:
                    tmpStrWeights = File.ReadAllLines(path); //читаем все строки файла
                    string[] memory_element; //временный массив, хранящий веса одного нейрона в виде строк
                    for (int i = 0; i < numOfNeurons; i++)
                    {
                        memory_element = tmpStrWeights[i].Split(delim);
                        for (int j = 0; j < numOfPrevNeurons + 1; j++)
                        {
                            weights[i, j] = double.Parse(memory_element[j].Replace(',', '.'),
                                System.Globalization.CultureInfo.InvariantCulture);
                        }
                    }
                    break;
                case MemoryMode.SET:
                    for (int i = 0; i < numOfNeurons; i++)
                    {
                        for (int j = 0; j < numOfPrevNeurons + 1; j++)
                        {
                            weights[i, j] = Neurons[i].Weights[j];
                        }
                    }
                    SaveWeights(path, weights);
                    break;
                case MemoryMode.INIT:
                    Random random = new Random();
                    for (int i = 0; i < numOfNeurons; i++)
                    {
                        double sum = 0.0;
                        double squaredSum = 0.0;

                        //Генерация весов
                        for (int j = 0; j < numOfPrevNeurons + 1; j++)
                        {
                            weights[i, j] = random.NextDouble() * 2.0 - 1.0;
                            sum += weights[i, j];
                            squaredSum += weights[i, j] * weights[i, j];
                        }

                        //Вычисляем среднее и дисперсию
                        double mean = sum / (numOfPrevNeurons + 1);
                        double variance = (squaredSum / (numOfPrevNeurons + 1)) - (mean * mean);
                        double root = Math.Sqrt(variance);

                        Console.WriteLine($"[INIT_0] mean:\t{mean:f5} | var:\t{variance:f5} | root:\t{root:f5}");

                        //Нормализуем веса
                        for (int j = 0; j < numOfPrevNeurons + 1; j++)
                        {
                            weights[i, j] = (weights[i, j] - mean) / root;
                        }

                        // ------------------------------------

                        sum = 0.0;
                        squaredSum = 0.0;

                        for (int j = 0; j < numOfPrevNeurons + 1; j++)
                        {
                            sum += weights[i, j];
                            squaredSum += weights[i, j] * weights[i, j];
                        }

                        //Вычисляем среднее и дисперсию
                        mean = sum / (numOfPrevNeurons + 1);
                        variance = (squaredSum / (numOfPrevNeurons + 1)) - (mean * mean);
                        root = Math.Sqrt(variance);

                        Console.WriteLine($"[INIT_1] mean:\t{mean:f5} | var:\t{variance:f5} | root:\t{root:f5}");
                    }

                    SaveWeights(path, weights);
                    break;
            }
            return weights;
        }

        private void SaveWeights(string path, double[,] weights)
        {
            string tmpStr = "";
            for (int i = 0; i < numOfNeurons; i++)
            {
                string[] tmpRow = new string[numOfPrevNeurons + 1];
                for (int j = 0; j < numOfPrevNeurons + 1; j++)
                {
                    tmpRow[j] = weights[i, j].ToString(System.Globalization.CultureInfo.InvariantCulture);
                }
                tmpStr += string.Join(";", tmpRow) + "\n";
            }
            File.WriteAllText(path, tmpStr);
        }

        abstract public void Recognize(Network net, Layer nextLayer); // для прямых проходов 
        abstract public double[] BackwardPass(double[] stuff); // и обратных 
    }
}
