#include <iostream>
#include <cmath>
#include <memory>
#include <SFML/Graphics.hpp>
#include "Vectors.hpp"

struct point
{
    vec3i pos;
    sf::Color color;
};

class Camera
{
    public:
        vec3f rotation = {0, 0, 0};
        vec2i position = {0, 0};
        int scale = 0;
    public:
        Camera(vec2i position, vec3f rotation, int scale) : position(position), rotation(rotation), scale(scale) {};
};

class Transform
{
    public:
        static vec3i scaleVector(Camera &camera, vec3i vec)
        {
            vec3i ret = vec;

            ret.x *= camera.scale;
            ret.y *= camera.scale;
            ret.z *= camera.scale;

            return ret;
        }

        static vec3i rotateVector(Camera &camera, vec3i vec)
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

        static vec3i translateVector(Camera &camera, vec3i vec)
        {
            vec3i ret = vec;

            ret.x += camera.position.x;
            ret.y += camera.position.y;

            return ret;
        }
};

class Controller
{
    private:
        sf::RenderWindow &_window;
        Camera &_camera;
    public:
        Controller(sf::RenderWindow &window, Camera &camera) : _window(window), _camera(camera) {};
        void handleInput()
        {
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
                _camera.position.x -= 1;
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
                _camera.position.x += 1;
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
                _camera.position.y -= 1;
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
                _camera.position.y += 1;

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::J))
                _camera.rotation.y -= 0.1f;
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::L))
                _camera.rotation.y += 0.1f;
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::I))
                _camera.rotation.x += 0.1f;
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::K))
                _camera.rotation.x -= 0.1f;

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Dash))
                _camera.scale -= 1;
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Equal))
                _camera.scale += 1;
        }
};

class Surface
{
    private:
        int _width = 0;
        int _height = 0;
    public:
        std::unique_ptr<sf::Uint8[]> data;
    public:
        Surface(int width, int height) : _width(width), _height(height)
        {
            data = std::unique_ptr<sf::Uint8[]> (new sf::Uint8 [width * height * 4]);
        };

        inline void drawPoint(point p) const
        {
            if (p.pos.x >= 0 && p.pos.x < _width && p.pos.y >= 0 && p.pos.y < _height)
            {
                data[(p.pos.x + p.pos.y * _width) * 4] = p.color.r;
                data[(p.pos.x + p.pos.y * _width) * 4 + 1] = p.color.g;
                data[(p.pos.x + p.pos.y * _width) * 4 + 2] = p.color.b;
                data[(p.pos.x + p.pos.y * _width) * 4 + 3] = p.color.a;
            }
        }

        inline void drawLine(point p0, point p1) const
        {
            int x, y, xe, ye;
            int x1 = p0.pos.x;
            int x2 = p1.pos.x;
            int y1 = p0.pos.y;
            int y2 = p1.pos.y;
            point p;
            int dx = x2 - x1;
            int dy = y2 - y1;
            int dx1 = abs(dx);
            int dy1 = abs(dy);
            int px = 2 * dy1 - dx1;
            int py = 2 * dx1 - dy1;
            if (dy1 <= dx1)
            {
                if (dx >= 0)
                {
                    x = x1;
                    y = y1;
                    xe = x2;
                }
                else
                {
                    x = x2;
                    y = y2;
                    xe = x1;
                }
                p.pos.x = x;
                p.pos.y = y;
                p.color = p0.color;

                drawPoint(p);
                for (int i = 0; x < xe; i++)
                {
                    x++;
                    if (px < 0)
                        px = px + 2 * dy1;
                    else
                    {
                        if ((dx < 0 && dy < 0) || (dx > 0 && dy > 0))
                            y++;
                        else
                            y--;
                        px = px + 2 * (dy1 - dx1);
                    }

                    p.pos.x = x;
                    p.pos.y = y;
                    p.color = p0.color;

                    drawPoint(p);
                }
            }
            else
            {
                if (dy >= 0)
                {
                    x = x1;
                    y = y1;
                    ye = y2;
                }
                else
                {
                    x = x2;
                    y = y2;
                    ye = y1;
                }
                p.pos.x = x;
                p.pos.y = y;
                p.color = p0.color;

                drawPoint(p);
                for (int i = 0; y < ye; i++)
                {
                    y++;
                    if (py <= 0)
                        py = py + 2 * dx1;
                    else
                    {
                        if ((dx < 0 && dy < 0) || (dx > 0 && dy > 0))
                            x++;
                        else
                            x--;
                        py = py + 2 * (dx1 - dy1);
                    }
                    p.pos.x = x;
                    p.pos.y = y;
                    p.color = p0.color;

                    drawPoint(p);
                }
            }
        }

        inline void clear() const
        {
            for (int i = 0; i < _width * _height * 4; i++)
            {
                data[i] = 0;
            }
        }

        inline void clear(sf::Color color) const
        {
            for (int i = 0; i < _width * _height; i++)
            {
                //((sf::Uint32 *)data.get())[i] = color.toInteger();
            }
        }

        sf::Uint8* getData() const
        {
            return data.get();
        }
};

class Map
{
    private:
        static int countWidth(std::string data_file)
        {
            /* Count real space between numbers and add 1 at the end to know how much numbers in line */

            int width = 0;

            for (int i = 0; data_file[i] != '\n'; i++ )
            {
                if (data_file [i] == ' ' && data_file [i - 1] != ' ')
                {
                    width++;
                }
            }

            width++;

            return width;
        }
        static int countHeight(std::string data_file)
        {
            int height = 0;

            for (int i = 0; data_file[i] != '\0'; i++)
            {
                if (data_file[i] == '\n')
                    height++;
            }

            return height;
        }
    public:
        int width = 0;
        int height = 0;
        int min_depth = 0;
        int max_depth = 0;
        std::unique_ptr<point[]> data = std::unique_ptr<point[]>(nullptr);
    public:
        explicit Map(const std::string& path)
        {
            std::ifstream file ( path );
            std::string line;
            std::string data_str;

            if (file.is_open())
            {
                while (getline( file, line ))
                {
                    data_str += line;
                    data_str += "\n";
                }
            }
            else
            {
                std::cerr << "Failed to read map" << std::endl;
                exit(-1);
            }
            width = countWidth( data_str );
            height = countHeight( data_str );

            data = std::unique_ptr<point[]>(new point[width * height]);
            int count = 0;
            std::stringstream ss;

            ss << data_str;

            std::string temp;
            int found;
            while (!ss.eof())
            {
                ss >> temp;
                if (std::stringstream(temp) >> found)
                {
                    if (count != width * height)       // LAST SYMBOL IS '\0'
                        data[count].pos.z = found;
                    if (count == 0)
                    {
                        max_depth = found;
                        min_depth = found;
                    }

                    if (found > max_depth)
                        max_depth = found;
                    if (found < min_depth)
                        min_depth = found;
                    count++;
                }
            }
        }
        void colorize(sf::Color min_color, sf::Color max_color) const
        {
            // Dont ready
            for (int i = 0; i < width * height; i++)
            {
                data[i].color = min_color;
            }
        }
        ~Map() = default;
};

class Gui
{
    private:
        sf::Color gui_color = {50, 50, 50, 255};
    public:
        sf::Text text;
        std::unique_ptr<point[]> data;
        int _width = 0;
        int _height = 0;
    public:
        Gui(sf::Window &window, sf::Font &font)
        {
            text = sf::Text("How to use: \nMove: A, S, W, D \nRotate: I, J, K, L", font, 15);
            text.setPosition(window.getSize().x / 100 * 85, window.getSize().y / 100 * 5);

            _width = window.getSize().x / 100 * 23;
            _height = window.getSize().y;
            data = std::unique_ptr<point[]>(new point [_width * _height]);

            int window_width = window.getSize().x;

            for (int y = 0; y < _height; y++)
            {
                for (int x = 0; x < _width; x++)
                {
                    point p;
                    p.pos = vec3i (window_width - x, y, 0);
                    p.color = gui_color;
                    data [x + y * _width] = p;
                }
            }
        }
};

class Renderer
{
    private:
        sf::RenderWindow &_window;
        Camera &_camera;
        sf::Texture texture;
        sf::Sprite sprite;
    public:
        Surface surface;

        Renderer(sf::RenderWindow &window, Camera &camera) : _window(window), _camera(camera), surface(window.getSize().x, window.getSize().y){};
};

void drawMap(Surface &_surface, Camera &_camera, Map &map)
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
void drawGui(Gui &gui, Surface &_surface)
{
    for (int i = 0; i < gui._width * gui._height; i++)
    {
        _surface.drawPoint(gui.data[i]);
    }
}

int main()
{
    int width = 960;
    int height = 540;
    sf::RenderWindow window(sf::VideoMode(width, height), "title");
    window.setPosition(sf::Vector2i(0, 0));

    sf::Font font;
    if (!font.loadFromFile("./Roboto-Medium.ttf"))
        return EXIT_FAILURE;

    sf::Texture texture;
    texture.create(width, height);
    sf::Sprite sprite(texture); // need to draw the texture on screen

    Camera camera(vec2i(width / 2, height / 2), vec3f(0, 0, 0), 10);
    Controller controller(window, camera);

    Surface surface(width, height);
    Map map("./maps/42.fdf");
    Gui gui(window, font);
    map.colorize(sf::Color(255, 0, 0, 255), sf::Color(255, 0, 0));

    point test;
    test.pos = vec3i(40, 40, 0);
    test.color = sf::Color(0, 255, 0, 255);

    Renderer renderer(window, camera);

    while (window.isOpen() && !sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
    {
        sf::Event event{};
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        // Controll
        controller.handleInput();
        //

        window.clear();
        renderer.surface.clear();

        drawMap(renderer.surface, camera, map);
        drawGui(gui, renderer.surface);
        texture.update(renderer.surface.getData());
        window.draw(sprite);
        window.draw(gui.text);

        window.display();
    }


    return 0;
}


//int main()
//{
//    sf::Uint8 array[4];
//    sf::Color color(1, 2, 3, 4);
//    array[0] = color.r;
//    array[1] = color.g;
//    array[2] = color.b;
//    array[3] = color.a;
//    for (int i = 0; i < 4; i++)
//    {
//        std::cout << (int)array[i] << std::endl;
//    }
//    std::cout << *(sf::Uint32*)array << std::endl << (int)*(sf::Uint8*)array << std::endl;
//    *(sf::Uint32*)array = int (0x01020304);
//    std::cout << *(sf::Uint32*)array << std::endl << (int)*(sf::Uint8*)array << std::endl;
//    for (int i = 0; i < 4; i++)
//    {
//        std::cout << (int)array[i] << std::endl;
//    }
//
//}
