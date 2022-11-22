# pragma once
# include "TexturedElement.h"

class Pokemon : protected TexturedElement {
private:
	Types type[2];
	Capacity capacities[4];
	std::string caption;
	struct Level;
	//Audio;

public:
	std::map<Stat, int> Stats;

	Pokemon();
	~Pokemon();

};
