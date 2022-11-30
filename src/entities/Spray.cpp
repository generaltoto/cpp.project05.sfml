# include "include/entities/Spray.h"

Spray::Spray(SprayType st, std::string path) : TexturedElement(path) { this->type = st; }

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