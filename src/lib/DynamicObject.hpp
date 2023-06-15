#pragma once

#include "lib.hpp"
#include "Collider.hpp"

class DynamicObject
{
    public :
        virtual void collision(collider::BoxCollider* other) = 0;
};