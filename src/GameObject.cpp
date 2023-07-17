#include "lib/GameObject.hpp"

GameObject::GameObject()
{
    sprite.setPosition(0, 0);
    col.setSize(0, 0);
}

void GameObject::load(std::string dir)
{
    if (!texture.loadFromFile(dir)) return;
    
    // std::cout << "Loading " << dir << std::endl;
    sprite.setTexture(texture);
    isLoaded = true;
}

void GameObject::update()
{
    
}

void GameObject::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(sprite, states);
    col.colDraw(target);
}

