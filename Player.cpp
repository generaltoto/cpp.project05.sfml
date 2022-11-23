# include "Player.h"

Player::Player() { 
	//for (int i = 0; i < 6; i++) {
	//	this->team[i] == NULL;
	//}
}

Player::~Player() { }

void Player::addPokemon(Pokemon* p) {
	//for (int i = 0; i < 6; i++) {
	//	if (this->team[i] != NULL) {
	//		this->team[i] = p;
	//	}
	//}
}

void Player::removePokemon(int id) {

}

void Player::addItem(int bag, int added) { this->bag[bag] += added; }

void Player::removeItem(int bag, int sub) { this->bag[bag] -= sub; }

void Player::move() {

}