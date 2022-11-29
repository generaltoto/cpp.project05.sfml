#include "include/entities/Pokemon.h"

Pokemon::Pokemon() = default;

Pokemon::Pokemon(
	int x,
	int y,
	std::string name,
	std::string path,
	std::string type[2],
	std::string caption,
	int level,
	std::vector<int> stats
) {
	this->posX = x;
	this->posY = y;
	this->name = name;
	this->path = path;
	for (int i = 0; i < 2; i++) {
		this->type[i] = type[i];
	}
	this->caption = caption;
	this->levels.level = level;
	this->levels.ExpToNext = level ^ 3;
	this->levels.currentExp = 0;
	initStats(stats, level);
}

Pokemon::~Pokemon() { }

void Pokemon::initStats(std::vector<int> stats, int level) {
	this->baseStats.insert({ HP,stats[0] });
	this->baseStats.insert({ ATK,stats[1] });
	this->baseStats.insert({ ATKSPE,stats[2] });
	this->baseStats.insert({ DEF,stats[3] });
	this->baseStats.insert({ DEFSPE,stats[4] });
	this->baseStats.insert({ VIT,stats[5] });
	this->levels.level = level;
	updateCurrentStat();
}

void Pokemon::levelUp(int expEarn) {
	this->levels.currentExp += expEarn;
	if (this->levels.currentExp >= this->levels.ExpToNext) {
		this->levels.level++;
		this->levels.currentExp -= this->levels.ExpToNext;
		this->levels.ExpToNext = this->levels.level ^ 3;
		updateCurrentStat();
	}
	if (this->levels.level == this->levels.evolveLvl) {
		/*evolve();*/
	}
}

void Pokemon::updateCurrentStat() {
	std::map<Stat, int>::iterator it;

	for (it = this->currentStats.begin(); it != this->currentStats.end(); it++) {
		if (it != this->currentStats.begin()) {
			it->second = int(
				((2 * this->baseStats[it->first]) * this->levels.level) / 100)
				+ 5;
		}
	}
	this->currentStats[HP] = int
	((2 * this->baseStats[HP] * this->levels.level) / 100)
		+ this->levels.level + 10;
}

//Pokemon Pokemon::evolve() {
//	
//}