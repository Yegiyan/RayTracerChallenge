using System;

namespace RayTracerChallenge
{
    abstract class Tuple
    {
        const float EPSILON = 0.00001f;

        public float x;
        public float y;
        public float z;
        public byte w;

        public Tuple(float x, float y, float z, byte w)
        {
            this.x = x; 
            this.y = y; 
            this.z = z;
            this.w = w;
        }

        public static Tuple operator +(Tuple t1, Tuple t2)
        {
            if (t1 is Color && t2 is Color)
                return new Color(t1.x + t2.x, t1.y + t2.y, t1.z + t2.z);

            if (t1 is Point && t2 is Point)
                throw new InvalidOperationException("Both tuples are points and cannot be added.");

            if (t1 is Point || t2 is Point)
                return new Point(t1.x + t2.x, t1.y + t2.y, t1.z + t2.z);

            else
                return new Vector(t1.x + t2.x, t1.y + t2.y, t1.z + t2.z);
        }

        public static Tuple operator -(Tuple t1, Tuple t2)
        {
            if (t1 is Color && t2 is Color)
                return new Color(t1.x - t2.x, t1.y - t2.y, t1.z - t2.z);

            if (t1 is Point && t2 is Point)
                return new Vector(t1.x - t2.x, t1.y - t2.y, t1.z - t2.z);

            if (t1 is Point || t2 is Point)
                return new Point(t1.x - t2.x, t1.y - t2.y, t1.z - t2.z);

            else
                return new Vector(t1.x - t2.x, t1.y - t2.y, t1.z - t2.z);
        }

        public static Tuple operator -(Tuple t)
        {
            if (t is Vector)
                return new Vector(-t.x, -t.y, -t.z);

            else
                return new Point(-t.x, -t.y, -t.z);
        }

        public static Tuple operator *(Tuple t, float c)
        {
            if (t is Vector)
                return new Vector(t.x * c, t.y * c, t.z * c);

            else if (t is Point)
                return new Point(t.x * c, t.y * c, t.z * c);

            else
                return new Color(t.x * c, t.y * c, t.z * c);
        }

        public static Tuple operator /(Tuple t, float c)
        {
            if (t is Vector)
                return new Vector(t.x / c, t.y / c, t.z / c);

            else
                return new Point(t.x / c, t.y / c, t.z / c);
        }

        public void Print()
        {
            if (w == 0)
                Console.WriteLine("({0}, {1}, {2} | VECTOR)", x, y, z);

            else if (w == 1)
                Console.WriteLine("({0}, {1}, {2} | POINT)", x, y, z);

            else
                Console.WriteLine("({0}, {1}, {2} | COLOR)", x, y, z);
        }
    }
}