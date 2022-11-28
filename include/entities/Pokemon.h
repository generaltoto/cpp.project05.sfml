# pragma once
# include "TexturedElement.h"

class Pokemon : public TexturedElement {
private:
	Types type[2];
	Capacity capacities[4];
	std::string caption;
	struct Level levels;
	//Audio;

public:
	std::map<Stat, int> baseStats;
	std::map<Stat, int> currentStats;

	Pokemon(
		int x,
		int y,
		std::string name,
		std::string path,
		Types type[2],
		Capacity capacities[4],
		std::string caption,
		int level
	);
	~Pokemon();

	void initStats(int stats[6], int level);

	void levelUp(int expEarn);

	void updateCurrentStat();

	/*Pokemon evolve();*/
};
