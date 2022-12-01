#include "include/entities/Pokemon.h"
#include "include/data/Types.h"

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
	
	this->currentStats.insert({ HP,0 });
	this->currentStats.insert({ ATK,0 });
	this->currentStats.insert({ ATKSPE,0 });
	this->currentStats.insert({ DEF,0 });
	this->currentStats.insert({ DEFSPE,0 });
	this->currentStats.insert({ VIT,0 });
	std::map<Stat, int>::iterator it;
	for (it = currentStats.begin(); it != currentStats.end(); it++) {
		if (it != this->currentStats.begin()) {
			this->currentStats[it->first] =
				(((2 * this->baseStats[it->first]) 
					* this->levels.level) / 100) + 5;
		}
	}
	this->currentStats[HP] = int((2 * this->baseStats[HP] * this->levels.level) / 100)
		+ this->levels.level + 10;
}

std::vector<Capacity>& Pokemon::getCapacities() { return this->capacities; }

float Pokemon::getTypeAdvantage(Pokemon attacking, Pokemon defending, int capacity)
{
	float ratio = 0;
	for (int x = 0; x < defending.type.size(); x++) {
		if (ratio != 0) ratio *= typeTable[fromTypesToInt(attacking.getCapacities()[capacity].type)][fromTypesToInt(defending.type[x])];
		else ratio += typeTable[fromTypesToInt(attacking.getCapacities()[capacity].type)][fromTypesToInt(defending.type[x])];
	}
	return ratio;
}

int Pokemon::fromTypesToInt(std::string typeName) {
	if (typeName == "Normal") return 0;
	else if (typeName == "Fighting") return 1;
	else if (typeName == "Flying") return 2;
	else if (typeName == "Poison") return 3;
	else if (typeName == "Ground") return 4;
	else if (typeName == "Rock") return 5;
	else if (typeName == "Bug") return 6;
	else if (typeName == "Ghost") return 7;
	else if (typeName == "Steel") return 8;
	else if (typeName == "Fire") return 9;
	else if (typeName == "Water") return 10;
	else if (typeName == "Grass") return 11;
	else if (typeName == "Electric") return 12;
	else if (typeName == "Psychic") return 13;
	else if (typeName == "Ice") return 14;
	else if (typeName == "Dragon") return 15;
	else if (typeName == "Dark") return 16;
	else if (typeName == "Fairy") return 17;
	else return 0;
}


int Pokemon::enemyAttack(Pokemon enemy, Pokemon ally) {
	int capaALancer = 0;
	int currentCapa = 0;
	for (int i = 0; i < enemy.getCapacities().size(); i++) {
		if (enemy.getCapacities()[i].attackType == "physic")
		{
			currentCapa = enemy.currentStats[ATK] * enemy.getCapacities()[i].damage * enemy.getTypeAdvantage(enemy, ally, capaALancer);
		}
		else if (enemy.getCapacities()[i].attackType == "special")
		{
			currentCapa = enemy.currentStats[ATKSPE] * enemy.getCapacities()[i].damage * enemy.getTypeAdvantage(enemy, ally, capaALancer);
		}
		if (i == 0 || currentCapa > capaALancer)
		{
			capaALancer = i;
		}
	}
	if (enemy.getCapacities()[capaALancer].attackType == "physic")
	{
		ally.currentHealth -= round(((((enemy.getLevel().level * 0.4 + 2) * enemy.currentStats[ATK] * enemy.getCapacities()[capaALancer].damage) / (enemy.currentStats[DEF] * 50)) + 2) * enemy.getTypeAdvantage(enemy, ally, capaALancer));
	}
	else if (enemy.getCapacities()[capaALancer].attackType == "special")
	{
		ally.currentHealth -= round(((((enemy.getLevel().level * 0.4 + 2) * enemy.currentStats[ATKSPE] * enemy.getCapacities()[capaALancer].damage) / (enemy.currentStats[DEFSPE] * 50)) + 2) * enemy.getTypeAdvantage(enemy, ally, capaALancer));
	}
	return ally.currentHealth;
	std::cout << "curent health :" << ally.currentHealth  << std::endl;
	std::cout <<"dmg inflicted :" << round(((((enemy.getLevel().level * 0.4 + 2) * enemy.currentStats[ATKSPE] * enemy.getCapacities()[capaALancer].damage) / (enemy.currentStats[DEFSPE] * 50)) + 2) * enemy.getTypeAdvantage(enemy, ally, capaALancer)) << std::endl;
}
//Pokemon Pokemon::evolve() {
//	
//}