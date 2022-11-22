# pragma once
# include "TexturedElement.h"
# include "Pokemon.h"

class Player : protected TexturedElement {
private:
	Pokemon team[6];
	int bag[2];

public:
	Player();
	~Player();

	void addPokemon(Pokemon p);

	void removePokemon(int id);

	void addItem(int bag, int added);

	void removeItem(int bag, int sub);

	void move();
};