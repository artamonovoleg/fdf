//
// Created by kaygalle on 21.08.2020.
//

#ifndef FDF_INTERPOLATE_HPP
#define FDF_INTERPOLATE_HPP

#include <SFML/Graphics.hpp>

class Interpolate
{
    public:
        static int lerp(int start, int end, double percentage);
        static float percent(int start, int end, int current);
        static sf::Color mix_color(sf::Color color1, sf::Color color2, float percent);
};

#endif //FDF_INTERPOLATE_HPP
