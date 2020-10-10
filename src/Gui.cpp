//
// Created by user on 09.10.2020.
//

#include "Gui.hpp"

Gui::Gui(sdl::Window &window) : font("Roboto-Medium.ttf", 24), text(font, "How to use: \nMove: A, S, W, D \nRotate: I, J, K, L \nChange color: c\n ", SDL_Color {255, 255, 255})
{
    int window_width = window.getWidth();

    width = window_width / 100 * 20;
    height = window.getHeight();

    data = std::unique_ptr<Point[]>(new Point[width * height]);
    text.setPos(window_width - width + 20, height / 100 * 5);

    for (int y = 0; y < height; y++)
    {
        for (int x = 0; x < width; x++)
        {
            data[x + y * width] = Point {vec3i (window_width - x, y, 0), _color};
        }
    }
}
