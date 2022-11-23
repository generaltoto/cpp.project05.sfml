# include "Pokemon.h"

Pokemon::Pokemon(
	int x,
	int y,
	std::string name,
	std::string path,
	Types type[2],
	Capacity capacities[4],
	std::string caption,
	int level
) {
	this->posX = x;
	this->posY = y;
	this->name = name;
	this->path = path;
	for (int i = 0; i < 2; i++) {
		this->type[i] = type[i];
	}
	for (int i = 0; i < 4; i++) {
		this->capacities[i] = capacities[i];
	}
	this->caption = caption;
	this->levels.level = level;
	this->levels.ExpToNext = level ^ 3;
	this->levels.currentExp = 0;
}

Pokemon::~Pokemon() { }