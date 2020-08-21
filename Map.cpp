//
// Created by kaygalle on 18.08.2020.
//

#include "Map.hpp"

int Map::color_count = 8;
std::unique_ptr<sf::Color[]> Map::colors = std::unique_ptr<sf::Color[]>(new sf::Color[Map::color_count] {sf::Color(133, 0, 75),
                                                                                                         sf::Color(255, 255, 255),
                                                                                                         sf::Color(255, 146, 0),
                                                                                                         sf::Color(255, 211, 0),
                                                                                                         sf::Color(18, 64, 171),
                                                                                                         sf::Color(0, 153, 153),
                                                                                                         sf::Color(166, 0, 0),
                                                                                                         sf::Color(255, 120, 0)});

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

void Map::colorize()
{
    sf::Color min_color = colors[color_set];
    sf::Color max_color = colors[color_set + 1];
    // Dont ready
    for (int i = 0; i < width * height; i++)
    {
        data[i].color = Interpolate::mix_color(min_color, max_color, Interpolate::percent(min_depth, max_depth, data[i].pos.z));
    }
    color_set+=2;
    if (color_set == color_count)
        color_set = 0;
}

