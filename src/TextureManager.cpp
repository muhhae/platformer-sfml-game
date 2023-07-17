#pragma once

#include "lib/TextureManager.hpp"

TextureManager::~TextureManager()
{
    
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
    texture.clear();
    int i = 0;
    while (std::filesystem::exists(dir+"/"+ CharacterName + "/" + state + "/" + std::to_string(i) + "." + extension))
    {
        // std::cout<<(dir+"/"+ CharacterName + "/" + state + "/" + std::to_string(i) + "." + extension)<<" Found"<<std::endl;
        std::unique_ptr txt = std::make_unique<sf::Texture>(sf::Texture());
        txt->loadFromFile(dir+"/"+ CharacterName + "/" + state + "/" + std::to_string(i) + "." + extension);
        texture.push_back(std::move(txt));
        i++;
    }
    // std::cout<<(dir+"/"+ CharacterName + "/" + state + "/" + std::to_string(i) + "." + extension)<<" Not Found"<<std::endl;
}
sf::Texture& TextureManager::get(int frame, int maxFrame)
{
    frame = frame / (maxFrame/texture.size());
    if (frame >= texture.size()) frame = texture.size() - 1;
    return *texture.at(frame);
}
