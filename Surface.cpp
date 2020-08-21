//
// Created by kaygalle on 21.08.2020.
//

#include "Surface.hpp"

Surface::Surface(int width, int height) : _width(width), _height(height)
{
    data = std::unique_ptr<sf::Uint8[]> (new sf::Uint8 [width * height * 4]);
}

void Surface::drawPoint(point p) const
{
    if (p.pos.x >= 0 && p.pos.x < _width && p.pos.y >= 0 && p.pos.y < _height)
    {
        sf::Color rev (p.color.a, p.color.b, p.color.g, p.color.r);
        *(sf::Uint32*) (data.get() + (p.pos.x + p.pos.y * _width) * 4) = rev.toInteger();
    }
}

void Surface::drawLine(point p0, point p1) const
{
    int x, y, xe, ye;
    int x1 = p0.pos.x;
    int x2 = p1.pos.x;
    int y1 = p0.pos.y;
    int y2 = p1.pos.y;
    point p;
    int dx = x2 - x1;
    int dy = y2 - y1;
    int dx1 = abs(dx);
    int dy1 = abs(dy);
    int px = 2 * dy1 - dx1;
    int py = 2 * dx1 - dy1;
    if (dy1 <= dx1)
    {
        if (dx >= 0)
        {
            x = x1;
            y = y1;
            xe = x2;
        }
        else
        {
            x = x2;
            y = y2;
            xe = x1;
        }
        p.pos.x = x;
        p.pos.y = y;
        p.color = p0.color;
        p.color = Interpolate::mix_color(p0.color, p1.color, Interpolate::percent(p0.pos.x, p1.pos.x, p.pos.x));

        drawPoint(p);
        for (int i = 0; x < xe; i++)
        {
            x++;
            if (px < 0)
                px = px + 2 * dy1;
            else
            {
                if ((dx < 0 && dy < 0) || (dx > 0 && dy > 0))
                    y++;
                else
                    y--;
                px = px + 2 * (dy1 - dx1);
            }

            p.pos.x = x;
            p.pos.y = y;
            p.color = p0.color;
            p.color = Interpolate::mix_color(p0.color, p1.color, Interpolate::percent(p0.pos.x, p1.pos.x, p.pos.x));

            drawPoint(p);
        }
    }
    else
    {
        if (dy >= 0)
        {
            x = x1;
            y = y1;
            ye = y2;
        }
        else
        {
            x = x2;
            y = y2;
            ye = y1;
        }
        p.pos.x = x;
        p.pos.y = y;
        p.color = p0.color;
        p.color = Interpolate::mix_color(p0.color, p1.color, Interpolate::percent(p0.pos.x, p1.pos.x, p.pos.x));

        drawPoint(p);
        for (int i = 0; y < ye; i++)
        {
            y++;
            if (py <= 0)
                py = py + 2 * dx1;
            else
            {
                if ((dx < 0 && dy < 0) || (dx > 0 && dy > 0))
                    x++;
                else
                    x--;
                py = py + 2 * (dx1 - dy1);
            }
            p.pos.x = x;
            p.pos.y = y;
            p.color = p0.color;
            p.color = Interpolate::mix_color(p0.color, p1.color, Interpolate::percent(p0.pos.x, p1.pos.x, p.pos.x));

            drawPoint(p);
        }
    }
}

void Surface::clear() const
{
    sf::Color rev_black(255, 0, 0, 0);
    for (int i = 0; i < _width * _height * 4; i+=4)
    {
        *(sf::Uint32*) (data.get() + i) = rev_black.toInteger();
    }
}

sf::Uint8 *Surface::getData() const
{
    return data.get();
}
