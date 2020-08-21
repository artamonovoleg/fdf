//
// Created by kaygalle on 21.08.2020.
//

#ifndef FDF_GUI_HPP
#define FDF_GUI_HPP

#include <SFML/Graphics.hpp>
#include "Point.hpp"

class Gui
{
    private:
        sf::Color gui_color = {50, 50, 50, 255};
    public:
        sf::Text text;
        std::unique_ptr<point[]> data;
        int width = 0;
        int height = 0;
    public:
        Gui(sf::Window &window, sf::Font &font);
        ~Gui() = default;
};

#endif //FDF_GUI_HPP
