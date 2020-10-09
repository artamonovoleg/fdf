//
// Created by user on 09.10.2020.
//

#include "Controller.hpp"

Controller::Controller(Camera &camera, Map &map): _camera(camera), _map(map)
{
    sdl::EventHandler::initialize();
}

void Controller::camera_control()
{
    if (sdl::EventHandler::inputGetKey(SDL_SCANCODE_A))
        _camera.position.x -= 1;
    if (sdl::EventHandler::inputGetKey(SDL_SCANCODE_D))
        _camera.position.x += 1;
    if (sdl::EventHandler::inputGetKey(SDL_SCANCODE_W))
        _camera.position.y -= 1;
    if (sdl::EventHandler::inputGetKey(SDL_SCANCODE_S))
        _camera.position.y += 1;
    if (sdl::EventHandler::inputGetKey(SDL_SCANCODE_J))
        _camera.rotation.y -= 0.1f;
    if (sdl::EventHandler::inputGetKey(SDL_SCANCODE_L))
        _camera.rotation.y += 0.1f;
    if (sdl::EventHandler::inputGetKey(SDL_SCANCODE_I))
        _camera.rotation.x += 0.1f;
    if (sdl::EventHandler::inputGetKey(SDL_SCANCODE_K))
        _camera.rotation.x -= 0.1f;
    if (sdl::EventHandler::inputGetKey(SDL_SCANCODE_MINUS))
        _camera.scale -= 1;
    if (sdl::EventHandler::inputGetKey(SDL_SCANCODE_EQUALS))
        _camera.scale += 1;
}

void Controller::update()
{
    sdl::EventHandler::update();
    camera_control();
    map_control();
}

void Controller::map_control()
{
    if (sdl::EventHandler::inputGetKeyDown(SDL_SCANCODE_C))
        _map.changeColor();
}

