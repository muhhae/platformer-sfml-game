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
    std::list<sf::Texture>::iterator it = texture.begin();

    int i = 0;

    while (std::filesystem::exists(dir+"/"+ CharacterName + "/" + state + "/" + std::to_string(i) + "." + extension))
    {
        std::cout<<(dir+"/"+ CharacterName + "/" + state + "/" + std::to_string(i) + "." + extension)<<" Found"<<std::endl;
        texture.push_back(sf::Texture());
        (*it).loadFromFile(dir+"/"+ CharacterName + "/" + state + "/" + std::to_string(i) + "." + extension);
        i++;
        std::advance(it, 1);
    }
    std::cout<<(dir+"/"+ CharacterName + "/" + state + "/" + std::to_string(i) + "." + extension)<<" Not Found"<<std::endl;
}
sf::Texture& TextureManager::get(int frame, int maxFrame)
{
    std::cout<<"Masuk get"<<std::endl;
    // std::cout<<frame<<" = "<<frame << " / " << maxFrame << " / " <<texture.size()<<std::endl;
    std::list<sf::Texture>::iterator it = texture.begin();

    frame = frame / (maxFrame/texture.size());
    if (frame >= texture.size()) frame = texture.size() - 1;

    std::cout<<"Not Advance"<<std::endl;

    std::advance(it, frame);

    std::cout<<"Advance"<<std::endl;
    // std::cout<<"frame : "<<frame<<std::endl;
    return (*it);
}
