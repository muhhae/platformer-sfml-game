#include <SFML/Graphics.hpp>
#include <iostream>

sf::RenderWindow window(sf::VideoMode(800, 600), "My Game", sf::Style::Default);
sf::Event event;

int x = 0;
int y = 0;

void input()
{
    if (event.type == sf::Event::Closed) window.close();
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) window.close();

    // if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) y += 1;
    // if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) y -= 1;
    // if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) x += 1;
    // if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) x -= 1;

    // if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) window.setSize(sf::Vector2u(1024, 720));
    // if (sf::Keyboard::isKeyPressed(sf::Keyboard::B)) window.setSize(sf::Vector2u(800, 600));
    // if (event.type == sf::Event::TextEntered)
    // {
    //     if (event.text.unicode < 128)
    //         std::cout << "ASCII character typed: " << static_cast<char>(event.text.unicode) << std::endl;
    // }
}

int main()
{
    bool kanan;
    bool move = 0;

    window.setFramerateLimit(60);

    sf::Texture txt_knight;
    int frame = 0;

    sf::RectangleShape box(sf::Vector2f(100, 100));
    box.setOrigin(50, 100);

    // sf::Image img_knight;
    // img_knight.loadFromFile("Sprite/Knight/Idle/0.gif");

    sf::Sprite spr_knight;

    sf::Image img_knight[10];
    sf::Image img_knight_run[10];




    for (int i = 0; i < 10; i++)
    {
        img_knight[i].loadFromFile("Sprite/Knight/Idle/" + std::to_string(i) + ".gif");
        img_knight_run[i].loadFromFile("Sprite/Knight/Run/" + std::to_string(i) + ".gif");
        // std::cout<<("Sprite/Knight/Run/" + std::to_string(i) + ".gif")<<std::endl;
    }

    // window.setVerticalSyncEnabled(true);

    spr_knight.setOrigin(50, 80);
    spr_knight.setScale(3,3);
    spr_knight.setPosition(100, 400);

    txt_knight.loadFromImage(img_knight_run[0]);
    spr_knight.setTexture(txt_knight);


    box.setPosition(spr_knight.getPosition());

    while (window.isOpen())
    {
        frame++;
        if (frame > 59) frame = 0;

        x = 0;
        y = 0;

        while (window.pollEvent(event))
        {
            input();
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) 
            {
                if (!move)
                {
                    frame = 0;
                    move = true;
                }
                
                kanan = true;
            }
            else if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
            {
                if (!move)
                {
                    frame = 0;
                    move = true;
                }
                kanan = false;
            }
            else 
            {
                // std::cout<<"henti"<<std::endl;
                move = false;
            }

        }

        

        if (move) txt_knight.update(img_knight_run[frame/6]);
        else txt_knight.update(img_knight[frame/6]);

        // std::cout<<"move : "<<(move ? "true" : "false")<<std::endl;
        // std::cout<<"frame : "<<frame/6<<std::endl;

        if (kanan) spr_knight.setScale(3,3);
        else spr_knight.setScale(-3, 3);

        if (move && kanan) spr_knight.move(2,0);

        else if (move) spr_knight.move(-2, 0);

        window.clear(sf::Color::Black);
        window.draw(box);
        window.draw(spr_knight);
        window.display();
    }


    return 0;
}