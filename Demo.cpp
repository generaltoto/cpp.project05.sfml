/*
 * Simple demonstration of the Perlin Noise algorithm.
 *
 * To set up SFML, refer to the official website:
 * https://www.sfml-dev.org/
 */

#include <SFML/Graphics.hpp>
#include "db_perlin.hpp"
#include "TileMap.h"
#include <iostream>
#include "MapGenerator.h"
#define DB_PERLIN_IMPL


int main() {
    int unsigned width = 1080 ;
    int unsigned height =  720 ; 

    
    sf::RenderWindow window{
        sf::VideoMode { width, height },"Perlin Noise"
    };

    window.setFramerateLimit(60);

    sf::Image image;
    image.create(width, height);

    sf::Texture texture;
    texture.loadFromImage(image);

    sf::Sprite output;
    output.setTexture(texture);

    MapGenerator mapGenerator;
    int seed1 = NULL;
    findMap:
    mapGenerator.GenerateSeed();
    if (seed1 && seed1 == mapGenerator.GetSeed()) goto findMap;
    mapGenerator.GenerateMap();
    mapGenerator.NormalizeMap();
    mapGenerator.SetMountains();
    mapGenerator.SetMapToLevel2();
    mapGenerator.SetEntryExitPoints();
    //mapGenerator.PrintMap();
    if (mapGenerator.IsPath())
    {
        std::cout << "there's a path" << std::endl;
    }
    else {
        std::cout << "there's no path" << std::endl;
        
        seed1 = mapGenerator.GetSeed();
        goto findMap;
    }
      

    while (window.isOpen()) {
        sf::Event ev{};
        while (window.pollEvent(ev)) {
            if (ev.type == sf::Event::Closed) {
                window.close();
            }
        }

        TileMap map;
        if (!map.load("pixil-frame-0.png", sf::Vector2u(32, 32), mapGenerator.GetLevel2(), MAPWIDTH, MAPHEIGHT, 2.9)) //2.9 pour 64 * 64   11.6 pour 256 * 256
        return -1;


        texture.update(image);

        window.clear();
        window.draw(map);
        window.display();
    }
}

