//
// Created by kaygalle on 21.08.2020.
//

#include "Camera.hpp"

Camera::Camera(vec2i position, vec3f rotation, int scale) :
        position(position), rotation(rotation), scale(scale) {}

void Camera::updateCameraVectors()
{
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
        position.x -= 1;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
        position.x += 1;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
        position.y -= 1;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
        position.y += 1;

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::J))
        rotation.y -= 0.1f;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::L))
        rotation.y += 0.1f;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::I))
        rotation.x += 0.1f;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::K))
        rotation.x -= 0.1f;

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Dash))
        scale -= 1;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Equal))
        scale += 1;
}

