/*
 * Simple demonstration of the Perlin Noise algorithm.
 *
 * To set up SFML, refer to the official website:
 * https://www.sfml-dev.org/
 */

#include <SFML/Graphics.hpp>

#define DB_PERLIN_IMPL
#include "db_perlin.hpp"
#include "TileMap.h"
#include <iostream>

int main() {
    int unsigned width = 1024 ;
    int unsigned height =  512 ;
    

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

    sf::Clock clock;
    int count = 0;
    float level[32][16] = {};
    int level2[512] = {};
        

    while (window.isOpen()) {
        sf::Event ev{};
        while (window.pollEvent(ev)) {
            if (ev.type == sf::Event::Closed) {
                window.close();
            }
        }
        auto const dt = clock.getElapsedTime().asSeconds();

        for (auto y = 0; y < 16; ++y) {
            for (auto x = 0; x < 32; ++x) {
                
                level[x][y] = (
                    db::perlin(float(x) / 64.0f, float(y) / 64.0f, dt * 0.25f) * 1.0f +
                    db::perlin(float(x) / 32.0f, float(y) / 32.0f, dt * 0.75f) * 0.5f
                    ) / 0.25f;
                if (level[x][y] <= 0) {
                    level[x][y] = -level[x][y];
                }
                if (level[x][y] >= 3) level[x][y] = 3;
                level2[count] = round(level[x][y]);
                count++;
            }
        }
        count = 0;

        

        TileMap map;
        if (!map.load("tileSet.png", sf::Vector2u(32, 32), level2, 32, 16))
        return -1;


        texture.update(image);

        window.clear();
        window.draw(map);
        window.display();
    }
}