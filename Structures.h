# pragma once
# include <string>
# include <SFML/Graphics.hpp>
# include <SFML/Audio.hpp>
# include <SFML/Window.hpp>
# include <SFML/System.hpp>

enum Types { FIGHT, DRAKE, WATER, ELEC, FIRE, ICE, BUG, POISON, PSY, ROCK, GROUND, GHOST, FLY };

enum Stat { HP, ATK, ATKSPE, DEF, DEFSPE, VIT };

enum Status { POISONED, SLEPT, BURNING, PARALYSED };

enum ViewTypes { MENU, PLAY, COMBAT };

struct Capacity {
	int damage;
	bool isPhysical;
	Types type[1];
	int accuracy;
	std::string description;
};

struct Level {
	int level, currentExp, ExpToNext, evolveLvl; //ExpToNext = level^3
};

#define ANIME_SACHA_RECT {\
	{	sf::IntRect(0, 0, 110, 140),sf::IntRect(160, 0, 110, 140),sf::IntRect(330, 0, 110, 140), sf::IntRect(490, 0, 110, 140) },\
	{	sf::IntRect(0, 160, 110, 140), sf::IntRect(160, 160, 110, 140), sf::IntRect(330, 160, 110, 140), sf::IntRect(490, 160, 110, 140) },\
	{	sf::IntRect(0, 330, 110, 140), sf::IntRect(160, 330, 110, 140), sf::IntRect(330, 330, 110, 140), sf::IntRect(490, 330, 110, 140) },\
	{ sf::IntRect(0, 490, 110, 140), sf::IntRect(160, 490, 110, 140), sf::IntRect(330, 490, 110, 140), sf::IntRect(490, 490, 110, 140) },\
}