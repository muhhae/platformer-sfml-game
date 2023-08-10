#include "lib/Collider.hpp"
#include "lib/HasCollider.hpp"

#include <cmath>

namespace collider {

    HasCollider::HasCollider() {
        hasColliderVector.push_back(std::shared_ptr<HasCollider>(this));
    }

    void HasCollider::collision(collider::HasCollider* other)
    {
        if (!other->getCollider().getSolid() || !getCollider().getSolid()) return;  

        sf::Vector2f move = col.vectorCollision(&other->getCollider());

        if (!isGrounded)
        {
            if (move.y < 0) isGrounded = true;
            else isGrounded = false;
        }

        if (abs(colMove.x) < abs(move.x)) colMove.x = move.x;
        if (abs(colMove.y) < abs(move.y)) colMove.y = move.y;  
    }

    void checkCollision()
    {
        for (int i = 0; i < collider::hasColliderVector.size(); i++)
        {
            if (collider::hasColliderVector.at(i)->getCollider().isKinematic() == true) continue;

            for (int j = 0; j < collider::hasColliderVector.size(); j++)
            {
                if (i == j) continue;

                collider::hasColliderVector.at(i)->collision(collider::hasColliderVector.at(j).get());
            }
        }
    }


}