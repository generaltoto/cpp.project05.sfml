#include "include/entities/Player.h"

Player::Player(int x, int y, std::string name, std::string path) : TexturedElement(x, y, name, path) { 
	this->nbPokemon = 0;
	this->bag.resize(3);
	this->xOnMap = x;
	this->yOnMap = x;
	this->name = name;
	this->path = path;
	this->animeCount = 0;
	this->animePos = std::vector<std::vector<sf::IntRect>>(ANIME_SACHA_RECT);
	if (animePos.empty()) throw("ERROR::LOADING_PLAYER_SPRITE");
	else this->sprite.setTextureRect(this->animePos[0][this->animeCount]);
	this->sprite.setScale(0.6f, 0.6f);
}

int& Player::getNbPokemon() { return this->nbPokemon; }

Pokemon* Player::getTeam() { return this->team; }

std::vector<int> Player::getBag() { return this->bag; }

void Player::addPokemon(Pokemon p) {
	if (this->nbPokemon < 6)
	{
		team[nbPokemon] = p;
		++this->nbPokemon;
	}
}

void Player::removePokemon(Pokemon* p) {
	// not implemented //
}

void Player::addItems(int bag, int added) { this->bag[bag] += added; }

void Player::removeItem(int bag, int sub) { this->bag[bag] -= sub; }

void Player::updatePlayer(int* frameCount, sf::View* view, const int* level, ViewTypes *viewType) {
	

	const int frameUpdater = 300;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
		tileValue = level[(MAPHEIGHT * (yOnMap-1)) + xOnMap];
		if (*frameCount % frameUpdater == 0) {
			if ((tileValue < 4 || tileValue > 13) && !OutOfBoundaries(xOnMap, yOnMap - 1))
			{
				if (CombatTrigger()) *viewType = COMBAT;
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
				if (CombatTrigger()) *viewType = COMBAT;
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
				if (CombatTrigger()) *viewType = COMBAT;
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
				if (CombatTrigger()) *viewType = COMBAT;
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
	this->xOnMap = x;
	this->yOnMap = y;
}

int Player::GetMapPositionX() { return this->xOnMap; }

int Player::GetMapPositionY() { return this->yOnMap; }

bool Player::OutOfBoundaries(int x, int y)
{
	if (x >= MAPWIDTH || x < 0) return true;
	if (y > MAPHEIGHT-1 || y < 0) return true;
	return false;
}

bool Player::CombatTrigger()
{
	srand(time(0));
	int random = (rand() % 100);
	if (tileValue == 1 || tileValue == 14)
	{
		if (random <= 15) return true;
		return false;
	}
	return false;
}

void Player::healPokemon(SprayType type, Pokemon& p) {
	switch (type) {
	case HEAL:
		if (p.currentHealth + 20 <= p.currentStats[HP]) p.currentHealth += 20;
		else p.currentHealth = p.currentStats[HP];
		this->bag[1]--;
		break;
	case RESET:
		for (int i = 0; i < 4; i++) {
			p.getCapacities()[i].current = p.getCapacities()[i].pp;
		}
		this->bag[2]--;
		break;
	}
}


