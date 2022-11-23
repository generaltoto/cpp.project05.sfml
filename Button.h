#pragma once

#include "SFML/Graphics.hpp"

class Button
{
private:
	sf::RectangleShape _shape;
	sf::Font* _font;
	sf::Text _text;
	sf::Color _textColor;
	sf::Color _shapeColor;

public:
	Button(
		sf::Vector2f pos, sf::Vector2f dim,
		sf::Font* font, std::string text,
		sf::Color textCol, sf::Color shapeCol
	);
	~Button();

	void display(sf::RenderWindow* window);
};

