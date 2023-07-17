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
    col.setSize(150, 100);
    doJump = false;
}

void Character::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(sprite, states);
    col.colDraw(target);
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

void Character::input(int controlType)
{
    if (controlType == 0 || controlType == 2)
    {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) 
        {
            if (isGrounded)
            {
                isJump = 7;
                doJump = true;
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
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) 
        {
            if (isGrounded)
            {
                isJump = 7;
                doJump = true;
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

    if (!isGrounded) isJump -= 0.1;
    else if(!doJump) isJump = -0.1;

    doJump = !isGrounded;

    if (!isGrounded)
    {
        if (isJump > 0) switchState("Jump");
        else if (isJump < 0) switchState("Fall");
    }

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
    
    sprite.move(0, -1 * isJump);
    animUpdate();

    col.updatePos(getPosition());
    isGrounded = false;
}

void Character::colTempUpdate() {
    sprite.move(colMove);
    col.updatePos(getPosition());

    colMove = sf::Vector2f(0, 0);
}

