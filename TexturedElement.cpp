# include "TexturedElement.h"

TexturedElement::TexturedElement() { }

TexturedElement::~TexturedElement() { }

sf::Sprite TexturedElement::getSprite() { return this->sprite; }

int TexturedElement::getPos(char c) {
	if (c == 'x') {
		return this->posX;
	}
	else if (c == 'y') {
		return this->posY;
	}
	return 0;
}

void TexturedElement::displayEntity(sf::RenderWindow* window) { 
	window->draw(this->sprite);
}

void TexturedElement::setPos(int x, int y) {
	this->posX = x;
	this->posY = y;
	this->sprite.setPosition(float(x), float(y));
}

void TexturedElement::nextAnimation(int direction) {
	this->animeCount++;
	if (this->animeCount >= this->animePos.size())
		this->animeCount = 0;

	this->sprite.setTextureRect(animePos[direction][this->animeCount]);
}