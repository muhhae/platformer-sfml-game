#include "lib/Collider.hpp"
#include "lib/HasCollider.hpp"

void collider::HasCollider::collision(collider::HasCollider* other)
{
    sf::Vector2f move = col.vectorCollision(&other->getCollider());

    if (!isGrounded)
    {
        if (move.y < 0) isGrounded = true;
        else isGrounded = false;
    }

    if (move.y > 0 && isGrounded) return;

    colMove.push_back(move);
}