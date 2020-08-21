//
// Created by kaygalle on 21.08.2020.
//

#ifndef FDF_TRANSFORM_HPP
#define FDF_TRANSFORM_HPP

#include "Vectors.hpp"
#include "Camera.hpp"
#include <cmath>

class Transform
{
    public:
        static vec3i scaleVector(Camera &camera, vec3i vec);
        static vec3i rotateVector(Camera &camera, vec3i vec);
        static vec3i translateVector(Camera &camera, vec3i vec);
};

#endif //FDF_TRANSFORM_HPP
