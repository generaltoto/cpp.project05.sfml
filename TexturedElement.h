# pragma once
# include <string>
# include <iostream>
# include <SFML/Graphics.hpp>
# include <SFML/Audio.hpp>
# include "Structures.h"

class TexturedElement {
protected:
	size_t animeCount;
	std::vector<std::vector<sf::IntRect>> animePos;
	int posX, posY;
	std::string name;
	std::string path;
	sf::Texture asset;
	sf::Sprite sprite;

public:
	TexturedElement();
	TexturedElement(
		int x,
		int y,
		std::string name,
		std::string path
	);
	~TexturedElement();

	sf::Sprite getSprite();

	void displayEntity(sf::RenderWindow* window);

	void setPos(int x, int y);

	void nextAnimation(int direction);
};