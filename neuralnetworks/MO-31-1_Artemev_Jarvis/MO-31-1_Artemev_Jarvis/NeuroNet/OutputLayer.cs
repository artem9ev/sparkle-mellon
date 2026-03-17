using System;

namespace MO_31_1_Artemev_Jarvis.NeuroNet
{
    internal class OutputLayer : Layer
    {
        public OutputLayer(int non, int nopn, NeuronType nt, string nmLayer) : base(non, nopn, nt, nmLayer)
        {
        }

        public override void Recognize(Network net, Layer nextLayer)
        {
            double e_sum = 0;
            for (int i = 0; i < neurons.Length; i++)
                e_sum += neurons[i].Output;

            for (int i = 0; i < neurons.Length; i++)
                net.Fact[i] = neurons[i].Output / e_sum;

        }

        //обратный проход
        public override double[] BackwardPass(double[] errors)
        {
            double[] gr_sum = new double[numOfPrevNeurons];
            for (int i = 0; i < numOfPrevNeurons; i++)
            {
                double sum = 0;
                for (int k = 0; k < numOfNeurons; k++)
                {
                    sum += neurons[k].Weights[i + 1] * errors[k];
                }
                gr_sum[i] = sum;
            }

            for (int i = 0; i < numOfNeurons; i++)
            {
                for (int n = 0; n < numOfPrevNeurons + 1; n++)
                {
                    double deltaw = momentum * lastDeltaWeights[i, n];
                    if (n == 0) // есть порог 
                        deltaw += learningRate * errors[i];
                    else
                        deltaw += learningRate * errors[i] * neurons[i].Inputs[n - 1];

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
