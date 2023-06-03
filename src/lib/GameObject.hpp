#pragma once

#include "lib.hpp"

class GameObject : public sf::Drawable
{
    private:
        sf::Sprite sprite;
        sf::RectangleShape boxCollider;    
    public :
        GameObject();
        virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};