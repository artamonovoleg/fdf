//
// Created by kaygalle on 21.08.2020.
//

#include "../include/Camera.hpp"

Camera::Camera(vec2i position, vec3f rotation, int scale) :
        position(position), rotation(rotation), scale(scale) {}

void Camera::updateCameraVectors()
{
    if (sdl::EventHandler::inputGetKey(SDL_SCANCODE_A))
        position.x -= 1;
    if (sdl::EventHandler::inputGetKey(SDL_SCANCODE_D))
        position.x += 1;
    if (sdl::EventHandler::inputGetKey(SDL_SCANCODE_W))
        position.y -= 1;
    if (sdl::EventHandler::inputGetKey(SDL_SCANCODE_S))
        position.y += 1;
    if (sdl::EventHandler::inputGetKey(SDL_SCANCODE_J))
        rotation.y -= 0.1f;
    if (sdl::EventHandler::inputGetKey(SDL_SCANCODE_L))
        rotation.y += 0.1f;
    if (sdl::EventHandler::inputGetKey(SDL_SCANCODE_I))
        rotation.x += 0.1f;
    if (sdl::EventHandler::inputGetKey(SDL_SCANCODE_K))
        rotation.x -= 0.1f;
    if (sdl::EventHandler::inputGetKey(SDL_SCANCODE_MINUS))
        scale -= 1;
    if (sdl::EventHandler::inputGetKey(SDL_SCANCODE_EQUALS))
        scale += 1;
}

