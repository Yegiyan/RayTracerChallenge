using System;

namespace RayTracerChallenge
{
    class PPM
    {
        public static void CanvasToPPM(Canvas canvas)
        {
            string filePath = @"C:\Dev\Programs\Ray Tracer Challenge\image.ppm";
            using (StreamWriter writer = new StreamWriter(filePath))
            {
                // PPM Header Information
                writer.WriteLine("P3");
                writer.WriteLine($"{canvas.width} {canvas.height}");
                writer.WriteLine("255");

                // Write RGB Pixel Data to PPM
                int lineLength = 0;
                for (int y = 0; y < canvas.height; y++)
                {
                    for (int x = 0; x < canvas.width; x++)
                    {
                        Color color = PixelAt(canvas, x, y);
                        string pixelData = ($"{Math.Clamp((int)Math.Round(color.red * 255), 0, 255)} " +
                                            $"{Math.Clamp((int)Math.Round(color.green * 255), 0, 255)} " +
                                            $"{Math.Clamp((int)Math.Round(color.blue * 255), 0, 255)} ");

                        // Make sure line lengths in PPM don't exceed 70 characters
                        if (lineLength + pixelData.Length > 70)
                        {
                            writer.WriteLine();
                            lineLength = 0;
                        }

                        writer.Write(pixelData);
                        lineLength += pixelData.Length;
                    }
                    writer.WriteLine();
                    lineLength = 0;
                }
            }
            Console.WriteLine($"PPM image has been written to {filePath}");
        }

        public static void WritePixel(Canvas canvas, int x, int y, Color color)
        {
            if (x >= 0 && x < canvas.width && y >= 0 && y < canvas.height)
                canvas.pixels[x, y] = color;
            else
                Console.WriteLine($"Cannot write pixel at ({x}, {y}), it's out of bounds!");
        }

        public static Color PixelAt(Canvas canvas, int x, int y)
        {
            return canvas.pixels[x, y];
        }
    }
}