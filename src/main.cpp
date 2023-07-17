#include "lib/lib.hpp"
#include "lib/Character.hpp"
#include "lib/GameObject.hpp"
#include <random>


int main()
{
    srand(time(NULL));

    sf::RenderWindow window(sf::VideoMode().getDesktopMode(), "My Game", sf::Style::Default);
    sf::Event event;
    sf::View view;

    bool full = true;
    window.setFramerateLimit(100);

    sf::Texture bg;
    bg.loadFromFile("Sprite/BG/BG3.jpg");
    bg.setSmooth(0);

    sf::Sprite background;

    bg.setRepeated(true);
    background.setTexture(bg);
    background.setTextureRect(sf::IntRect(0, 0, 10000, 2160));
    background.setOrigin(bg.getSize().x, background.getTextureRect().height/2);
    background.setScale(3, 3);

    sf::Image acuan;
    acuan.loadFromFile("Sprite/Mage/Idle/0.gif");

    Character Mage("Mage", sf::Vector2i(acuan.getSize().x/2, acuan.getSize().y* 0.57));
    Mage.setPosition(sf::Vector2f(200, 0));
    Mage.getCollider().setWeight(2);
    Mage.getCollider().setSize(100, 200);

    Character Knight("Knight", sf::Vector2i(55,61));
    Knight.setPosition(sf::Vector2f(0, 0));
    Knight.getCollider().setWeight(1);
    Knight.getCollider().setSize(100, 150);

    view.setCenter(Knight.getPosition().x, Knight.getPosition().y);
    view.setSize(window.getSize().x, window.getSize().y);

    background.setPosition(sf::Vector2f(view.getCenter()));
    background.move(0, 580);

    GameObject boxCol;
    boxCol.getCollider().setSize(3000, 300);
    boxCol.getCollider().updatePos(background.getPosition() + sf::Vector2f(0, -228));
    boxCol.getCollider().setWeight(100000);
    boxCol.getCollider().isSolid(0);

    std::vector<GameObject*> blocks;
    sf::Vector2f blockPos = sf::Vector2f(-400, -28);
    int gap = 0;

    for (int i = 0; i < 100; i++)
    {
        GameObject* block = new GameObject();

        block->load("Sprite/Block/block.jpeg");
        block->getSprite().setOrigin(block->getSprite().getLocalBounds().width/2, block->getSprite().getLocalBounds().height/2);
        block->getSprite().setPosition(background.getPosition() + blockPos);
        block->getSprite().setScale(0.8, 0.8);
        block->getCollider().setSize(block->getSprite().getLocalBounds().width * block->getSprite().getScale().x, block->getSprite().getLocalBounds().height * block->getSprite().getScale().y);
        
        block->getCollider().debug();
        block->getCollider().setKinematic(true);

        if (i == 4) block->getSprite().move(0, -1 * block->getSprite().getLocalBounds().height * block->getSprite().getScale().y);

        block->getCollider().updatePos(block->getSprite().getPosition());

        blocks.push_back(block);

        blockPos += sf::Vector2f(block->getSprite().getLocalBounds().width * block->getSprite().getScale().x + gap, 0);
    }

    blockPos = sf::Vector2f(0, -28);

    Mage.getCollider().debug(true);
    Knight.getCollider().debug();

    Mage.getCollider().setKinematic(false);    
    Knight.getCollider().setKinematic(false);
     
    Mage.load();
    Knight.load();   

    background.move(0, 800);

    while (window.isOpen())
    {
        while (window.pollEvent(event))
        {   
            if (event.type == sf::Event::Closed) window.close();

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) window.close();

            if (event.type == sf::Event::KeyReleased)
            {
                if (event.key.code == sf::Keyboard::X)
                {
                    if (!full) window.create(sf::VideoMode().getDesktopMode(), "My Game", sf::Style::Fullscreen);
                    else window.create(sf::VideoMode(1024, 728), "My Game", sf::Style::Default);
                    full = 1 - full;
                    window.setFramerateLimit(100);
                    view.setSize(window.getSize().x, window.getSize().y);
                }
            }

            if (event.type == sf::Event::Resized)
            {
                view.setSize(window.getSize().x, window.getSize().y);
            }

            
        }

        Knight.input(0);
        Mage.input(1);

        Knight.update();
        Mage.update();

        collider::checkCollision();

        Knight.colTempUpdate();
        Mage.colTempUpdate();

        view.setCenter(Knight.getPosition().x, Knight.getPosition().y);

        window.setView(view);

        window.clear(sf::Color::White);

        window.draw(background);

        window.draw(boxCol);

        for (const auto& b : blocks)
        {
            window.draw(*b);
        }

        window.draw(Knight);
        window.draw(Mage);
       

        window.display();
    }
    return 0;
}