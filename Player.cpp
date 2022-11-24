# include "Player.h"

Player::Player() { 
	for (int i = 0; i < 6; i++) {
		this->team[i] = NULL;
	}
	this->posX = 10;
	this->posY = 10;
	this->name = "Petit Louis";
	this->path = "assets/sacha.png";
	this->animeCount = 0;
	this->animePos = std::vector<sf::IntRect>(ANIME_SACHA_RECT);
	this->sprite.scale(10, 10);
	if (animePos.size() <= 0)
		throw;

	this->sprite.setTextureRect(this->animePos[this->animeCount]);
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

void Player::move(int x, int y) {
	setPos(this->posX + x, this->posY + y);
}