# pragma once
# include <string>
# include <SFML/Graphics.hpp>
# include <SFML/Audio.hpp>
# include "Structures.h"

class TexturedElement {
protected:
	int posX, posY;
	std::string name;
	std::string path;
	sf::Texture asset;
	sf::Sprite sprite;

	TexturedElement();
	~TexturedElement();

	sf::Sprite getSprite();

	void displayEntity();

	void setPos(int x, int y);
};