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
	for (auto it = currentStats.begin(); it != currentStats.end(); ++it) {
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
	for (auto const &t : defending.type) {
		if (ratio != 0) ratio *= typeTable[fromTypesToInt(attacking.getCapacities()[capacity].type)][fromTypesToInt(t)];
		else ratio += typeTable[fromTypesToInt(attacking.getCapacities()[capacity].type)][fromTypesToInt(t)];
	}
	return ratio;
}

int Pokemon::fromTypesToInt(const std::string &typeName) {
	if (typeName == "Normal")   return 0;
	if (typeName == "Fighting") return 1;
	if (typeName == "Flying")   return 2;
	if (typeName == "Poison")   return 3;
	if (typeName == "Ground")   return 4;
	if (typeName == "Rock")     return 5;
	if (typeName == "Bug")      return 6;
	if (typeName == "Ghost")    return 7;
	if (typeName == "Steel")    return 8;
	if (typeName == "Fire")     return 9;
	if (typeName == "Water")    return 10;
	if (typeName == "Grass")    return 11;
	if (typeName == "Electric") return 12;
	if (typeName == "Psychic")  return 13;
	if (typeName == "Ice")      return 14;
	if (typeName == "Dragon")   return 15;
	if (typeName == "Dark")     return 16;
	if (typeName == "Fairy")    return 17;
	return 0;
}

void Pokemon::pokemonAttack(Pokemon* attacker, Pokemon* defender, const int capacityIndex)
{
	if (attacker->getCapacities()[capacityIndex].attackType == "physic" && attacker->getCapacities()[capacityIndex].current > 0)
	{
		attacker->getCapacities()[capacityIndex].current--;
		defender->currentHealth -= round(((((attacker->getLevel().level * 0.4 + 2) * attacker->currentStats[ATK] * (
			attacker->getCapacities()[capacityIndex].damage) / (attacker->currentStats[DEF] * 50)) + 2) * attacker->getTypeAdvantage(*attacker, *defender, capacityIndex))
		);
	}
	else if (attacker->getCapacities()[capacityIndex].attackType == "special" && attacker->getCapacities()[capacityIndex].current > 0)
	{
		attacker->getCapacities()[capacityIndex].current--;
		defender->currentHealth -= round(((((attacker->getLevel().level * 0.4 + 2) * attacker->currentStats[ATKSPE] * (
			attacker->getCapacities()[capacityIndex].damage) / (attacker->currentStats[DEFSPE] * 50)) + 2) * attacker->getTypeAdvantage(*attacker, *defender, capacityIndex))
		);
	}
}

void Pokemon::pokemonIAChoseAttack(Pokemon* attacker, Pokemon* defender) {
	int capaToCast = 0;
	int currentCapa = 0;
	for (int i = 0; i < attacker->getCapacities().size(); i++) {
		if (attacker->getCapacities()[i].attackType == "physic")
		{
			currentCapa = attacker->currentStats[ATK] * attacker->getCapacities()[i].damage * (
				attacker->getTypeAdvantage(*attacker, *defender, capaToCast)
				);
		}
		else if (attacker->getCapacities()[i].attackType == "special")
		{
			currentCapa = attacker->currentStats[ATKSPE] * attacker->getCapacities()[i].damage * (
				attacker->getTypeAdvantage(*attacker, *defender, capaToCast)
				);
		}
		else if (attacker->getCapacities()[i].attackType == "status") {
			currentCapa = 0;
		}
		if (i == 0 || currentCapa > capaToCast) capaToCast = i;
	}

	this->pokemonAttack(attacker, defender, capaToCast);
	
}