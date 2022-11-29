#pragma once
#include "json.hpp"

using json = nlohmann::json;

class DataManager
{
public:
	/// Returns a specified move
	json static getMove(int);
	
	/// Returns a specified pokemon
	json static getPokemon(int);

	/// Returns all moves
	json static getAllMoves();

	/// Returns all pokemons
	json static getAllPokemons();

	/// Template of a move in the Json
	json static templateMove(int timeC, int timeT, int quantity, bool eat, bool vomited);
	
	/// Template of a pokemon in the Json
	json static templatePokemon(int quantity);
};

