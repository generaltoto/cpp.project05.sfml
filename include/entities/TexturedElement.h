# pragma once
# include <SFML/Graphics.hpp>
# include "include/Structures.h"
# include <iostream>
# include <chrono>
# include <thread>
using namespace std::this_thread;
using namespace std::chrono;


class TexturedElement {
protected:
	size_t animeCount;
	std::vector<std::vector<sf::IntRect>> animePos;
	int posX, posY;
	std::string name;
	std::string path;
	sf::Texture *asset;
	sf::Sprite sprite;

public:

	TexturedElement();

	TexturedElement(
		int x,
		int y,
		std::string name,
		std::string path
	);

	/// Returns the sprite of the texture.
	sf::Sprite &getSprite();

	/// Returns the name of the texture.
	std::string &getName();

	/// Displays the entity.
	void displayEntity(sf::RenderWindow* window);

	/// Sets the position of the element on the screen.
	void setPos(int x, int y);

	/// Animates the element depending on a given direction.
	void nextAnimation(int direction);
};