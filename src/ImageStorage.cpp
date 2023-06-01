#pragma once

#include "lib/ImageStorage.hpp"

ImageStorage::ImageStorage()
{

}

ImageStorage::ImageStorage(std::string state, int count, std::string dir, std::string extension)
{
    load(state, count, dir, extension);
}

void ImageStorage::load(std::string state, int count, std::string dir, std::string extension)
{
    for (int i = 0; i < count; i++)
    {
        img.push_back(sf::Image());
        img.at(i).loadFromFile(dir + "/" + state + "/" + std::to_string(i) + "." + extension);
    }
}
sf::Image& ImageStorage::getImg(int frame)
{
    return img.at(frame);
}
