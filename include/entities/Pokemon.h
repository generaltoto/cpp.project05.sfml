# pragma once
# include "TexturedElement.h"

class Pokemon : public TexturedElement {
private:
	std::vector<std::string> type;
	Capacity capacities[4];
	std::string caption;
	struct Level levels;
	//Audio;

public:
	std::map<Stat, int> baseStats;
	std::map<Stat, int> currentStats;

	Status pokemonStatus;

	Pokemon();
	Pokemon(
		int x,
		int y,
		std::string name,
		std::string path,
<<<<<<< HEAD
		std::vector<std::string> types,
		std::string caption,
		int level,
		std::vector<int>
	);
	~Pokemon();

	void initStats(std::vector<int>, int level);

=======
		Types type[2],
		Capacity capacities[4],
		/*std::string caption,*/
		int level,
		int stats[6],
		sf::IntRect pokeImg
	);
	~Pokemon();

>>>>>>> feature/audio
	void levelUp(int expEarn);

	void updateCurrentStat();

	/*Pokemon evolve();*/
};
