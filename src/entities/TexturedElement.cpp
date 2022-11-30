#include "include/entities/TexturedElement.h"

TexturedElement::TexturedElement() = default;

TexturedElement::TexturedElement(
	int x,
	int y,
	std::string name,
	std::string path
)
{
	this->posX = x;
	this->posY = y;
	this->name = name;
	this->path = path;
	this->asset = new sf::Texture;
	if (this->asset->loadFromFile(path)) {
		std::cout << "loaded : '" << path << "'" << std::endl;
		this->sprite.setTexture(*this->asset);
	}
	else throw("ERROR::LOADING_ENTITY_TEXTURE");
}

sf::Sprite &TexturedElement::getSprite() { return this->sprite; }

std::string &TexturedElement::getName()
{
	return this->name;
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