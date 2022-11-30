#pragma once
#include "TexturedElement.h"
#include "Pokemon.h"

class Spray : public TexturedElement {
private:
	int heal = 50;
	SprayType type;

public:
	Spray(SprayType, std::string path);
	~Spray();

	void updatePokemon(Pokemon* p);

};