# pragma once
# include <string>

enum Types { FIGHT, DRAKE, WATER, ELEC, FIRE, ICE, BUG, POISON, PSY, ROCK, GROUND, GHOST, FLY };

enum Stat { HP, ATK, ATKSPE, DEF, DEFSPE, VIT };

enum Status { POISON, SLEEP, BURN, PARALYSIS };

struct Capacity {
	int damage;
	bool isPhysical;
	Types type[1];
	int accuracy;
	std::string description;
};

struct Level {
	int level, currentExp, ExpToNext; //ExpToNext = level^3
};

/*
{
	{ HP, 0 },
	{ ATK, 0 },
	{ ATKSPE, 0 },
	{ DEF, 0 },
	{ DEFSPE, 0 },
	{ VIT, 0 }
};
*/