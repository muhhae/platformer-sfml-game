#pragma once

#include "lib.hpp"

namespace collider
{
    class BoxCollider 
    {
        private :
            float width;
            float height;

            struct bound
            {
                float top, left, right, bot;
            };
            bound m_bound;
        public :
            bound getBound(){return m_bound;}
            BoxCollider();

            void updatePos(sf::Vector2f position);
            void setSize(float height, float width);
            BoxCollider(float height, float width);
            

            sf::Vector2f vectorCollision(BoxCollider *other);  
    };
}