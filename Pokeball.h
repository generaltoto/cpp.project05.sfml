# pragma once
# include "Pokemon.h"
# include "Player.h"

class Pokeball : public TexturedElement {
public:
	Pokeball();
	~Pokeball();

	void capture(Pokemon* p, Player* j);
};