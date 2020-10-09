//
// Created by user on 09.10.2020.
//

#include "Renderer.hpp"

void Renderer::drawGui(Gui& gui)
{
    for (int i = 1; i < gui.width * gui.height; i++)
    {
        _window.drawLine(gui.data[i - 1].position.x, gui.data[i - 1].position.y, gui._color, gui.data[i].position.x, gui.data[i].position.y, gui._color);
    }
    _window.drawText(gui.text);
}

void Renderer::drawMap(Map &map)
{
    for (int y = 0; y < map.height; y++)
    {
        for (int x = 1; x < map.width; x++)
        {
            if ((x) % map.width != 0)
            {
                Point p1;
                p1.position.x = x - 1;
                p1.position.y = y;
                p1.position.z = map.data[(x - 1) + y * map.width].position.z;
                p1.color = map.data[(x - 1) + y * map.width].color;

                Point p2;
                p2.position.x = x;
                p2.position.y = y;
                p2.position.z = map.data[x + y * map.width].position.z;
                p2.color = map.data[x + y * map.width].color;

                p1.position = Transform::scaleVector(_camera, p1.position);
                p1.position = p1.position - vec3i(map.width / 2 * _camera.scale, map.height / 2 * _camera.scale, 0);
                p1.position = Transform::rotateVector(_camera, p1.position);
                p1.position = Transform::translateVector(_camera, p1.position);

                p2.position = Transform::scaleVector(_camera, p2.position);
                p2.position = p2.position - vec3i(map.width / 2 * _camera.scale, map.height / 2 * _camera.scale, 0);
                p2.position = Transform::rotateVector(_camera, p2.position);
                p2.position = Transform::translateVector(_camera, p2.position);

                _window.drawLine(p1.position.x, p1.position.y, p1.color, p2.position.x, p2.position.y, p2.color);
            }
        }
    }

    for (int y = 1; y < map.height; y++)
    {
        for (int x = 0; x < map.width; x++)
        {
            Point p1;
            p1.position.x = x;
            p1.position.y = y - 1;
            p1.position.z = map.data[x + (y - 1) * map.width].position.z;
            p1.color = map.data[x + (y - 1) * map.width].color;

            Point p2;
            p2.position.x = x;
            p2.position.y = y;
            p2.position.z = map.data[x + y * map.width].position.z;
            p2.color = map.data[x + y * map.width].color;

            p1.position = Transform::scaleVector(_camera, p1.position);
            p1.position = p1.position - vec3i(map.width / 2 * _camera.scale, map.height / 2 * _camera.scale, 0);
            p1.position = Transform::rotateVector(_camera, p1.position);
            p1.position = Transform::translateVector(_camera, p1.position);

            p2.position = Transform::scaleVector(_camera, p2.position);
            p2.position = p2.position - vec3i(map.width / 2 * _camera.scale, map.height / 2 * _camera.scale, 0);
            p2.position = Transform::rotateVector(_camera, p2.position);
            p2.position = Transform::translateVector(_camera, p2.position);
            _window.drawLine(p1.position.x, p1.position.y, p1.color, p2.position.x, p2.position.y, p2.color);
        }
    }
}