# pragma once
#include "TexturedElement.h"
#include "Pokemon.h"
#include "Player.h"

class Pokeball : public TexturedElement {
public:
	Pokeball(int x, int y, std::string name, std::string path);
	~Pokeball();

	void capture(Pokemon* p, Player* j);
};