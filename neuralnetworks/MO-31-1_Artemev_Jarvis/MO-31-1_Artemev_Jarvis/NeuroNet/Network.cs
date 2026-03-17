using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Threading;

namespace MO_31_1_Artemev_Jarvis.NeuroNet
{
    internal class Network
    {
        // 15 70 33 10

        // все слои сети 
        private InputLayer input_layer = null;
        private HiddenLayer hidden_layer1 = new HiddenLayer(70, 15, NeuronType.Hidden, nameof(hidden_layer1));
        private HiddenLayer hidden_layer2 = new HiddenLayer(33, 70, NeuronType.Hidden, nameof(hidden_layer2));
        private OutputLayer output_layer = new OutputLayer(10, 33, NeuronType.Output, nameof(output_layer));

        private double[] fact = new double[10]; // массив фактического выхода сети
        private double[] e_error_avr; // среднее значение энергии ошибки эпохи обучения 
        private double[] accuracy_avr; // среднее значение точности

        // свойства
        public double[] Fact { get => fact; }

        public double[] E_error_avr { get => e_error_avr; set => e_error_avr = value; }

        public event Action<double> OnE_Error;
        public event Action<double> OnAccuracy;
        public event Action OnTaskStart;
        public event Action<NetworkMode> OnTaskEnd;

        // конструктор
        public Network() { }

        private void TrainEpoch(int epoch)
        {
            double tmpSumError;
            double[] errors;
            double[] temp_gsums1;
            double[] temp_gsums2;

            e_error_avr[epoch] = 0;
            accuracy_avr[epoch] = 0;
            input_layer.Shuffling_Array_Rows(input_layer.TrainSet);
            for (int i = 0; i < input_layer.TrainSet.GetLength(0); i++)
            {
                double[] tmpTrain = new double[15];
                for (int j = 0; j < tmpTrain.Length; j++)
                    tmpTrain[j] = input_layer.TrainSet[i, j + 1];

                ForwardPass(tmpTrain);

                tmpSumError = 0;
                errors = new double[fact.Length];
                for (int x = 0; x < errors.Length; x++)
                {
                    if (x == input_layer.TrainSet[i, 0])
                        errors[x] = 1.0 - fact[x];
                    else
                        errors[x] = -fact[x];

                    tmpSumError += errors[x] * errors[x] / 2; // текущее значение э ошиб
                }
                e_error_avr[epoch] += tmpSumError / errors.Length / input_layer.TrainSet.GetLength(0);
                accuracy_avr[epoch] += 100 * Fact.Max() / input_layer.TrainSet.GetLength(0);

                temp_gsums2 = output_layer.BackwardPass(errors);
                temp_gsums1 = hidden_layer2.BackwardPass(temp_gsums2);
                hidden_layer1.BackwardPass(temp_gsums1);

            }

            string pathDirWeights = AppDomain.CurrentDomain.BaseDirectory + "memory\\";
            hidden_layer1.WeightInit(MemoryMode.SET, pathDirWeights + nameof(hidden_layer1) + "_memory.csv");
            hidden_layer2.WeightInit(MemoryMode.SET, pathDirWeights + nameof(hidden_layer2) + "_memory.csv");
            output_layer.WeightInit(MemoryMode.SET, pathDirWeights + nameof(output_layer) + "_memory.csv");
        }

        private void TestEpoch(int epoch)
        {
            e_error_avr[epoch] = 0;
            accuracy_avr[epoch] = 0;

            input_layer.Shuffling_Array_Rows(input_layer.TestSet);
            Console.WriteLine($"Test Epoch - {epoch}");
            for (int i = 0; i < input_layer.TestSet.GetLength(0); i++)
            {
                double[] tmpTrain = new double[15];
                Console.Write($"{input_layer.TestSet[i, 0]} -");

                for (int j = 0; j < tmpTrain.Length; j++)
                {
                    tmpTrain[j] = input_layer.TestSet[i, j + 1];
                    Console.Write($" {tmpTrain[j]}");
                }

                Console.WriteLine();

                ForwardPass(tmpTrain);

                double tmpSumError = 0;
                double[] errors = new double[fact.Length];
                for (int x = 0; x < errors.Length; x++)
                {
                    if (x == input_layer.TestSet[i, 0])
                        errors[x] = 1 - fact[x];
                    else
                        errors[x] = -fact[x];

                    tmpSumError += errors[x] * errors[x] / 2; // текущее значение э ошиб
                }
                e_error_avr[epoch] += tmpSumError / errors.Length / input_layer.TestSet.GetLength(0);
                accuracy_avr[epoch] += 100 * Fact.Max() / input_layer.TestSet.GetLength(0);

            }
            Console.WriteLine($"test len: {input_layer.TestSet.GetLength(0)}");
        }

        public async Task TrainAsync(int epoches = 20)
        {
            OnTaskStart?.Invoke();

            input_layer = new InputLayer(NetworkMode.Train);

            e_error_avr = new double[epoches];
            accuracy_avr = new double[epoches];
            for (int k = 0; k < epoches; k++)
            {
                await Task.Run(() => TrainEpoch(k));
                OnE_Error?.Invoke(e_error_avr[k]);
                OnAccuracy?.Invoke(accuracy_avr[k]);
            }

            OnTaskEnd?.Invoke(NetworkMode.Train);
        }

        public async Task TestAsync(int epoches = 2)
        {
            OnTaskStart?.Invoke();
            input_layer = new InputLayer(NetworkMode.Test);

            e_error_avr = new double[epoches];
            accuracy_avr = new double[epoches];
            for (int k = 0; k < epoches; k++)
            {
                await Task.Run(() => TestEpoch(k));
                OnE_Error?.Invoke(e_error_avr[k]);
                OnAccuracy?.Invoke(accuracy_avr[k]);
            }

            OnTaskEnd?.Invoke(NetworkMode.Test);
        }

        // прямой проход сети
        public void ForwardPass(double[] netInput)
        {
            hidden_layer1.Data = netInput;
            hidden_layer1.Recognize(null, hidden_layer2);
            hidden_layer2.Recognize(null, output_layer);
            output_layer.Recognize(this, null);
        }

        public void Kill()
        {
            hidden_layer1.KillWieghts();
            hidden_layer2.KillWieghts();
            output_layer.KillWieghts();
        }
    }
}
