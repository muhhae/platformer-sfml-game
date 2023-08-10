#pragma once

#include "lib/TextureManager.hpp"

TextureManager::~TextureManager()
{
    for (auto & i : texture) delete i;
    texture.clear();
}

TextureManager::TextureManager()
{

}

TextureManager::TextureManager(std::string state, std::string dir,std::string CharacterName, std::string extension)
{
    load(state, dir, CharacterName ,extension);
}

void TextureManager::load(std::string state, std::string dir,std::string CharacterName, std::string extension)
{
    for (auto* i : texture) delete i;
    texture.clear();
    
    int i = 0;
    while (std::filesystem::exists(dir+"/"+ CharacterName + "/" + state + "/" + std::to_string(i) + "." + extension))
    {
        sf::Texture* txt = new sf::Texture();
        txt->loadFromFile(dir+"/"+ CharacterName + "/" + state + "/" + std::to_string(i) + "." + extension);
        texture.push_back(std::move(txt));
        i++;
    }
}
sf::Texture& TextureManager::get(int& frame)
{
    if (frame >= texture.size()) frame = 0;
    return *texture.at(frame);
}
