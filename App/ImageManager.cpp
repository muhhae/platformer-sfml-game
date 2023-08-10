#pragma once

#include "lib/ImageManager.hpp"

ImageManager::ImageManager()
{

}

ImageManager::ImageManager(std::string state,   std::string dir,std::string CharacterName, std::string extension)
{
    load(state, dir, extension);
}

void ImageManager::load(std::string state, std::string dir,std::string CharacterName, std::string extension)
{
    int i = 0;
    while (std::filesystem::exists(dir+"/"+ CharacterName + "/" + state + "/" + std::to_string(i) + "." + extension))
    {
        std::cout<<(dir+"/"+ CharacterName + "/" + state + "/" + std::to_string(i) + "." + extension)<<" Found"<<std::endl;
        img.push_back(sf::Image());
        img.at(i).loadFromFile(dir+"/"+ CharacterName + "/" + state + "/" + std::to_string(i) + "." + extension);
        i++;
    }
}
sf::Image& ImageManager::getImg(int frame, int maxFrame)
{
    frame = frame / (maxFrame/img.size());
    return img.at(frame);
}
