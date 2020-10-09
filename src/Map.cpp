//
// Created by kaygalle on 18.08.2020.
//

#include "Map.hpp"

#define COLOR_SETS_COUNT 4

#define WHITE       0xFFFFFF
#define DISCO		0x9A1F6A
#define BRICK_RED	0xC2294E
#define SUN		    0xEF8633
#define SAFFRON		0xF3AF3D

int Map::_colors[COLOR_SETS_COUNT * 2] = {DISCO, BRICK_RED, WHITE, DISCO, SUN, SAFFRON, DISCO, SUN};

Map::Map(const std::string &path)
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

    data = std::unique_ptr<Point[]>(new Point[width * height]);
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
                data[count].position.z = found;
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

    changeColor();
}

int Map::countWidth(std::string data_file)
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

int Map::countHeight(std::string data_file)
{
    int height = 0;

    for (int i = 0; data_file[i] != '\0'; i++)
    {
        if (data_file[i] == '\n')
            height++;
    }

    return height;
}

void Map::changeColor()
{
    static int current_set = 0;
    current_set %= COLOR_SETS_COUNT;

    Uint32 min_color = _colors[current_set * 2];
    Uint32 max_color = _colors[current_set * 2 + 1];

    current_set += 1;

    for (int i = 0; i < width * height; i++)
    {
        data[i].color = sdl::Color::mix_color(min_color, max_color, sdl::Color::percent(min_depth, max_depth, data[i].position.z));
    }
}