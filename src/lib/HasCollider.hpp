#pragma once
#include "Collider.hpp"

namespace collider
{
    class HasCollider
    {
        protected:
            bool isGrounded;
            std::vector<sf::Vector2f> colMove;
            collider::BoxCollider col;
        public:
            HasCollider(){}
            void collision(collider::HasCollider * other);
            BoxCollider& getCollider(){ return col;}
    };
}


