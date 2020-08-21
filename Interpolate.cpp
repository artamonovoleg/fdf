//
// Created by kaygalle on 21.08.2020.
//

#include "Interpolate.hpp"

int Interpolate::lerp(int start, int end, double percentage)
{
    return ((int)((1 - percentage) * start + percentage * end));
}

float Interpolate::percent(int start, int end, int current)
{
    float placement;
    float distance;

    placement = float(current - start);
    distance = float(end - start);
    return ((distance == 0) ? 1.0f : (placement / distance));
}

sf::Color Interpolate::mix_color(sf::Color color1, sf::Color color2, float percent)
{
    sf::Color ret;
    ret.r = lerp(color1.r, color2.r, percent);
    ret.g = lerp(color1.g, color2.g, percent);
    ret.b = lerp(color1.b, color2.b, percent);
    ret.a = lerp(color1.a, color2.a, percent);
    return ret;
}
