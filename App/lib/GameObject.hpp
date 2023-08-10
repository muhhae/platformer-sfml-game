#pragma once

#include "lib.hpp"
#include "Collider.hpp"
#include "HasCollider.hpp"
 
class GameObject : public sf::Drawable, public collider::HasCollider
{
    protected:
        sf::Sprite sprite;
        sf::Texture texture;
        bool isLoaded;
        bool isSolid = true;
    public :
        GameObject();
        virtual void load(std::string dir);
        virtual void update();
        virtual sf::Sprite& getSprite() { return sprite; }
        virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
        virtual void solid(bool isSolid) { this->isSolid = isSolid; };
};