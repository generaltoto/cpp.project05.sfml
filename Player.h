# pragma once
# include "TexturedElement.h"
# include "Pokemon.h"

class Player : public TexturedElement {
private:
	Pokemon* team[6];
	int xOnMap, yOnMap;
	int bag[2];

public:
	Player();
	~Player();

	void addPokemon(Pokemon* p);

	void removePokemon(int id);

	void addItem(int bag, int added);

	void removeItem(int bag, int sub);

	void updatePlayer(int* frameCount);
};