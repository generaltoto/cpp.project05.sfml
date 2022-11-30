# pragma once
# include "Player.h"

class NPC : public TexturedElement {
private:
	Pokemon* team[6];
	std::string dialogs[10];

public:
	NPC(int x, int y, std::string name, std::string path);
	~NPC();

	void movePattern();
};