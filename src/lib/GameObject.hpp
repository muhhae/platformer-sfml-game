#pragma once

#include "lib.hpp"

class GameObject : public sf::Drawable
{
    private:
           
    public :
        GameObject();
        virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};