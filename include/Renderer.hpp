//
// Created by user on 09.10.2020.
//

#ifndef FDF_RENDERER_HPP
#define FDF_RENDERER_HPP

#include "libsdl.hpp"
#include "Transform.hpp"
#include "Camera.hpp"
#include "Gui.hpp"
#include "Map.hpp"

class Renderer
{
    private:
        sdl::Window &_window;
        Camera &_camera;
    public:
        Renderer(sdl::Window &w, Camera &c) : _window(w), _camera(c) {};

        void drawGui(Gui& gui);
        void drawMap(Map &map);
};

#endif //FDF_RENDERER_HPP
