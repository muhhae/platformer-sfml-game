#pragma once
#include "Collider.hpp"

namespace collider
{
    class HasCollider
    {
        protected:
            bool isGrounded;
            sf::Vector2f colMove;
            collider::BoxCollider col;
        public:
            HasCollider();
            void collision(collider::HasCollider * other);
            BoxCollider& getCollider(){ return col;}
    };
    
    inline std::vector<std::shared_ptr<HasCollider>> hasColliderVector;

    void checkCollision();
}


