# pragma once
# include "TexturedElement.h"
# include "Pokemon.h"

class NPC : protected TexturedElement {
private:
	Pokemon team[6];
	std::string dialogs[10];

public:
	NPC();
	~NPC();

	void movePattern();
};