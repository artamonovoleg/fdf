//
// Created by kaygalle on 21.08.2020.
//

#include "Renderer.hpp"

Renderer::Renderer(sf::RenderWindow &window, Camera &camera)
        : _window(window), _camera(camera), _surface(window.getSize().x, window.getSize().y)
{
    _texture.create(window.getSize().x, window.getSize().y);
    _sprite = sf::Sprite(_texture);
}

void Renderer::drawMap(Map &map)
{
    for (int y = 0; y < map.height; y++)
    {
        for (int x = 1; x < map.width; x++)
        {
            if ((x) % map.width != 0)
            {
                point p1;
                p1.pos.x = x - 1;
                p1.pos.y = y;
                p1.pos.z = map.data[(x - 1) + y * map.width].pos.z;
                p1.color = map.data[(x - 1) + y * map.width].color;

                point p2;
                p2.pos.x = x;
                p2.pos.y = y;
                p2.pos.z = map.data[x + y * map.width].pos.z;
                p2.color = map.data[x + y * map.width].color;

                p1.pos = Transform::scaleVector(_camera, p1.pos);
                p1.pos = p1.pos - vec3i(map.width / 2 * _camera.scale, map.height / 2 * _camera.scale, 0);
                p1.pos = Transform::rotateVector(_camera, p1.pos);
                p1.pos = Transform::translateVector(_camera, p1.pos);

                p2.pos = Transform::scaleVector(_camera, p2.pos);
                p2.pos = p2.pos - vec3i(map.width / 2 * _camera.scale, map.height / 2 * _camera.scale, 0);
                p2.pos = Transform::rotateVector(_camera, p2.pos);
                p2.pos = Transform::translateVector(_camera, p2.pos);

                _surface.drawLine(p1, p2);
            }
        }
    }

    for (int y = 1; y < map.height; y++)
    {
        for (int x = 0; x < map.width; x++)
        {
            point p1;
            p1.pos.x = x;
            p1.pos.y = y - 1;
            p1.pos.z = map.data[x + (y - 1) * map.width].pos.z;
            p1.color = map.data[x + (y - 1) * map.width].color;

            point p2;
            p2.pos.x = x;
            p2.pos.y = y;
            p2.pos.z = map.data[x + y * map.width].pos.z;
            p2.color = map.data[x + y * map.width].color;

            p1.pos = Transform::scaleVector(_camera, p1.pos);
            p1.pos = p1.pos - vec3i(map.width / 2 * _camera.scale, map.height / 2 * _camera.scale, 0);
            p1.pos = Transform::rotateVector(_camera, p1.pos);
            p1.pos = Transform::translateVector(_camera, p1.pos);

            p2.pos = Transform::scaleVector(_camera, p2.pos);
            p2.pos = p2.pos - vec3i(map.width / 2 * _camera.scale, map.height / 2 * _camera.scale, 0);
            p2.pos = Transform::rotateVector(_camera, p2.pos);
            p2.pos = Transform::translateVector(_camera, p2.pos);
            _surface.drawLine(p1, p2);
        }
    }
}

void Renderer::drawGui(Gui &gui)
{
    for (int i = 0; i < gui.width * gui.height; i++)
    {
        _surface.drawPoint(gui.data[i]);
    }
}

void Renderer::clear()
{
    _window.clear();
    _surface.clear();
}

void Renderer::draw(Gui &gui, Map &map)
{
    drawMap(map);
    drawGui(gui);
    _texture.update(_surface.getData());
    _window.draw(_sprite);
    _window.draw(gui.text);
}

void Renderer::present()
{
    _window.display();
}
