#include "include/entities/Pokemon.h"

Pokemon::Pokemon() = default;

Pokemon::Pokemon(
	int x,
	int y,
	std::string name,
	std::string path,
	std::vector<std::string> types,
	std::string caption,
	int level,
	std::vector<int> stats
) : TexturedElement(x, y, name, path) {
	this->posX = x;
	this->posY = y;
	this->name = name;
	this->path = path;
	this->type.resize(types.size());
	for (int i = 0; i < types.size(); i++) 
	{
		this->type[i] = types[i];
	}
	this->caption = caption;
	this->levels.level = level;
	this->levels.ExpToNext = level ^ 3;
	this->levels.currentExp = 0;
	initStats(stats, level);
	this->currentHealth = this->currentStats[HP];
}

std::vector<int> Pokemon::getHealthAndMax()
{
	return std::vector<int>{ this->currentHealth, this->currentStats[HP] };
}

Level& Pokemon::getLevel()
{
	return this->levels;
}

void Pokemon::initStats(std::vector<int> stats, int level) {
	this->baseStats.insert({ HP,stats[0] });
	this->baseStats.insert({ ATK,stats[1] });
	this->baseStats.insert({ ATKSPE,stats[2] });
	this->baseStats.insert({ DEF,stats[3] });
	this->baseStats.insert({ DEFSPE,stats[4] });
	this->baseStats.insert({ VIT,stats[5] });
	updateCurrentStat();
}

void Pokemon::levelUp(int expEarn) {
	this->levels.currentExp += expEarn;
	if (this->levels.currentExp >= this->levels.ExpToNext) {
		this->levels.level++;
		this->levels.currentExp -= this->levels.ExpToNext;
		this->levels.ExpToNext = this->levels.level ^ 3;
		updateCurrentStat();
		this->currentHealth += 1 + ((2 * this->baseStats[HP]) / 100);
	}
	if (this->levels.level == this->levels.evolveLvl) {
		/*evolve();*/
	}
}

void Pokemon::updateCurrentStat() {
	std::map<Stat, int>::iterator it;

	for (it = this->currentStats.begin(); it != this->currentStats.end(); it++) {
		if (it != this->currentStats.begin()) {
			this->currentStats[it->first] = int(
				((2 * this->baseStats[it->first]) * this->levels.level) / 100)
				+ 5;
		}
	}
	this->currentStats[HP] = int((2 * this->baseStats[HP] * this->levels.level) / 100)
		+ this->levels.level + 10;
}

Capacity* Pokemon::getCapacities() { return this->capacities; }

//Pokemon Pokemon::evolve() {
//	
//}