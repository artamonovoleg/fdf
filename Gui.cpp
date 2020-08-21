//
// Created by kaygalle on 21.08.2020.
//

#include "Gui.hpp"

Gui::Gui(sf::Window &window, sf::Font &font)
{
    text = sf::Text("How to use: \nMove: A, S, W, D \nRotate: I, J, K, L", font, 15);
    text.setPosition(float(window.getSize().x) / 100 * 79, float(window.getSize().y) / 100 * 5);

    width = int(window.getSize().x / 100 * 23);
    height = window.getSize().y;
    data = std::unique_ptr<point[]>(new point [width * height]);

    int window_width = window.getSize().x;

    for (int y = 0; y < height; y++)
    {
        for (int x = 0; x < width; x++)
        {
            point p;
            p.pos = vec3i (window_width - x, y, 0);
            p.color = gui_color;
            data [x + y * width] = p;
        }
    }
}