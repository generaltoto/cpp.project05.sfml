#pragma once

#include "include/view/MainWindow.h"
#include "include/entities/Player.h"
#include "include/entities/Pokemon.h"

class CombatManager
{
public:
	/// Context window for view
	static MainWindow *contextWindow;

	/// texture of the background
	static sf::Texture* bgText;

	/// Sprite of the background
	static sf::Sprite* bgSprite;

	/// Context player for combat
	static Player *contextPlayer;

	/// Enemies for the combat
	static std::vector<Pokemon> enemies;

	/// Starts the combat
	static void startCombat();

	/// Main loop for combat
	static void runCombat(MainWindow* window, Player* p, std::vector<Pokemon> &e);

	/// Draws the combat
	static void drawCombat();

	/// Ends combat, deletes objects and changes view
	static void endCombat();
};

