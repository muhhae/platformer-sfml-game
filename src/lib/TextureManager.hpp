#pragma once

#include "lib.hpp"

class TextureManager
{
    private:
        std::string state;
        std::string CharacterName;
        std::vector<sf::Texture*> texture;
        
    public:
        TextureManager();
        ~TextureManager();
        TextureManager(std::string state, std::string dir = "Sprite",std::string CharacterName = "Knight", std::string extension = "gif");
        void load(std::string state, std::string dir = "Sprite",std::string CharacterName = "Knight", std::string extension = "gif");
        sf::Texture& get(int frame, int maxFrame = 100);
};