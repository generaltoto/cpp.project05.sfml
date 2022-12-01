#include "include/view/CombatMenu.h"

CombatMenu::CombatMenu(MainWindow* mainWindow, Player* player)
{
	this->contextWindow = mainWindow;
	this->contextPlayer = player;
	this->mainPos = { 1400,600 };
	this->mainSize = { 773, 450 };
	this->selfPokemonPos = { 480,750 };
	this->selfPokemonScaleSize = { 5.75f, 5.75f };
	this->activeIndex = 3;
}

void CombatMenu::drawPokeImage(int i, sf::Vector2f slotPos)
{
	this->contextPlayer->getTeam()[i].getSprite().setScale(1.5f, 1.5f);
	this->contextPlayer->getTeam()[i].getSprite().setPosition(slotPos);
	this->contextWindow->getWindow()->draw(this->contextPlayer->getTeam()[i].getSprite());
}

void CombatMenu::drawPokeText(int i, const int assetSize)
{
	sf::Text txt;
	txt.setFont(this->contextWindow->getFont());

	// drawing pokemon name 
	txt.setString(this->contextPlayer->getTeam()[i].getName());
	txt.setCharacterSize(20);
	txt.setOutlineColor(sf::Color::Black);
	txt.setOutlineThickness(5);
	txt.setPosition(
		this->contextPlayer->getTeam()[i].getSprite().getPosition().x + assetSize + assetSize / 2.f,
		this->contextPlayer->getTeam()[i].getSprite().getPosition().y + 20
	);
	this->contextWindow->getWindow()->draw(txt);

	txt.setOutlineThickness(0);
	txt.setCharacterSize(15);
	txt.setColor(this->basicTextColor);

	//drawing pokemon level
	txt.setString("Level : " + std::to_string(this->contextPlayer->getTeam()[i].getLevel().level));
	txt.setPosition(
		this->contextPlayer->getTeam()[i].getSprite().getPosition().x + assetSize + assetSize / 2.f,
		this->contextPlayer->getTeam()[i].getSprite().getPosition().y + 55
	);
	this->contextWindow->getWindow()->draw(txt);

	//drawing pokemon hp
	txt.setString("HP : " +
		std::to_string(this->contextPlayer->getTeam()[i].getHealthAndMax()[0]) +
		"/" +
		std::to_string(this->contextPlayer->getTeam()[i].getHealthAndMax()[1])
	);
	txt.setPosition(
		this->contextPlayer->getTeam()[i].getSprite().getPosition().x + assetSize + assetSize / 2.f,
		this->contextPlayer->getTeam()[i].getSprite().getPosition().y + 95
	);
	this->contextWindow->getWindow()->draw(txt);
}

void CombatMenu::drawPokeSlot()
{
	const int assetSize = 40;
	for (int i = 0; i < this->contextPlayer->getNbPokemon(); i++)
	{
		if (this->activeIndex == i)
			this->pokemonSlot.setFillColor(this->activeColor);
		else this->pokemonSlot.setFillColor(this->basicColor);

		sf::Vector2f slotPos;
		if (i - 2 < 1)
		{
			slotPos = {
				float(this->mainPos.x + this->mainSize.x * 0.05),
				float(this->mainPos.y + this->mainSize.y * 0.05 + ((this->mainSize.y / 3) * i))
			};
		}
		else
		{
			slotPos = {
				float(this->mainPos.x + this->mainSize.x * 0.05 + (this->mainSize.y / 2)),
				float(this->mainPos.y + this->mainSize.y * 0.05 + ((this->mainSize.y / 3) * (i - 3)))
			};
		}
		this->pokemonSlot.setPosition(slotPos);
		this->pokemonSlot.setSize(
			{ 256, 122 }
		);
		this->contextWindow->getWindow()->draw(this->pokemonSlot);
		drawPokeImage(i, slotPos);
		drawPokeText(i, assetSize);
	}
}

void CombatMenu::drawShapes()
{
	this->mainShape.setFillColor(this->basicColor);
	this->mainShape.setPosition(this->mainPos);
	this->mainShape.setSize(this->mainSize);
	this->contextWindow->getWindow()->draw(this->mainShape);
}

void CombatMenu::drawSelectedPokemon()
{
	
	this->contextPlayer->getTeam()[activeIndex].getSprite().setPosition(this->selfPokemonPos);
	this->contextPlayer->getTeam()[activeIndex].getSprite().setScale(this->selfPokemonScaleSize);
	this->contextWindow->getWindow()->draw(this->contextPlayer->getTeam()[activeIndex].getSprite());
}

void CombatMenu::navigateMenu()
{
}

void CombatMenu::drawMenu()
{
	this->drawShapes();
	this->drawPokeSlot();
	this->drawSelectedPokemon();
}
