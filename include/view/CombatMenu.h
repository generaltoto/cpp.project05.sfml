#pragma once

#include "MainWindow.h"

class CombatMenu
{
private:
	MainWindow* contextWindow;
	Player* contextPlayer;

	sf::Texture* bgText;
	sf::Sprite bgSprite;

	Pokemon* enemies;

	// Lots of variables for element positions and colors
	sf::RectangleShape mainShape;
	sf::Vector2f mainPos;
	sf::Vector2f mainSize;
	sf::RectangleShape pokemonSlot;
	sf::RectangleShape attackSlot;

	sf::Vector2f attackerPokemonPos;
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
	void drawAttacker();
	void drawAttackerSlot(Pokemon*);
	void drawDefenderSlot(Pokemon*);
	void drawTeam();
	void drawPokeImage(int, sf::Vector2f);
	void drawPokeText(int);
	void drawAttacksSlots(Pokemon*);
	void drawAttacksText(Capacity capa, int i);
	void drawSelectedPokemon();
	void drawSelectAction();

public:
	/// Indicates if a combat in running or not (when we go back to menu and press play)
	bool activeCombat;

	/// Team pokemon currently in battle
	int activePokemonIdx;

	/// Selected pokemon in selection menu (the one highlighted)
	int selectedPokemonIdx;

	/// Selected attack in selection menu (the one highlighted)
	int selectedAttackIdx;

	/// Selected tab in combat menu
	int sideNavigate = 0;

	int currentSelected;
	CombatAction currentView;

	CombatMenu(MainWindow*, Player*);

	/// Loads a random attacker team depending on the encouter type
	void loadAttacker(Pokemon* p, bool* loaded);

	/// Navigation through pokemon selection for combat
	void navigate(Sound*, ViewTypes*, bool*);

	/// Navigates through pokemon's capacity.
	void navigateAttacks(Sound* soundEffect);

	/// Navigates through pokemon team in combat.
	void navigatePokemon(Sound* soundEffect);

	/// Plays the turn of each pokemon.
	void attackTurn(Sound*);

	/// Checks if a pokemon is dead after an attack.
	/// Then, destroys the pokemon if needed.
	/// \return false is combat is ended
	///	\return true if combat is still running
	bool isCombatActive(Sound*);

	/// Draws the entire menu
	void drawMenu();
};

