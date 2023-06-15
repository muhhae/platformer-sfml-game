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
    setSize(150, 100);
    doJump = false;
}

void Character::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(sprite, states);
    colDraw(target);
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

    isGrounded = false;
    colMove.clear();
}

void Character::collision(collider::BoxCollider* other)
{
    sf::Vector2f move = vectorCollision(other);

    if (!isGrounded)
    {
        if (move.y < 0) isGrounded = true;
        else isGrounded = false;
    }

    // std::cout<<"move .y : "<<move.y<<std::endl;
    if (move.y > 0 && isGrounded) return;
    colMove.push_back(move);
}

void Character::update()
{
    for (const auto& mov : colMove)
    {
        if (mov.y > 0 && isGrounded) continue;
        sprite.move(mov);
    }
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
    
    hitbox.setPosition(getPosition());
    sprite.move(0, -1 * isJump);
    animUpdate();
    updatePos(getPosition());
    // std::cout<<name<<" : "<<currentState<<" isGrounded : "<<isGrounded<<" Jump "<<isJump<<std::endl;
}

