# pragma once
# include <string>
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
	~TexturedElement();

	sf::Sprite getSprite();

	int getPos(char c);

	void displayEntity(sf::RenderWindow* window);

	void setPos(int x, int y);

	void nextAnimation(int direction);
};