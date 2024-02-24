using System.IO;

namespace RayTracerChallenge
{
    class Canvas
    {
        public int width;
        public int height;

        public Color[,] pixels;

        public Canvas(int width, int height) 
        {
            this.width = width;
            this.height = height;
            pixels = new Color[width, height];

            
            for (int x = 0; x < width; x++)
                for (int y = 0; y < height; y++)
                    pixels[x, y] = new Color(0, 0, 0);
        }
    }
}