#pragma once

#include "MainWindow.h"

class CombatMenu
{
private:
	MainWindow* contextWindow;
	Player* contextPlayer;

	sf::Texture* bgText;
	sf::Sprite bgSprite;

	std::vector<Pokemon>* enemies;

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

	sf::Color basicColor = { 225, 225, 225, 225 };
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
	void drawAttacksSlots(Pokemon*);
	void drawAttacksText(Capacity capa, int i);
	void drawSelectedPokemon();
	void drawSelectAction();

public:
	bool activeCombat;

	int activePokemonIdx;
	int selectedPokemonIdx;
	int selectedAttackIdx;
	int sideNavigate = 0;

	int currentSelected;
	CombatAction currentView;

	CombatMenu(MainWindow*, Player*);

	void initCombatEnemies(std::vector<Pokemon>* e, bool* loaded);

	/// Loads a random enemy team depending on the encouter type
	void loadEnemy(Pokemon p);

	/// Navigation through pokemon selection for combat
	void navigate(Sound*, ViewTypes*, bool*);

	/// Navigates through pokemon's capacity.
	void navigateAttacks(Sound* soundEffect);

	/// Navigates through pokemon team in combat.
	void navigatePokemon(Sound* soundEffect);

	/// Draws the entire menu
	void drawMenu();

};

