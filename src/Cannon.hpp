#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <vector>
#include <cmath>

#include "Tuple.hpp"

struct Projectile
{
    Tuple position;
    Tuple velocity;
    Projectile(const Tuple& position, const Tuple& velocity) : position(position), velocity(velocity) {}
};

struct Environment
{
    Tuple gravity;
    Tuple wind;
    Environment(const Tuple& gravity, const Tuple& wind) : gravity(gravity), wind(wind) {}
};

Projectile tick(const Environment& env, const Projectile& proj)
{
    Tuple position = proj.position + proj.velocity;
    Tuple velocity = proj.velocity + env.gravity + env.wind;
    return Projectile(position, velocity);
}