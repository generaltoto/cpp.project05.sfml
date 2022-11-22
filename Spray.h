#pragma once
# include "Pokemon.h"

class Spray : protected TexturedElement {
private:
	int heal;

public:
	Spray();
	~Spray();

	void healPokemon(Pokemon* p);

};

