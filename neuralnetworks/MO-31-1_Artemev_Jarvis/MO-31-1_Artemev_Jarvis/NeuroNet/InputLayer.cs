using System;
using System.IO;

namespace MO_31_1_Artemev_Jarvis.NeuroNet
{
    internal class InputLayer
    {
        private double[,] trainSet;
        private double[,] testSet;

        public double[,] TrainSet { get => trainSet; }
        public double[,] TestSet { get => testSet; }

        public InputLayer(NetworkMode nm)
        {
            string path = AppDomain.CurrentDomain.BaseDirectory;
            string[] tempStrings;
            string[] tempValues;

            switch (nm)
            {
                case NetworkMode.Train:
                    if (!File.Exists(path + "train.txt"))
                    {
                        return;
                    }

                    tempStrings = File.ReadAllLines(path + "train.txt");
                    trainSet = new double[tempStrings.Length, 16];

                    for (int i = 0; i < tempStrings.Length; i++)
                    {
                        tempValues = tempStrings[i].Split(' ');

                        for (int j = 0; j < 16; j++)
                        {
                            trainSet[i, j] = double.Parse(tempValues[j]);
                        }
                    }
                    Shuffling_Array_Rows(trainSet);
                    break;

                case NetworkMode.Test:
                    tempStrings = File.ReadAllLines(path + "test.txt");
                    testSet = new double[tempStrings.Length, 16];

                    for (int i = 0; i < tempStrings.Length; i++)
                    {
                        tempValues = tempStrings[i].Split(' ');

                        for (int j = 0; j < 16; j++)
                        {
                            testSet[i, j] = double.Parse(tempValues[j]);
                        }
                    }
                    Shuffling_Array_Rows(testSet);
                    break;
            }

        }
        public void Shuffling_Array_Rows(double[,] arr)
        {
            Random random = new Random();
            int rowCount = arr.GetLength(0);
            int colCount = arr.GetLength(1);

            // Алгоритм Фишера-Йетса для перемешивания строк
            for (int i = rowCount - 1; i > 0; i--)
            {
                // Выбираем случайный индекс от 0 до i
                int j = random.Next(i + 1);

                // Меняем местами строки i и j
                for (int col = 0; col < colCount; col++)
                {
                    double temp = arr[i, col];
                    arr[i, col] = arr[j, col];
                    arr[j, col] = temp;
                }
            }
        }
    }
}
