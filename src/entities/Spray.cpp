# include "include/entities/Spray.h"

Spray::Spray(SprayType st, int x, int y, std::string name, std::string path) : TexturedElement(x, y, name, path) 
{ 
	this->type = st;
}

Spray::~Spray() { }

void Spray::updatePokemon(Pokemon* p) {
	switch (this->type)
	{
	case HEAL:
		p->currentStats[HP] += this->heal;
		break;
	case RESET:
		break;
	default:
		break;
	}
}