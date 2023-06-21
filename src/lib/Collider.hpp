#pragma once

#include "lib.hpp"

namespace collider
{
    class BoxCollider 
    {
        private :
            float width;
            float height;

            float weight = 1;

            struct bound
            {
                float top, left, right, bot;
            };

            sf::RectangleShape box;

            bound m_bound;
            bool kinematic = true;


        public :
            bound getBound(){return m_bound;}
            float getWeight(){return weight;}

            void updatePos(sf::Vector2f position);
            void setSize(float height, float width);
            void setWeight(float weight = 1);
            void colDraw(sf::RenderTarget& target) const;

            void debug(bool showOutline = true);
            void setType(bool kinematic);
            bool getType(){return kinematic;}
            
            BoxCollider(float height = 150, float width = 100);

            sf::Vector2f vectorCollision(BoxCollider *other);  
    };
}