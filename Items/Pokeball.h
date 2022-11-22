# pragma once
# include "Pokemon.h"
# include "Player.h"

class Pokeball : protected TexturedElement {
public:
	Pokeball();
	~Pokeball();

	void capture(Pokemon* p, Player* j);
};