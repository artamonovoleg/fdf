//
// Created by user on 09.10.2020.
//

#ifndef FDF_GUI_HPP
#define FDF_GUI_HPP

#include <memory>
#include "libsdl.hpp"
#include "Point.hpp"

class Gui
{
    private:
    public:
        std::unique_ptr<Point[]> data = std::unique_ptr<Point[]>(nullptr);
        sdl::Font font;
        sdl::Text text;
        int width = 0;
        int height = 0;
        Uint32 _color = 0x0F0F0F;

        Gui(sdl::Window& window);
};

#endif //FDF_GUI_HPP
