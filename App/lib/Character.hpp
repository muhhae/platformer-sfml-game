#pragma once

#include "lib.hpp"
#include "TextureManager.hpp"
#include "Collider.hpp"
#include "HasCollider.hpp"


class Character : public sf::Drawable, public collider::HasCollider
{
    private :
        std::string name;

        sf::Vector2i origin;
        sf::Vector2f scale = sf::Vector2f(4,4);

        sf::Sprite sprite;
        
        enum class State
        {
            Idle,
            Run,
            Jump,
            Fall
        };
        
        std::vector<TextureManager> states;
        State currentState = State::Idle;

        int frame = 0;
        int groundCount = 0;

        bool isMove, isMoveJump, isKanan, doJump;

        float verticalVelocity;
        
        float fps = 10;
        float timeElapsed = 0;

    public :
        Character();
        Character(std::string name, sf::Vector2i origin);

        void load(std::string dir = "Sprite", std::string extension = "gif");
        void switchState(State state);
        void update();
        void animUpdate();
        void colTempUpdate();

        void input(int);

        sf::Vector2f getPosition() { return sprite.getPosition(); }
        void setPosition(sf::Vector2f pos) { sprite.setPosition(pos); }

        virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const;
        
};