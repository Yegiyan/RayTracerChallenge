using System;

namespace RayTracerChallenge
{
    class Vector : Tuple
    {
        public Vector(float x, float y, float z) : base(x, y, z, 0)
        {
        }

        public static float Dot(Vector v1, Vector v2) 
        {
            return (v1.x * v2.x) + (v1.y * v2.y) + (v1.z * v2.z);
        
        }

        public static Vector Cross(Vector v1, Vector v2)
        {
            return new Vector(v1.y * v2.z - v1.z * v2.y, v1.z * v2.x - v1.x * v2.z, v1.x * v2.y - v1.y * v2.x);
        }

        public static Vector Normalize(Vector vec)
        {
            vec = new(vec.x / Magnitude(vec), vec.y / Magnitude(vec), vec.z / Magnitude(vec));
            return vec;
        }

        public static float Magnitude(Vector vec)
        {
            return (float)Math.Sqrt(Math.Pow(vec.x, 2) + Math.Pow(vec.y, 2) + Math.Pow(vec.z, 2));
        }
    }
}
