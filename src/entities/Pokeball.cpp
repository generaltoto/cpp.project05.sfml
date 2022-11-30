#include "include/entities/Pokeball.h"

Pokeball::Pokeball(int x, int y, std::string name, std::string path) : TexturedElement(x, y , name, path) { }

Pokeball::~Pokeball() { }

void Pokeball::capture(Pokemon* p, Player* j) {
	/*j->addPokemon(p);*/
}