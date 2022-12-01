#pragma once

#include "include/view/MainWindow.h"
#include "include/entities/Player.h"
#include "include/entities/Pokemon.h"
#include "include/view/CombatMenu.h"

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

	/// True if the player is currently in a combat (for menu gestion)
	static bool activeCombat;

	/// Starts the combat
	static void initCombatContexts(MainWindow*);

	/// Loads the enemies once.
	static void initCombatEnemies(std::vector<Pokemon>, bool*);

	/// Main loop for combat. 
	/// \return False when the combat is over
	static bool runCombat();

	/// Draws the combat
	static void updateCombat();

	/// Ends combat, deletes objects and changes view
	static void endCombat();
};

