#include "lib/lib.hpp"

sf::RenderWindow window(sf::VideoMode().getDesktopMode(), "My Game", sf::Style::Fullscreen);
sf::Event event;
sf::View view;

bool full = true;

int x = 0;
int y = 0;

void input()
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
            window.setFramerateLimit(80);
            view.setSize(window.getSize().x/2, window.getSize().y/2);
        }
    }

    if (event.type == sf::Event::Resized)
    {
        view.setSize(event.size.width/2, event.size.height/2);
        // std::cout<<"tes"<<std::endl;
    }

    // if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) y += 1;
    // if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) y -= 1;
    // if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) x += 1;
    // if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) x -= 1;

    
    
    
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

    float jump = 0;
    

    window.setFramerateLimit(80);

    sf::Texture txt_knight;
    int frame = 0;

    sf::RectangleShape box(sf::Vector2f(100, 100));
    box.setOrigin(50, 100);

    // sf::Image img_knight;
    // img_knight.loadFromFile("Sprite/Knight/Idle/0.gif");

    sf::Sprite spr_knight;

    ImageStorage Knight_run;
    ImageStorage Knight_idle;

    Knight_idle.load("Idle", 10);
    Knight_run.load("Run", 10, "Sprite/Knight", "gif");

    // window.setVerticalSyncEnabled(true);

    spr_knight.setOrigin(50, 80);
    spr_knight.setScale(3,3);
    spr_knight.setPosition(100, 400);

    txt_knight.loadFromImage(Knight_idle.getImg(0));
    spr_knight.setTexture(txt_knight);


    box.setPosition(spr_knight.getPosition());

    view.setCenter(spr_knight.getPosition().x, spr_knight.getPosition().y);
    view.setSize(window.getSize().x/2, window.getSize().y/2);

    while (window.isOpen())
    {
        frame++;
        if (frame > 59) frame = 0;

        x = 0;
        y = 0;

        // if (spr_knight.getPosition().y > 400 && !jump) spr_knight.move(sf::Vector2f(0, -1));

        if (spr_knight.getPosition().y < 600) jump -= 0.1;

        if (spr_knight.getPosition().y >= 600) jump = 0;

        while (window.pollEvent(event))
        {   
            if (event.type == sf::Event::KeyReleased)
            {
                if (event.key.code == sf::Keyboard::Space && jump == 0)
                {
                    jump = 5;
                    std::cout<<spr_knight.getPosition().y<<std::endl;
                }
            }
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

        spr_knight.move(sf::Vector2f(0, jump * -1));
        
        if (move) txt_knight.update(Knight_run.getImg(frame/6));
        else txt_knight.update(Knight_idle.getImg(frame/6));
        

        // std::cout<<"move : "<<(move ? "true" : "false")<<std::endl;
        // std::cout<<"frame : "<<frame/6<<std::endl;

        if (kanan) spr_knight.setScale(3,3);
        else spr_knight.setScale(-3, 3);

        if (move && kanan) spr_knight.move(2,0);

        else if (move) spr_knight.move(-2, 0);

        view.setCenter(spr_knight.getPosition().x, view.getCenter().y);
        // std::cout<<"cam pos: "<<view.getCenter().x<<" "<<view.getCenter().y<<std::endl;
        // view.setViewport(sf::FloatRect(0, 0, 1, 1));

        window.setView(view);
        window.clear(sf::Color::Black);
        window.draw(box);
        window.draw(spr_knight);
        window.display();
    }


    return 0;
}