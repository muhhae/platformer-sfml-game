#include "lib/lib.hpp"
#include "lib/Character.hpp"


int main()
{
    sf::RenderWindow window(sf::VideoMode().getDesktopMode(), "My Game", sf::Style::Fullscreen);
    sf::Event event;
    sf::View view;

    bool full = true;
    window.setFramerateLimit(100);

    sf::Texture bg;
    bg.loadFromFile("Sprite/BG/bg.gif");

    sf::Sprite background;

    bg.setRepeated(true);
    background.setTexture(bg);
    background.setTextureRect(sf::IntRect(0, 0, 10000, 2160));
    background.setOrigin(bg.getSize().x, background.getTextureRect().height/2);

    Character Knight("Knight", sf::Vector2i(55,61));
    Knight.load();

    sf::Image acuan;
    acuan.loadFromFile("Sprite/Mage/Idle/0.gif");

    Character Mage("Mage", sf::Vector2i(acuan.getSize().x/2, acuan.getSize().y* 0.57));
    Mage.load();
    Mage.setPosition(Knight.getPosition() + sf::Vector2f(200, 0));
    Mage.setWeight(2);
    Mage.setSize(200, 100);

    view.setCenter(Knight.getPosition().x, Knight.getPosition().y);
    view.setSize(window.getSize().x, window.getSize().y);

    background.setPosition(sf::Vector2f(view.getCenter()));
    background.move(0, 580);

    collider::BoxCollider boxCol(300, 3000);
    boxCol.updatePos(background.getPosition() + sf::Vector2f(0, -228));
    boxCol.setWeight(100000);

    collider::BoxCollider block(200, 200);
    block.updatePos(background.getPosition() + sf::Vector2f(400, -528));
    block.debug();

    Mage.debug(true);
    boxCol.debug();

    std::vector<collider::BoxCollider*> col;

    col.push_back(&Mage);
    col.push_back(&Knight);
    col.push_back(&boxCol);
    col.push_back(&block);

    Mage.setType(0);    
    Knight.setType(0);

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
                view.setSize(event.size.width/2, event.size.height/2);
            }

            
        }
        Knight.input(0);
        Mage.input(1);

        // Knight.collision(&Mage);
        // Mage.collision(&Knight);

        // Knight.collision(&boxCol);
        // Mage.collision(&boxCol);

        for (int i = 0; i < col.size(); i++)
        {
            if (col.at(i)->getType() == true) continue;

            for (int j = 0; j < col.size(); j++)
            {
                if (i == j) continue;

                col.at(i)->collision(col.at(j));
            }
        }

        Knight.update();
        Mage.update();

        view.setCenter(Knight.getPosition().x, view.getCenter().y);

        window.setView(view);

        window.clear(sf::Color::White);

        window.draw(background);
        
        window.draw(Mage);
        window.draw(Knight);

        boxCol.colDraw(window);
        block.colDraw(window);

        window.display();
    }
    return 0;
}