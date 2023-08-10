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
    states.resize(4);
    
    states.at((int)State::Run).load("Run" ,dir, name, extension);
    states.at((int)State::Idle).load("Idle" ,dir, name, extension);
    states.at((int)State::Jump).load("Jump" ,dir, name, extension);
    states.at((int)State::Fall).load("Fall" ,dir, name, extension);
}

void Character::switchState(State state)
{
    if (currentState == state) return;
    
    currentState = state;   
    frame = 0;
}

void Character::animUpdate()
{
    sprite.setTexture(states.at((int)currentState).get(frame));
}

void Character::input(int controlType)
{
    if (controlType == 0 || controlType == 2)
    {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) 
        {
            if (isGrounded)
            {
                verticalVelocity = jumpForce;
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
                verticalVelocity = jumpForce;
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
    sf::Vector2f moveVector = sf::Vector2f(0, 0);
    
    timeElapsed += timer::deltaTime;
    
    if (timeElapsed >= 1.0f / fps) timeElapsed = 0, frame++;
    
    // std::cout << "Time Elapsed : " << timeElapsed << "\n"
    //           << "FPS : " << fps << "\n"
    //           << "Frame : " << frame << "\n"
    //           << "1/FPS : " << 1.0f / fps << "\n";

    if (!isGrounded) verticalVelocity -= gravity * timer::deltaTime;
    else if(!doJump) verticalVelocity = -0.1;

    doJump = !isGrounded;

    if (!isGrounded)
    {
        if (verticalVelocity > 0) switchState(State::Jump);
        else if (verticalVelocity < 0) switchState(State::Fall);
    }

    if (isMove)
    {
        if (isKanan)
        {
            moveVector.x += speed;
            sprite.setScale(scale.x, scale.y);
        }   
        else 
        {
            moveVector.x -= speed;
            sprite.setScale(-1 * scale.x, scale.y);
        }

        if (isGrounded)
        {
            switchState(State::Run);
        }
    }
    else if(isGrounded) switchState(State::Idle);
    
    moveVector.y -= verticalVelocity;
    animUpdate();
    
    sprite.move(moveVector * timer::deltaTime);

    col.updatePos(getPosition());
    isGrounded = false;
}

void Character::colTempUpdate() {
    sprite.move(colMove);
    col.updatePos(getPosition());

    colMove = sf::Vector2f(0, 0);
}

