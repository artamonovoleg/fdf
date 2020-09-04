//
// Created by kaygalle on 18.08.2020.
//

#pragma once

#include <iostream>
#include <memory>

#include "libsdl.hpp"
#include "Point.hpp"

class Map
{
    private:
        static int countWidth(std::string data_file);
        static int countHeight(std::string data_file);
    public:
        int width = 0;
        int height = 0;
        int min_depth = 0;
        int max_depth = 0;
    public:
        std::unique_ptr<Point[]> data = std::unique_ptr<Point[]>(nullptr);
        explicit Map(const std::string& path);
        ~Map() = default;

        void colorize();
};
