# pragma once
# include <string>

enum Types { FIGHT, DRAKE, WATER, ELEC, FIRE, ICE, BUG, POISON, PSY, ROCK, GROUND, GHOST, FLY };

enum Stat { HP, ATK, ATKSPE, DEF, DEFSPE, VIT };

enum Status { POISONED, SLEPT, BURNING, PARALYSED };

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
