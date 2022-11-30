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

public:
	Player(int, int, std::string name, std::string path);
	~Player();

	/// Returns the number of pokemons in the player's team.
	int& getNbPokemon();

	/// Returns the player's team.
	Pokemon* getTeam();

	/// Returns the player's bag.
	std::vector<int> getBag();

	/// Adds a given pokemon in the team.
	void addPokemon(Pokemon p);

	/// Removes a pokemon in the team.
	void removePokemon(int id);

	/// Adds an item in the player's bag.
	void addItems(int bag, int added);

	/// Removes an item from the bag.
	void removeItem(int bag, int sub);

	/// Updates the player's animation and movement.
	void updatePlayer(int* frameCount, sf::View* view, const int* level);

	/// Sets the position of the player on the map.
	void SetMapPosition(int x, int y);

	/// Returns the x position of the player on the map.
	int GetMapPositionx();

	/// Returns the y position of the player on the map.
	int GetMapPositiony();

	/// Checks if the player is still on the map.
	bool OutOfBoundaries(int x, int y);

	/// Heals a given pokemon depending on the SprayType given.
	void healPokemon(SprayType type, Pokemon& p);
};