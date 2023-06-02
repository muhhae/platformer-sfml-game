#include "lib/lib.hpp"
#include "lib/Character.hpp"

int main()
{
    sf::RenderWindow window(sf::VideoMode().getDesktopMode(), "My Game", sf::Style::Fullscreen);
    sf::Event event;
    sf::View view;

    bool full = true;
    window.setFramerateLimit(100);

    sf::RectangleShape box(sf::Vector2f(10000, 1080));
    box.setOrigin(box.getSize().x/2, box.getSize().y/2);

    sf::Texture bg;
    bg.loadFromFile("Sprite/BG/bg.gif");

    sf::Sprite background;
    sf::Sprite background2;

    background.setTexture(bg);
    background.setTextureRect(sf::IntRect(0, 200, 1920, 1080));
    background.setOrigin(bg.getSize().x/2, bg.getSize().y/2);

    background2.setTexture(bg);
    background2.setTextureRect(sf::IntRect(0, 200, 1920, 1080));
    background2.setOrigin(bg.getSize().x/2, bg.getSize().y/2);

    Character Knight("Knight", sf::Vector2i(55,80));
    Knight.load();

    view.setCenter(Knight.getPosition().x, Knight.getPosition().y);
    view.setSize(window.getSize().x/2, window.getSize().y/2);

    
    background.setPosition(sf::Vector2f(view.getCenter()));
    background.move(0, 240);

    background2.setPosition(background.getPosition());
    background2.move(bg.getSize().x, 0);

    box.setPosition(background.getPosition());
    box.move(0, -580);

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
                    view.setSize(window.getSize().x/2, window.getSize().y/2);
                }
            }

            if (event.type == sf::Event::Resized)
            {
                view.setSize(event.size.width/2, event.size.height/2);
            }
            
            Knight.input(event);
        }

        Knight.update();

        view.setCenter(Knight.getPosition().x, view.getCenter().y);

        window.setView(view);
        window.clear(sf::Color::Black);

        window.draw(background2);
        window.draw(background);
        window.draw(box);
        window.draw(Knight);
        window.display();
    }


    return 0;
}