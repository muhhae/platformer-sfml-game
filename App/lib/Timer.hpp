#pragma once

#include <SFML/System/Clock.hpp>

namespace timer
{
    inline sf::Clock clock;
    inline float deltaTime;
    
    inline void update()
    {
        deltaTime = clock.restart().asSeconds();
    }
}