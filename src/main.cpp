#include "lib/lib.hpp"
#include "lib/Character.hpp"

int main()
{
    sf::RenderWindow window(sf::VideoMode().getDesktopMode(), "My Game", sf::Style::Fullscreen);
    sf::Event event;
    sf::View view;

    bool full = true;
    window.setFramerateLimit(100);

    sf::RectangleShape box(sf::Vector2f(3000, 300));
    box.setOrigin(box.getSize().x/2, box.getSize().y/2);

    sf::Texture bg;
    bg.loadFromFile("Sprite/BG/bg.gif");

    sf::Sprite background;

    bg.setRepeated(true);
    background.setTexture(bg);
    background.setTextureRect(sf::IntRect(0, 0, 10000, 2160));
    background.setOrigin(bg.getSize().x, background.getTextureRect().height);

    Character Knight("Knight", sf::Vector2i(55,80));
    Knight.load();

    sf::Image acuan;
    acuan.loadFromFile("Sprite/Mage/Idle/0.gif");

    Character Mage("Mage", sf::Vector2i(acuan.getSize().x/2, acuan.getSize().y * 0.67));
    Mage.load();
    Mage.setPosition(Knight.getPosition() + sf::Vector2f(200, 0));
    Mage.setWeight(2);

    view.setCenter(Knight.getPosition().x, Knight.getPosition().y);
    view.setSize(window.getSize().x, window.getSize().y);

    background.setPosition(sf::Vector2f(view.getCenter()));
    background.move(0, 580);

    box.setPosition(background.getPosition() + sf::Vector2f(0, -100));

    collider::BoxCollider boxCol(box.getSize().y, box.getSize().x);
    boxCol.updatePos(box.getPosition());
    boxCol.setWeight();

    sf::Color col;
    col.a = 150;

    box.setFillColor(col);

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

            Knight.input(event, 0);
            Mage.input(event, 1);
        }

        Knight.update();
        Mage.update();

        Knight.collision(&Mage);
        Mage.collision(&Knight);

        Knight.collision(&boxCol);
        Mage.collision(&boxCol);

        view.setCenter(Knight.getPosition().x, view.getCenter().y);

        window.setView(view);

        window.clear(sf::Color::White);

        window.draw(background);
        window.draw(box);
        
        window.draw(Mage);
        window.draw(Knight);

        window.display();
    }
    return 0;
}