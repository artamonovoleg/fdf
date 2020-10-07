//
// Created by kaygalle on 21.08.2020.
//

#include "../include/Transform.hpp"

vec3i Transform::scaleVector(Camera &camera, vec3i vec)
{
    vec3i ret = vec;

    ret.x *= camera.scale;
    ret.y *= camera.scale;
    ret.z *= camera.scale;

    return ret;
}

vec3i Transform::rotateVector(Camera &camera, vec3i vec)
{
    vec3i ret = vec;

    float x;
    float y;
    float z;

    x = vec.x;
    y = vec.y;
    z = vec.z;

    ret.x = cos(camera.rotation.y) * x + sin(camera.rotation.y) * z;
    ret.z = -sin(camera.rotation.y) * x + cos(camera.rotation.y) * z;
    y = vec.y;
    z = ret.z;
    ret.y = cos(camera.rotation.x) * y - sin(camera.rotation.x) * z;
    ret.z = sin(camera.rotation.x) * y + cos(camera.rotation.x) * z;
    x = ret.x;
    y = ret.y;
    ret.x = cos(camera.rotation.z) * x - sin(camera.rotation.z) * y;
    ret.y = sin(camera.rotation.z) * x + cos(camera.rotation.z) * y;

    return ret;
}

vec3i Transform::translateVector(Camera &camera, vec3i vec)
{
    vec3i ret = vec;

    ret.x += camera.position.x;
    ret.y += camera.position.y;

    return ret;
}
