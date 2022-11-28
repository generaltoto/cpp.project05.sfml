#include "include/entities/Player.h"
#include "include/map/MapGenerator.h"

Player::Player() { 
	for (int i = 0; i < 6; i++) {
		this->team[i] = NULL;
	}
	sf::VideoMode* size = new sf::VideoMode();
	this->xOnMap = 0;
	this->yOnMap = 0;
	this->name = "Petit Louis";
	this->path = "assets/sacha.png";
	this->animeCount = 0;
	this->animePos = std::vector<std::vector<sf::IntRect>>(ANIME_SACHA_RECT);
	if (animePos.size() <= 0) throw("C K C");
	if (!this->asset.loadFromFile("assets/sacha.png")) {
		throw("C K C");
	}
	else {
		this->sprite.setTexture(this->asset);
		this->sprite.setTextureRect(this->animePos[0][this->animeCount]);
	}
	this->sprite.setScale(0.6f, 0.6f);
	this->setPos(
		(((size->getDesktopMode().width) / 2) - 55), 
		(((size->getDesktopMode().height) / 2) - 65));
	delete size;
}

Player::~Player() { }

void Player::addPokemon(Pokemon* p) {
	for (int i = 0; i < 6; i++) {
		if (this->team[i] != NULL) {
			this->team[i] = p;
		}
	}
}

void Player::removePokemon(int id) {

}

void Player::addItem(int bag, int added) { this->bag[bag] += added; }

void Player::removeItem(int bag, int sub) { this->bag[bag] -= sub; }

void Player::updatePlayer(int* frameCount, sf::View* view, const int* level) {
	
	int tileValue = 0;
	const int frameUpdater = 600;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
		tileValue = level[(MAPHEIGHT * (yOnMap-1)) + xOnMap];
		if ((tileValue < 4 || tileValue > 13) && !OutOfBoundaries(xOnMap, yOnMap - 1))
		{
			view->move(0, -32 / 0.6f);
			yOnMap--;
		}
		if (*frameCount % frameUpdater == 0) {
			nextAnimation(3);
			*frameCount = 0;
		}
		return;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
		tileValue = level[(MAPHEIGHT * (yOnMap+1)) + xOnMap];
		if ((tileValue < 4 || tileValue > 13) && !OutOfBoundaries(xOnMap, yOnMap + 1))
		{
			view->move(0, 32 / 0.6f);
			yOnMap++;
		}
		if (*frameCount % frameUpdater == 0) {
			nextAnimation(0);
			*frameCount = 0;
		}
		return;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
		tileValue = level[(MAPHEIGHT * yOnMap) + xOnMap+1];
		if ((tileValue < 4 || tileValue > 13) && !OutOfBoundaries(xOnMap + 1, yOnMap))
		{
			view->move(32 / 0.6f, 0);
			xOnMap++;
		}
		if (*frameCount % frameUpdater == 0) {
			nextAnimation(2);
			*frameCount = 0;
		}
		return;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
		tileValue = level[(MAPHEIGHT * yOnMap) + xOnMap-1];
		if ((tileValue < 4 || tileValue > 13) && !OutOfBoundaries(xOnMap - 1, yOnMap))
		{
			view->move(-32 / 0.6f, 0);
			xOnMap--;
		}
		if (*frameCount % frameUpdater == 0) {
			nextAnimation(1);
			*frameCount = 0;
		}
		return;
	}
	this->animeCount = 0;
}

void Player::SetMapPosition(int x, int y)
{
	xOnMap = x;
	yOnMap = y;
}

int Player::GetMapPositionx()
{
	return xOnMap;
}

int Player::GetMapPositiony()
{
	return yOnMap;
}

bool Player::OutOfBoundaries(int x, int y)
{
	if (x >= MAPWIDTH || x < 0)
	{
		return true;
	}
	else if (y > MAPHEIGHT-1 || y < 0)
	{
		return true;
	}
	else return false;
}


