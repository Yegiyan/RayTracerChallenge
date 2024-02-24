using System;

namespace RayTracerChallenge
{
    class Program
    {
        public static void Main()
        {
            Matrix M = new Matrix(4, 4);
            Tuple P = new Point(1, 2, 3);

            M[0, 0] = 1;
            M[0, 1] = 2;
            M[0, 2] = 3;
            M[0, 3] = 4;

            M[1, 0] = 2;
            M[1, 1] = 4;
            M[1, 2] = 4;
            M[1, 3] = 2;

            M[2, 0] = 8;
            M[2, 1] = 6;
            M[2, 2] = 4;
            M[2, 3] = 1;

            M[3, 0] = 0;
            M[3, 1] = 0;
            M[3, 2] = 0;
            M[3, 3] = 1;

            Tuple T = M * P;

            T.Print();
            Console.ReadLine();
        }
    }
}