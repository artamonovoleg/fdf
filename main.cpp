#include <iostream>
#include <cmath>
#include <SFML/Graphics.hpp>
#include "Vectors.hpp"
#include "Camera.hpp"
#include "Map.hpp"
#include "Gui.hpp"
#include "Renderer.hpp"

int main(int argc, char * argv[])
{
    if (argc > 1)
    {
        // Create window
        int width = 800;
        int height = 600;
        sf::RenderWindow window(sf::VideoMode(width, height), "title");
        window.setPosition(sf::Vector2i(0, 0));

        // Load font for gui //
        sf::Font font;
        if (!font.loadFromFile("./Roboto-Medium.ttf"))
            return EXIT_FAILURE;

        // Initialize camera //
        Camera camera(vec2i(width / 2, height / 2), vec3f(0, 0, 0), 10);

        // Load map from file //
        std::string map_folder = "./maps/";
        std::string map_name = std::string (argv[1]);
        Map map(map_folder + map_name);
        map.colorize();

        // Create GUI //
        Gui gui(window, font);

        // Create renderer for draw gui and map //
        Renderer renderer(window, camera);

        while (window.isOpen() && !sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
        {
            // Check Input //
            sf::Event event{};
            while (window.pollEvent(event))
            {
                if (event.type == sf::Event::Closed)
                    window.close();
                if (event.type == sf::Event::KeyReleased)
                    if (event.key.code == sf::Keyboard::C)
                        map.colorize();
            }

            // Update position of camera //
            camera.updateCameraVectors();

            // Renderer loop //
            renderer.clear();
            renderer.draw(gui, map);
            renderer.present();
        }
    }

    return 0;
}
