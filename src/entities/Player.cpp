#include "include/entities/Player.h"

Player::Player() { 
	for (int i = 0; i < 6; i++) {
		this->team[i] = NULL;
	}
	sf::VideoMode* size = new sf::VideoMode();
	this->xOnMap = 10;
	this->yOnMap = 10;
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

void Player::updatePlayer(int* frameCount) {
	const int frameUpdater = 600;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
		this->yOnMap += 1;
		if (*frameCount % frameUpdater == 0) {
			nextAnimation(3);
			*frameCount = 0;
		}
		return;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
		this->yOnMap -= 1;
		if (*frameCount % frameUpdater == 0) {
			nextAnimation(0);
			*frameCount = 0;
		}
		return;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
		this->xOnMap += 1;
		if (*frameCount % frameUpdater == 0) {
			nextAnimation(2);
			*frameCount = 0;
		}
		return;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
		this->xOnMap -= 1;
		if (*frameCount % frameUpdater == 0) {
			nextAnimation(1);
			*frameCount = 0;
		}
		return;
	}
	this->animeCount = 0;
}