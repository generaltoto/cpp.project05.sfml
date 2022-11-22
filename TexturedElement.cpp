# include "TexturedElement.h"

TexturedElement::TexturedElement() { }

TexturedElement::~TexturedElement() { }

sf::Sprite TexturedElement::getSprite() { return this->sprite; }

void TexturedElement::displayEntity() { 

}

void TexturedElement::setPos(int x, int y) {
	this->posX = x;
	this->posY = y;
}
