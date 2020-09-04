#include "libsdl.hpp"
#include "Camera.hpp"
#include "Map.hpp"
#include "Point.hpp"
#include "Transform.hpp"




class Renderer
{
    private:
        sdl::Window &_window;
        Camera &_camera;
    public:
        Renderer(sdl::Window &w, Camera &c) : _window(w), _camera(c) {};

        // void drawPoint(Point p)
        // {
        //     _window.putPixel(p.position.x, p.position.y, p.color);
        // }

        void drawMap(Map &map)
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
};

int main(int argc, char * argv[])
{
    // Create window
    int width = 1920;
    int height = 1080;
    sdl::Window window("FDF", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, SDL_WINDOW_ALLOW_HIGHDPI);
    
    sdl::EventHandler::initialize();


        Map map("./maps/42.fdf");
        map.colorize();
        Camera camera(vec2i(0, 0), vec3f(0,0,0), 10);
        Renderer renderer(window, camera);
    while (!sdl::EventHandler::isClosed)
    {
        sdl::EventHandler::update();
        camera.updateCameraVectors();

        window.clear();
        renderer.drawMap(map);
        // window.putPixel(width / 2, height / 2, 0XFFFF00);
        // window.drawLine(0, 0, 0xFF00FF, width, height, 0X00FFFF);
        window.present();
    }

    return 0;
}
