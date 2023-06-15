#include "lib/Collider.hpp"

namespace collider
{
    void BoxCollider::colDraw(sf::RenderTarget& target) const
    {
        target.draw(box);
    }

    BoxCollider::BoxCollider(float height, float width)
    {
        this->height = height;
        this->width = width;    

        box.setSize(sf::Vector2f(width, height));
        box.setOrigin(width/2, height/2);
        box.setFillColor(sf::Color(0));
        box.setOutlineColor(sf::Color().Black);
    }

    void BoxCollider::debug(bool showOutline)
    {
        box.setOutlineThickness(3 * showOutline);
    }

    void BoxCollider::setType(bool kinematic)
    {
        this->kinematic = kinematic;
    }

    void BoxCollider::updatePos(sf::Vector2f position)
    {
        box.setPosition(position);

        m_bound.top = position.y - height/2; 
        m_bound.bot = position.y + height/2;
        m_bound.left = position.x - width/2;
        m_bound.right = position.x + width/2;
    }
    void BoxCollider::setSize(float height, float width)
    {
        this->height = height;
        this->width = width;

        box.setSize(sf::Vector2f(width, height));
        box.setOrigin(width/2, height/2);
    }

    void BoxCollider::setWeight(float weight)
    {
        this->weight = weight;
    }

    sf::Vector2f BoxCollider::vectorCollision(BoxCollider *other)
    {

        sf::Vector2f result;
        sf::Vector2f temp;

        bool top_overlap = m_bound.top >= other->getBound().top && m_bound.top <= other->getBound().bot;
        bool bot_overlap = m_bound.bot >= other->getBound().top && m_bound.bot <= other->getBound().bot;
        bool left_overlap = m_bound.left >= other->getBound().left && m_bound.left <= other->getBound().right;
        bool right_overlap = m_bound.right >= other->getBound().left && m_bound.right <= other->getBound().right;

        bool x_overlap = right_overlap || left_overlap;
        bool y_overlap = top_overlap || bot_overlap;

        if (x_overlap)
        {
            if (top_overlap) 
            {
                result.y = abs(m_bound.top - other->getBound().bot);
            }
            else if (bot_overlap)
            {
                result.y = abs(m_bound.bot - other->getBound().top) * -1;
            }
        }

        if (y_overlap)
        {
            if (left_overlap) 
            {
                result.x = abs(m_bound.left - other->getBound().right);
            }
            else if (right_overlap)
            {
                result.x = abs(m_bound.right - other->getBound().left) * -1;
            }
        }

        // std::cout<<"x : "<<result.x<<" y : "<<result.y<<std::endl;

        if (abs(result.x) > abs(result.y)) result.x *= 0;
        else result.y *= 0;

        result *= other->weight / (weight + other->getWeight());

        return result;
    }
}