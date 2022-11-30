#include "include/entities/Pokemon.h"

Pokemon::Pokemon() = default;

Pokemon::Pokemon(
	int x,
	int y,
	std::string name,
	std::string path,
<<<<<<< HEAD
	std::vector<std::string> types,
	std::string caption,
	int level,
	std::vector<int> stats
=======
	Types type[2],
	Capacity capacities[4],
	/*std::string caption,*/
	int level,
	int stats[6],
	sf::IntRect pokeImg
>>>>>>> feature/audio
) {
	this->posX = x;
	this->posY = y;
	this->name = name;
	this->path = path;
	this->type.resize(types.size());
	for (int i = 0; i < types.size(); i++) 
	{
		this->type[i] = types[i];
	}
	/*this->caption = caption;*/
	this->levels.level = level;
	this->levels.ExpToNext = level ^ 3;
	this->levels.currentExp = 0;
<<<<<<< HEAD
	initStats(stats, level);
}

Pokemon::~Pokemon() { }

void Pokemon::initStats(std::vector<int> stats, int level) {
=======

>>>>>>> feature/audio
	this->baseStats.insert({ HP,stats[0] });
	this->baseStats.insert({ ATK,stats[1] });
	this->baseStats.insert({ ATKSPE,stats[2] });
	this->baseStats.insert({ DEF,stats[3] });
	this->baseStats.insert({ DEFSPE,stats[4] });
	this->baseStats.insert({ VIT,stats[5] });
	updateCurrentStat();

	if (!this->asset.loadFromFile(path)) {
		throw("C K C");
	}
	else {
		this->sprite.setTexture(this->asset);
		this->sprite.setTextureRect(pokeImg);
	}
}

Pokemon::~Pokemon() { }

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
			this->currentStats[it->first] = int(
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