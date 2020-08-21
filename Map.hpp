//
// Created by kaygalle on 18.08.2020.
//

#ifndef SFML_MAP_HPP
#define SFML_MAP_HPP

#include <iostream>
#include <memory>
#include <SFML/Graphics.hpp>

#include "Point.hpp"
#include "Interpolate.hpp"

class Map
{
    private:
        static int countWidth(std::string data_file);
        static int countHeight(std::string data_file);
    private:
        static std::unique_ptr<sf::Color[]> colors;
        static int color_count;
        int color_set = 0;
    public:
        int width = 0;
        int height = 0;
        int min_depth = 0;
        int max_depth = 0;
        std::unique_ptr<point[]> data = std::unique_ptr<point[]>(nullptr);
    public:
        explicit Map(const std::string& path);
        ~Map() = default;

        void colorize();
};

#endif //SFML_MAP_HPP
