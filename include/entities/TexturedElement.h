# pragma once
# include <iostream>
# include <SFML/Graphics.hpp>
# include <SFML/Audio.hpp>
# include "include/Structures.h"

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
	TexturedElement(std::string path);
	TexturedElement(
		int x,
		int y,
		std::string name,
		std::string path
	);

	sf::Sprite &getSprite();

	std::string &getName();

	void displayEntity(sf::RenderWindow* window);

	void setPos(int x, int y);

	void nextAnimation(int direction);
};