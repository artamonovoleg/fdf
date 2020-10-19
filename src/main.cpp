#include <vector>
#include "libsdl.hpp"
#include "Camera.hpp"
#include "Map.hpp"
#include "Gui.hpp"
#include "Renderer.hpp"
#include "Controller.hpp"


int main(int argc, char* argv[])
{
    if (argc > 1)
    {
        // Create window
        int width = 1920;
        int height = 1080;
        sdl::Window window("FDF", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height,
                           SDL_WINDOW_ALLOW_HIGHDPI);
        // window.setFullscreenMode();

        std::string folder = "./maps/";
        std::string file = argv[1];
        std::string path = folder + file;

        Camera camera(vec2i(width / 2, height / 2), vec3f(0, 0, 0), 10);
        Renderer renderer(window, camera);

        Map map(path);
        Gui gui(window);

        Controller controller(camera, map);

        while (!sdl::EventHandler::isClosed && !sdl::EventHandler::inputGetKeyDown(SDL_SCANCODE_ESCAPE))
        {
            controller.update();
            window.clear();
            renderer.drawMap(map);
            renderer.drawGui(gui);
            window.present();
        }
    }

    return 0;
}
