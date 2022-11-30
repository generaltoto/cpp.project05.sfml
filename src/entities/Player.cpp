#include "include/entities/Player.h"

Player::Player(std::string path) : TexturedElement(path) { 
	this->bag.resize(3);
	this->xOnMap = 0;
	this->yOnMap = 0;
	this->name = "Petit Louis";
	this->path = path;
	this->animeCount = 0;
	this->animePos = std::vector<std::vector<sf::IntRect>>(ANIME_SACHA_RECT);
	if (animePos.size() <= 0) throw("C K C");
	else this->sprite.setTextureRect(this->animePos[0][this->animeCount]);
	this->sprite.setScale(0.6f, 0.6f);
}

std::vector<Pokemon> Player::getTeam() { return this->team; }

std::vector<int> Player::getBag() { return this->bag; }

void Player::addPokemon(Pokemon p) {
	if (this->team.size() < 6) this->team.push_back(p);
}

void Player::removePokemon(int id) {

}

void Player::addItems(int bag, int added) { this->bag[bag] += added; }

void Player::removeItem(int bag, int sub) { this->bag[bag] -= sub; }

void Player::updatePlayer(int* frameCount, sf::View* view, const int* level) {
	
	int tileValue = 0;
	const int frameUpdater = 300;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
		tileValue = level[(MAPHEIGHT * (yOnMap-1)) + xOnMap];
		if (*frameCount % frameUpdater == 0) {
			if ((tileValue < 4 || tileValue > 13) && !OutOfBoundaries(xOnMap, yOnMap - 1))
			{
				view->move(0, -32 / 0.6f);
				yOnMap--;
			}
			nextAnimation(3);
			*frameCount = 0;
		}
		return;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
		tileValue = level[(MAPHEIGHT * (yOnMap+1)) + xOnMap];
		if (*frameCount % frameUpdater == 0) {
			if ((tileValue < 4 || tileValue > 13) && !OutOfBoundaries(xOnMap, yOnMap + 1))
			{
				view->move(0, 32 / 0.6f);
				yOnMap++;
			}
			nextAnimation(0);
			*frameCount = 0;
		}
		return;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
		tileValue = level[(MAPHEIGHT * yOnMap) + xOnMap+1];
		if (*frameCount % frameUpdater == 0) {
			if ((tileValue < 4 || tileValue > 13) && !OutOfBoundaries(xOnMap + 1, yOnMap))
			{
				view->move(32 / 0.6f, 0);
				xOnMap++;
			}
			nextAnimation(2);
			*frameCount = 0;
		}
		return;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
		tileValue = level[(MAPHEIGHT * yOnMap) + xOnMap-1];
		if (*frameCount % frameUpdater == 0) {
			if ((tileValue < 4 || tileValue > 13) && !OutOfBoundaries(xOnMap - 1, yOnMap))
			{
				view->move(-32 / 0.6f, 0);
				xOnMap--;
			}
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


