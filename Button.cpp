#include "Button.h"

Button::Button(
	sf::Vector2f pos, sf::Vector2f dim,
	sf::Font* font, std::string text,
	sf::Color textCol, sf::Color shapeCol)
{
	this->_shape.setPosition(pos);
	this->_shape.setSize(dim);
	this->_shape.setFillColor(shapeCol);

	this->_font = font;
	this->_text.setFont(*this->_font);
	this->_text.setString(text);
	this->_text.setFillColor(textCol);
	this->_text.setCharacterSize(20);
	this->_text.setPosition(
		this->_shape.getPosition().x / 2.f - this->_text.getGlobalBounds().width / 2.f,
		this->_shape.getPosition().y / 2.f - this->_text.getGlobalBounds().height / 2.f
	);
}

Button::~Button()
{
}

void Button::display(sf::RenderWindow* window)
{
	window->draw(this->_shape);
}
