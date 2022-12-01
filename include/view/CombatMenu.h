#pragma once

#include "MainWindow.h"

class CombatMenu
{
private:
	MainWindow* contextWindow;
	Player* contextPlayer;

	sf::Texture* bgText;
	sf::Sprite bgSprite;

	std::vector<Pokemon> enemies;

	// Lots of variables for element positions and colors
	sf::RectangleShape mainShape;
	sf::Vector2f mainPos;
	sf::Vector2f mainSize;
	sf::RectangleShape pokemonSlot;

	sf::Vector2f selfPokemonPos;
	sf::Vector2f inGamePokemonScaleSize;
	sf::Vector2f statPokemonScaleSize;
	const int assetSize = 40;

	sf::Color activeColor = { 127,127,127,127 };
	sf::Color activeTextColor = { 255, 255, 255, 255 };

	sf::Color basicColor = { 245, 245, 245, 245 };
	sf::Color basicTextColor = { 0, 0, 0, 255 };

	void drawEnemy();
	void drawEnemySlot(Pokemon);
	void drawPokeImage(int, sf::Vector2f);
	void drawPokeText(int);
	void drawPokeSlot();
	void drawShape();
	void drawSelectedPokemon();

public:
	bool activeCombat;

	int activeIndex;

	CombatMenu(MainWindow*, Player*);

	void initCombatEnemies(std::vector<Pokemon> e, bool* loaded);

	/// Navigation through pokemon selection for combat
	void navigate();

	/// Draws the entire menu
	void drawMenu();
};

