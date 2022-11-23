#pragma once
# include "Pokemon.h"

class Spray : public TexturedElement {
private:
	int heal;

public:
	Spray();
	~Spray();

	void healPokemon(Pokemon* p);

};

