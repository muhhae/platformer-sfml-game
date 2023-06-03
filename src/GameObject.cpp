#include "lib/GameObject.hpp"

GameObject::GameObject()
{

}

void GameObject::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(sprite, states);
}

