#pragma once

#include "lib.hpp"

class ImageManager
{
    private:
        std::string state;
        std::string CharacterName;
        std::vector<sf::Image> img;
        
    public:
        ImageManager();
        ImageManager(std::string state, std::string dir = "Sprite",std::string CharacterName = "Knight", std::string extension = "gif");
        void load(std::string state, std::string dir = "Sprite",std::string CharacterName = "Knight", std::string extension = "gif");
        sf::Image& getImg(int frame, int maxFrame = 60);
};