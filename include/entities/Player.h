# pragma once
# include "TexturedElement.h"
# include "Pokemon.h"

class Player : public TexturedElement {
private:
	std::vector<Pokemon> team;
	int xOnMap, yOnMap;
	std::vector<int> bag;
	int tileValue = 0;

public:
	bool isFighting = false;
	Player();
	~Player();

	std::vector<Pokemon> getTeam();

	std::vector<int> getBag();

	void addPokemon(Pokemon p);

	void removePokemon(int id);

	void addItems(int bag, int added);

	void removeItem(int bag, int sub);

	void updatePlayer(int* frameCount, sf::View* view, const int* level, ViewTypes* viewType);

	void SetMapPosition(int x, int y);

	int GetMapPositionx();

	int GetMapPositiony();

	bool OutOfBoundaries(int x, int y);

	bool CombatTrigger();
};