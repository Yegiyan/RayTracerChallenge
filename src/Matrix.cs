using System;

namespace RayTracerChallenge
{
    class Matrix
    {
        private float[,] array;
        const float EPSILON = 0.00001f;

        private int rows;
        private int cols;
        private static int size;

        public Matrix(int rows, int cols)
        {
            this.rows = rows;
            this.cols = cols;
            size = rows * cols;
            array = new float[rows, cols];
        }

        public float this[int r, int c]
        {
            get
            {
                return array[r, c];
            }

            set
            {
                array[r, c] = value;
            }
        }

        public static Matrix operator *(Matrix m1, Matrix m2)
        {
            Matrix M = new Matrix(4, 4); // only expect to multiply 4x4 matrices

            for (int i = 0; i < 4; i++)
            {
                for (int j = 0; j < 4; j++)
                {
                    M[i, j] = m1[i, 0] * m2[0, j] +
                              m1[i, 1] * m2[1, j] +
                              m1[i, 2] * m2[2, j] +
                              m1[i, 3] * m2[3, j];
                }
            }

            return M;
        }

        public static Tuple operator *(Matrix m, Tuple t)
        {
            float x = m[0, 0] * t.x + m[0, 1] * t.y + m[0, 2] * t.z + m[0, 3] * t.w;
            float y = m[1, 0] * t.x + m[1, 1] * t.y + m[1, 2] * t.z + m[1, 3] * t.w;
            float z = m[2, 0] * t.x + m[2, 1] * t.y + m[2, 2] * t.z + m[2, 3] * t.w;
            float w = m[3, 0] * t.x + m[3, 1] * t.y + m[3, 2] * t.z + m[3, 3] * t.w;

            if (t is Vector)
                return new Vector(x, y, z);
            else
                return new Point(x, y, z);
        }

        public bool Compare(Matrix m)
        {
            for (int i = 0; i < rows; i++)
            {
                for (int j = 0; j < cols; j++)
                {
                    if (!isEqual(this[i, j], m[i, j]))
                        return false;
                }
            }

            return true;
        }

        private bool isEqual(float a, float b)
        {
            if (MathF.Abs(a - b) < EPSILON)
                return true;
            else
                return false;
        }
    }
}