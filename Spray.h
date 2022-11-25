#pragma once
# include "Pokemon.h"  

class Spray : public TexturedElement {
private:
	int heal = 50;

public:
	Spray();
	~Spray();

	void healPokemon(Pokemon* p);

};