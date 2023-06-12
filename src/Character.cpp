#include "lib/Character.hpp"

Character::Character()
{

}

Character::Character(std::string name, sf::Vector2i origin)
{
    this->name = name;
    this->origin = origin;
    sprite.setOrigin(origin.x, origin.y);
    sprite.setScale(scale.x, scale.y);
    hitbox.setSize(sf::Vector2f(100, 150));
    hitbox.setOrigin(hitbox.getSize().x/2, hitbox.getSize().y);
}

void Character::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(hitbox, states);
    target.draw(sprite, states);
}

void Character::load(std::string dir, std::string extension )
{
    run.load("Run" ,dir, name, extension);
    idle.load("Idle" ,dir, name, extension);
    jump.load("Jump" ,dir, name, extension);
    fall.load("Fall" ,dir, name, extension);
}

void Character::switchState(std::string state)
{
    if (currentState != state)
    {
        currentState = state;   
        frame = 0;
    }
}

void Character::animUpdate()
{
    if (currentState == "Run") sprite.setTexture(run.get(frame));
    else if (currentState == "Idle") sprite.setTexture(idle.get(frame));
    else if (currentState == "Jump") sprite.setTexture(jump.get(frame));
    else if (currentState == "Fall") sprite.setTexture(fall.get(frame));
}

void Character::input(sf::Event event, int controlType)
{
    if (controlType == 0 || controlType == 2)
    {
        if (event.type == sf::Event::KeyPressed)
        {
            if ((event.key.code == sf::Keyboard::Up ) && isGrounded)
            {
                isJump = 5;
                isGrounded = false;
            }
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) 
        {
            if (!isMove)
            {
                isMove = true;
            }
            
            isKanan = true;
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
        {
            if (!isMove)
            {
                isMove = true;
            }
            isKanan = false;
        }
        else 
        {
            isMove = false;
        }
    }
    
    if (controlType == 1 || controlType == 2)
    {
        if (event.type == sf::Event::KeyPressed)
        {
            if ((event.key.code == sf::Keyboard::W) && isGrounded)
            {
                isJump = 5;
                isGrounded = false;
            }
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) 
        {
            if (!isMove)
            {
                isMove = true;
            }
            
            isKanan = true;
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
        {
            if (!isMove)
            {
                isMove = true;
            }
            isKanan = false;
        }
        else 
        {
            isMove = false;
        }
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::P)) sprite.rotate(1);
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::O)) sprite.rotate(-1);
}

void Character::update()
{
    frame++;
    if (frame > 99) frame = 0;

    if (sprite.getPosition().y >= 200 && isJump < 0) 
    {
        switchState("Idle");
        isGrounded = true;
    }

    if (!isGrounded) isJump -= 0.1;
    else isJump = 0;

    if (isJump > 0) switchState("Jump");
    else if (isJump < 0) switchState("Fall");

    if (isMove)
    {
        if (isKanan)
        {
            sprite.move(4, 0);
            sprite.setScale(scale.x, scale.y);
        }   
        else 
        {
            sprite.move(-4, 0);
            sprite.setScale(-1 * scale.x, scale.y);
        }

        if (isGrounded)
        {
            switchState("Run");
        }
    }
    else if(isGrounded) switchState("Idle");
    
    hitbox.setPosition(getPosition());
    sprite.move(0, -1 * isJump);
    animUpdate();
}

