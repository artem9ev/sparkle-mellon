using System;

namespace MO_31_1_Artemev_Jarvis.NeuroNet
{
    internal class HiddenLayer : Layer
    {
        public HiddenLayer(int non, int nopn, NeuronType nt, string nmLayer) : base(non, nopn, nt, nmLayer)
        {
        }

        //прямой проход 
        public override void Recognize(Network net, Layer nextLayer)
        {
            double[] hidden_out = new double[numOfNeurons];
            for (int i = 0; i < numOfNeurons; i++)
            {
                hidden_out[i] = neurons[i].Output;

                nextLayer.Data = hidden_out;
            }
        }
        //обратный проход
        public override double[] BackwardPass(double[] gradient_sums)
        {
            double[] gr_sum = new double[numOfPrevNeurons];
            for (int i = 0; i < numOfPrevNeurons; i++)
            {
                double sum = 0;
                for (int k = 0; k < numOfNeurons; k++)
                {
                    sum += neurons[k].Weights[i] * neurons[k].Derivative * gradient_sums[k];
                }
                gr_sum[i] = sum;
            }

            for (int i = 0; i < numOfNeurons; i++)
            {
                for (int n = 0; n < numOfPrevNeurons + 1; n++)
                {
                    double deltaw = momentum * lastDeltaWeights[i, n];
                    if (n == 0) // есть порог 
                        deltaw += learningRate * neurons[i].Derivative * gradient_sums[i];
                    else
                        deltaw += learningRate * neurons[i].Derivative * gradient_sums[i] * neurons[i].Inputs[n - 1];

                    lastDeltaWeights[i, n] = deltaw;
                    neurons[i].Weights[n] += deltaw;
                }
            }
            return gr_sum;
        }

        public void SaveMemory()
        {
            WeightInit(MemoryMode.SET, AppDomain.CurrentDomain.BaseDirectory + "memory\\" + name + "_memory.csv");
        }
    }
}
