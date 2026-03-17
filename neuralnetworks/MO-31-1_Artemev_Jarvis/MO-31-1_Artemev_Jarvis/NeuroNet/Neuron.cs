using System;
using static System.Math;

namespace MO_31_1_Artemev_Jarvis.NeuroNet
{
    internal class Neuron
    {
        private NeuronType type;
        private double[] weights;
        private double[] inputs;
        private double output;
        private double derivative;

        // крнстанты для ф-ии фктивации
        private double a = 0.8d;
        // и т.д.

        public double[] Weights 
        {
            get => weights;
            set 
            {
                for (int i = 0; i < value.Length; i++)
                {
                    if (double.IsNaN(value[i]))
                    {
                        throw new Exception($"Неверный вес - [{type} - w: {i}]");
                    }
                }

                weights = value;
            }
        }
        public double[] Inputs { get => inputs; set => inputs = value; }
        public double Output => output;
        public double Derivative => derivative;

        public Neuron(double[] memoryWeights, NeuronType typeNeuron)
        {
            weights = memoryWeights;
            type = typeNeuron;
        }

        public void Activator(double[] i)
        {
            inputs = i;

            double sum = weights[0];

            for (int j = 0; j < inputs.Length; j++)
            {
                sum += inputs[j] * weights[j + 1];
            }

            switch (type)
            {
                case NeuronType.Hidden:
                    output = LogicFunc(sum);
                    derivative = LogicFunc_Derivator(sum);
                    break;
                case NeuronType.Output:
                    output = Exp(sum);
                    break;
            }
        }

        public double LogicFunc(double sum)
        {
            return 1 / (1 + Exp(-sum * a));
        }

        public double LogicFunc_Derivator(double sum)
        {
            return LogicFunc(sum) * (1 - LogicFunc(sum));
        }
    }
}
