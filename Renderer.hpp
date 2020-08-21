//
// Created by kaygalle on 21.08.2020.
//

#ifndef FDF_RENDERER_HPP
#define FDF_RENDERER_HPP

#include <SFML/Graphics.hpp>
#include "Surface.hpp"
#include "Map.hpp"
#include "Gui.hpp"
#include "Camera.hpp"
#include "Transform.hpp"

class Renderer
{
    private:
        sf::RenderWindow &_window;
        Camera &_camera;
        Surface _surface;
        sf::Texture _texture;
        sf::Sprite _sprite;
    private:
        void drawMap(Map &map);
        void drawGui(Gui &gui);

    public:
        Renderer(sf::RenderWindow &window, Camera &camera);
        ~Renderer() = default;

        void clear();
        void draw(Gui& gui, Map &map);
        void present();
};

#endif //FDF_RENDERER_HPP
