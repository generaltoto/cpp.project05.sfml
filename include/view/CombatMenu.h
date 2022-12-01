#pragma once

#include "MainWindow.h"

class CombatMenu
{
private:
	MainWindow* contextWindow;
	Player* contextPlayer;

	sf::RectangleShape mainShape;
	sf::Vector2f mainPos;
	sf::Vector2f mainSize;
	sf::RectangleShape pokemonSlot;

	sf::Color activeColor = { 127,127,127,127 };
	sf::Color activeTextColor = { 255, 255, 255, 255 };

	sf::Color basicColor = { 245, 245, 245, 245 };
	sf::Color basicTextColor = { 0, 0, 0, 255 };

	void drawPokeImage(int, sf::Vector2f);

	void drawPokeText(int, const int);

	void drawPokeSlot();

	void drawShapes();

public:
	int activeIndex;

	CombatMenu(MainWindow*, Player*);

	void navigateMenu();

	void drawMenu();
};

