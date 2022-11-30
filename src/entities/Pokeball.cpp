#include "include/entities/Pokeball.h"

Pokeball::Pokeball(std::string path) : TexturedElement(path) { }

Pokeball::~Pokeball() { }

void Pokeball::capture(Pokemon* p, Player* j) {
	/*j->addPokemon(p);*/
}