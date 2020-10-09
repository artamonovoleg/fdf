//
// Created by user on 09.10.2020.
//

#ifndef FDF_CONTOLLER_HPP
#define FDF_CONTOLLER_HPP

#include "libsdl.hpp"
#include "Camera.hpp"
#include "Map.hpp"

class Controller
{
    private:
        Camera& _camera;
        Map& _map;

        void camera_control();
        void map_control();
    public:
        Controller(Camera& camera, Map& map);
        ~Controller() = default;
        void update();
};

#endif //FDF_CONTOLLER_HPP
