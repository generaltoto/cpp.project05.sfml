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
	sf::RectangleShape attackSlot;

	sf::Vector2f enemyPokemonPos;
	sf::Vector2f selfPokemonPos;
	sf::Vector2f inGamePokemonScaleSize;
	sf::Vector2f statPokemonScaleSize;
	const int assetSize = 40;

	sf::Color activeColor = { 127,127,127,127 };
	sf::Color activeTextColor = { 255, 255, 255, 255 };

	sf::Color basicColor = { 245, 245, 245, 245 };
	sf::Color basicTextColor = { 0, 0, 0, 255 };

	std::vector<const char*> options;
	std::vector<sf::Text> texts;
	std::vector<std::size_t> sizes;

	std::vector<sf::Vector2f> zoneCoords;
	sf::Vector2f zoneSize;
	std::vector<sf::RectangleShape> zones;

	enum CombatAction { ATTACKS, TEAM };

	void drawShape();
	void drawEnemy();
	void drawEnemySlot(Pokemon);
	void drawTeam();
	void drawPokeImage(int, sf::Vector2f);
	void drawPokeText(int);
	void drawAttacks(Pokemon*);
	void drawSelectedPokemon();
	void drawSelectAction();

public:
	bool activeCombat;

	int selectedPokemonIdx;
	int selectedAttackIdx;

	int currentSelected;
	CombatAction currentView;

	CombatMenu(MainWindow*, Player*);

	void initCombatEnemies(std::vector<Pokemon> e, bool* loaded);

	/// Navigation through pokemon selection for combat
	void navigate(Sound* soundEffect, ViewTypes* currentView);

	/// Draws the entire menu
	void drawMenu();
};

