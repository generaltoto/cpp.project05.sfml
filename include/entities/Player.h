# pragma once
# include "TexturedElement.h"
# include "Pokemon.h"
# include "include/map/MapGenerator.h"


class Player : public TexturedElement {
private:
	int nbPokemons;
	Pokemon team[6];
	int xOnMap, yOnMap;
	std::vector<int> bag;
	int tileValue = 0;

public:
	Player(int, int, std::string name, std::string path);

	int& getNbPokemon();

	Pokemon* getTeam();

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