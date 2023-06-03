#pragma once

#include "lib.hpp"
#include "TextureManager.hpp"

class Character : public sf::Drawable
{
    private :
        std::string name;

        sf::Vector2i origin;
        sf::Vector2f scale = sf::Vector2f(4,4);

        sf::Sprite sprite;
        sf::RectangleShape hitbox;

        TextureManager run;
        TextureManager idle;
        TextureManager jump;
        TextureManager fall;

        std::string currentState = "Idle";

        int frame = 0;

        bool isMove, isMoveJump, isKanan, isGrounded;

        float isJump;

    public :
        Character();
        Character(std::string name, sf::Vector2i origin);

        // void setPosition(sf::Vector2f position);

        void load(std::string dir = "Sprite", std::string extension = "gif");
        void switchState(std::string state);
        void update();
        void animUpdate();
        void input(sf::Event event, int);

        sf::Vector2f getPosition(){return sprite.getPosition();}

        virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};