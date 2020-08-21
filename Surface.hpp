//
// Created by kaygalle on 21.08.2020.
//

#ifndef FDF_SURFACE_HPP
#define FDF_SURFACE_HPP

#include <memory>
#include <SFML/Graphics.hpp>

#include "Point.hpp"
#include "Interpolate.hpp"

class Surface
{
    private:
        int _width = 0;
        int _height = 0;
    public:
        std::unique_ptr<sf::Uint8[]> data;
    public:
        Surface(int width, int height);

        void clear() const;
        void drawPoint(point p) const;
        void drawLine(point p0, point p1) const;

        sf::Uint8* getData() const;
};

#endif //FDF_SURFACE_HPP
