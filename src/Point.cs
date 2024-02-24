using System;

namespace RayTracerChallenge
{
    class Point : Tuple
    {
        public Point(float x, float y, float z) : base(x, y, z, 1)
        {
        }
    }
}
