//
// Created by kaygalle on 21.08.2020.
//

#ifndef FDF_CAMERA_HPP
#define FDF_CAMERA_HPP

#include <SFML/Graphics.hpp>
#include "Vectors.hpp"

class Camera
{
    public:
        vec3f rotation = {0, 0, 0};
        vec2i position = {0, 0};
        int scale = 0;
    public:
        Camera(vec2i position, vec3f rotation, int scale);
        ~Camera() = default;

        void updateCameraVectors();
};


#endif //FDF_CAMERA_HPP
