# pragma once
# include "TexturedElement.h"

class Pokemon : public TexturedElement {
private:
	std::vector<std::string> type;
	std::vector<Capacity> capacities;
	std::string caption;
	Level levels;

public:
	/// Stocks the base stats of the pokemon.
	std::map<Stat, int> baseStats;

	/// Stocks the current stats of the pokemon.
	std::map<Stat, int> currentStats;

	/// Stocks the current health of the pokemon.
	int currentHealth;

	Pokemon();
	Pokemon(
		int x,
		int y,
		std::string name,
		std::string path,
		std::vector<std::string> types,
		std::string caption,
		int level,
		std::vector<int>
	);

	/// Returns the current health and the current stat HP of the pokemon in a vector.
	std::vector<int> getHealthAndMax();

	/// Returns the level structure.
	Level& getLevel();

	/// Initializes the base stats and the current ones.
	void initStats(std::vector<int>, int level);

	/// Ups the level of the pokemon.
	void levelUp(int expEarn);

	/// Updates the current stats of the pokemon using the level.
	void updateCurrentStat();

	/// Returns the capacities of the pokemon.
	std::vector<Capacity>& getCapacities();

	/// Returns the type position in the Types Matrice ('include/date/Types.h')
	int fromTypesToInt(const std::string &typeName);

	/// Returns the efficiency of a given Pokemon against another one.
	float getTypeAdvantage(Pokemon, Pokemon, int);

	/// Attacks a given pokemon with a given capacity index and the attacker
	void pokemonAttack(Pokemon* attacker, Pokemon* defender, const int capacityIndex);

	/// Chooses the best attack to use against a pokemon
	void pokemonIAChoseAttack(Pokemon*, Pokemon*);
};
