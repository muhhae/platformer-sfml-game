#pragma once

#include "lib/TextureManager.hpp"

TextureManager::TextureManager()
{

}

TextureManager::TextureManager(std::string state, std::string dir,std::string CharacterName, std::string extension)
{
    load(state, dir, extension);
}

void TextureManager::load(std::string state, std::string dir,std::string CharacterName, std::string extension)
{
    int i = 0;
    while (std::filesystem::exists(dir+"/"+ CharacterName + "/" + state + "/" + std::to_string(i) + "." + extension))
    {
        std::cout<<(dir+"/"+ CharacterName + "/" + state + "/" + std::to_string(i) + "." + extension)<<" Found"<<std::endl;
        texture.push_back(new sf::Texture());
        texture.at(i)->loadFromFile(dir+"/"+ CharacterName + "/" + state + "/" + std::to_string(i) + "." + extension);
        i++;
    }
    std::cout<<(dir+"/"+ CharacterName + "/" + state + "/" + std::to_string(i) + "." + extension)<<" Not Found"<<std::endl;
}
sf::Texture* TextureManager::get(int frame, int maxFrame)
{
    // std::cout<<frame<<" = "<<frame << " / " << maxFrame << " / " <<texture.size()<<std::endl;
    frame = frame / (maxFrame/texture.size());
    if (frame >= texture.size()) frame = texture.size() - 1;
    // std::cout<<"frame : "<<frame<<std::endl;
    return texture.at(frame);
}
