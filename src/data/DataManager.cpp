#include "include/data/DataManager.h"

using namespace std;
using json = nlohmann::json;

inline json DataManager::getMove(int id) { return DataManager::getAllPokemons()[id - 1]; }

inline json DataManager::getPokemon(int id) { return DataManager::getAllPokemons()[id - 1]; }

inline json DataManager::getAllMoves()
{
	ifstream file("include/data/moves.json");
	return json::parse(file);
}

inline json DataManager::getAllPokemons()
{
	ifstream file("include/data/pokedex.json");
	return json::parse(file);
}

json DataManager::templateMove(int timeC, int timeT, int quantity, bool eat, bool vomited)
{
	json tempFeeder =
	{
		{"timeCreated", timeC}, //time_t
		{"timeTaken", timeT}, //time_t
		{"quantity", quantity}, //int
		{"isEated", eat},
		{"isVomited", vomited} //bool
	};
	return tempFeeder;
}

json DataManager::templatePokemon(int quantity)
{
	json tempProduct =
	{
		{"quantity", quantity}, //int
	};
	return tempProduct;
}