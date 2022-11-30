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

	void initStats(std::vector<int>, int level);
	void levelUp(int expEarn);

	void updateCurrentStat();

	/*Pokemon evolve();*/
};
