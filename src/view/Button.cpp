#include "include/view/Button.h"

Button::Button(
	sf::Vector2f pos, sf::Vector2f dim,
	sf::Font* font, std::string text,
	int textSize,
	sf::Color textCol, sf::Color shapeCol)
{
	this->_shape.setPosition(pos);
	this->_shape.setSize(dim);
	this->_shape.setFillColor(shapeCol);

	this->_font = font;
	this->_text.setFont(*this->_font);
	this->_text.setString(text);
	this->_text.setFillColor(textCol);
	this->_text.setCharacterSize(textSize);
	this->_text.setPosition(
		(this->_shape.getPosition().x) + (
			this->_shape.getSize().x / 2.f - (((text.length()) / 2) * textSize)
			),
		(this->_shape.getPosition().y) + (
			this->_shape.getSize().y / 2.f - (textSize / 2))
	);
}

Button::~Button()
{
}

void Button::display(sf::RenderWindow* window)
{
	window->draw(this->_text);
	window->draw(this->_shape);
}
