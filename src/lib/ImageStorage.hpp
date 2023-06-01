#pragma once

#include "lib.hpp"

class ImageStorage
{
    private:
        std::string state;
        std::vector<sf::Image> img;
        
    public:
        ImageStorage();
        ImageStorage(std::string state, int count, std::string dir = "Sprite/Knight", std::string extension = "gif");
        void load(std::string state, int count, std::string dir = "Sprite/Knight", std::string extension = "gif");
        sf::Image& getImg(int frame, int maxFrame = 60);
};