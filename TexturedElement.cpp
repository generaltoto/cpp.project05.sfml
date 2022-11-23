# include "TexturedElement.h"

TexturedElement::TexturedElement()
{
}

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
}

TexturedElement::~TexturedElement() { }

sf::Sprite TexturedElement::getSprite() { return this->sprite; }

void TexturedElement::displayEntity(sf::RenderWindow* window) 
{ 
	if (!this->asset.loadFromFile(this->path))
		std::cout << "Error loading file " << this->path << std::endl;
	else sprite.setTexture(this->asset);
	window->draw(this->sprite);
}

void TexturedElement::setPos(int x, int y) {
	this->posX = x;
	this->posY = y;
}
