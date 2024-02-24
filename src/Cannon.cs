using System;

namespace RayTracerChallenge
{
    class Cannon
    {
        public void Launch()
        {
            Canvas canvas = new Canvas(900, 550);

            Point startPos = new Point(0, 1, 0);
            Vector velocity = (Vector)(Vector.Normalize(new Vector(1, 1.8f, 0)) * 10);

            Vector gravity = new Vector(0, -0.1f, 0);
            Vector wind = new Vector(-0.01f, 0, 0);

            Projectile proj = new(startPos, velocity);
            Environment env = new(gravity, wind);

            Projectile pixel = Tick(env, proj);

            int tick = 0;
            while (pixel.position.y > 0)
            {
                pixel = Tick(env, pixel);
                tick++;

                PPM.WritePixel(canvas, (int)pixel.position.x, canvas.height - (int)pixel.position.y, new Color(1, 0.8f, 0.6f));
                Console.WriteLine("Y-Position: {0} at tick {1}", Math.Max(pixel.position.y, 0).ToString("n2"), tick);
            }
            PPM.CanvasToPPM(canvas);
        }

        Projectile Tick(Environment env, Projectile proj)
        {
            Tuple position = proj.position + proj.velocity;
            Tuple velocity = proj.velocity + env.gravity + env.wind;
            return new Projectile((Point)position, (Vector)velocity);
        }
    }

    class Environment
    {
        public Vector gravity;
        public Vector wind;

        public Environment(Vector gravity, Vector wind)
        {
            this.gravity = gravity;
            this.wind = wind;
        }
    }

    class Projectile
    {
        public Point position;
        public Vector velocity;

        public Projectile(Point position, Vector velocity)
        {
            this.position = position;
            this.velocity = velocity;
        }
    }
}