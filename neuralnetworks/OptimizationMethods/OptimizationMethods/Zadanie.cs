using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace OptimizationMethods
{
    internal abstract class Zadanie
    {
        protected double[] m_points;

        public double[] points => points;

        public abstract void Calculate();
    }
}
