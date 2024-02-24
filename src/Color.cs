using System;

namespace RayTracerChallenge
{
    class Color : Tuple
    {
        public float red
        {
            get { return x; }
            set { x = value; }
        }

        public float green
        {
            get { return y; }
            set { y = value; }
        }

        public float blue
        {
            get { return z; }
            set { z = value; }
        }

        public Color(float red, float green, float blue) : base(red, green, blue, 2)
        {
        }

        public static Color operator *(Color c1, Color c2)
        {
            return new Color(c1.red * c2.red, c1.green * c2.green, c1.blue * c2.blue);
        }
    }
}
