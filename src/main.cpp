#include <iostream>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <yaml-cpp/yaml.h>
#include "Chunk.h"
#include "Animal.h"
#include "Renderer.h"

using namespace std;

Chunk ch;

int main()
{
    ch.tiles[4][4][15].attributes[0] = true;
    Animal player;
    player.character = '@';
    player.mass = 60;
    player.radius = 0.50;
    player.location.x = 2.0;
    player.location.y = 2.0;
    player.location.z = 15.0;
    for(int i = 0; i < 10; i++)
    {
        Animal *dude = new Animal();
        dude->character = '&';
        dude->mass = 40;
        dude->radius = 0.50;
        dude->location.x = i;
        dude->location.y = 8.0;
        dude->location.z = 15.0;
        ch.entities.push_back(dude);
    }
    ch.entities.push_back(&player);
    Material dirt(1510.0);
    sf::Color brown(153, 102, 51);
    dirt.colour = brown;
    for(int i = 0; i < 16; i++)
        for(int j = 0; j < 16; j++)
            ch.tiles[i][j][15].floorMaterial = &dirt;

    uint64_t ticks = 0;
    sf::RenderWindow window(sf::VideoMode(800, 600), "SFWT");
    sf::Font font;
    if(!font.loadFromFile("Resources/Font.ttf"))
    {
        std::cerr << "Font not found: Please provide a font at Resources/Font.ttf" << 
std::endl;
    }
    setFont(&font);
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if(event.type == sf::Event::Closed)
                window.close();
        }

        window.clear();
        render(ch, window);
        window.display();

        // Input

        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
            player.velocity += Vector {0.0, 0.1, 0.0};
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
            player.velocity += Vector {0.0, -0.1, 0.0};
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
            player.velocity += Vector {-0.1, 0.0, 0.0};
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
            player.velocity += Vector {0.1, 0.0, 0.0};

        // Tick
        ch.run(16); // At 60 FPS, this is approximately real-time
        ticks += 16;
    }
    return 0;
}
