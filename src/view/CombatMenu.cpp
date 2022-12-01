#include "include/view/CombatMenu.h"

CombatMenu::CombatMenu(MainWindow* mainWindow, Player* player)
{
	this->contextWindow = mainWindow;
	this->contextPlayer = player;
	this->mainPos = { 1400,600 };
	this->mainSize = { 773, 450 };
	this->selfPokemonPos = { 480,750 };
	this->inGamePokemonScaleSize = { 5.75f, 5.75f };
	this->statPokemonScaleSize = { 3.f, 3.f };
	this->activeIndex = 0;
	this->activeCombat = false;
	this->enemies = {};

	this->bgText = new sf::Texture();
	if (this->bgText->loadFromFile("assets/combat.png"))
	{
		this->bgSprite.setTexture(*this->bgText);
	}
	else throw("ERROR::LOADING_COMBAT_BACKGROUND");
}

void CombatMenu::initCombatEnemies(std::vector<Pokemon> e, bool* loaded)
{
	this->enemies = e;
	*loaded = true;
}

void CombatMenu::drawEnemy()
{
	for (auto& it : this->enemies)
	{
		if (it.currentHealth <= 0) continue;
		else
		{
			it.getSprite().setScale(inGamePokemonScaleSize);
			it.getSprite().setPosition(1240, 330);
			contextWindow->getWindow()->draw(it.getSprite());

			drawEnemySlot(it);
			break;
		}
	}
}

void CombatMenu::drawEnemySlot(Pokemon pokemon)
{
	//creating stats zone
	sf::Vector2f statsPos = { 0,150 };
	sf::Vector2f statsSize = { 670, 170 };

	sf::RectangleShape s;
	s.setPosition(statsPos);
	s.setSize(statsSize);
	s.setFillColor({ 245,245,245,245 });
	contextWindow->getWindow()->draw(s);

	pokemon.getSprite().setScale(statPokemonScaleSize);
	pokemon.getSprite().setPosition(
		statsPos.x + statsSize.x * 0.025,
		statsPos.y + statsSize.y * 0.05
	);
	contextWindow->getWindow()->draw(pokemon.getSprite());

	sf::Text txt;
	txt.setFont(contextWindow->getFont());

	// drawing pokemon name 
	txt.setString(pokemon.getName());
	txt.setCharacterSize(30);
	txt.setOutlineColor(sf::Color::Black);
	txt.setOutlineThickness(5);
	txt.setPosition(
		pokemon.getSprite().getPosition().x + this->assetSize + 100,
		pokemon.getSprite().getPosition().y + 20
	);
	contextWindow->getWindow()->draw(txt);

	txt.setOutlineThickness(0);
	txt.setCharacterSize(20);
	txt.setColor(sf::Color::Black);

	//drawing pokemon level
	txt.setString("Level :    " + std::to_string(pokemon.getLevel().level));
	txt.setPosition(
		pokemon.getSprite().getPosition().x + this->assetSize + 100,
		pokemon.getSprite().getPosition().y + 90
	);
	contextWindow->getWindow()->draw(txt);

	//drawing pokemon hp
	txt.setString("HP :    " +
		std::to_string(pokemon.getHealthAndMax()[0]) +
		"  /  " +
		std::to_string(pokemon.getHealthAndMax()[1])
	);
	txt.setPosition(
		pokemon.getSprite().getPosition().x + this->assetSize + 300,
		pokemon.getSprite().getPosition().y + 90
	);
	contextWindow->getWindow()->draw(txt);

}

void CombatMenu::drawPokeImage(int i, sf::Vector2f slotPos)
{
	this->contextPlayer->getTeam()[i].getSprite().setScale(1.5f, 1.5f);
	this->contextPlayer->getTeam()[i].getSprite().setPosition(slotPos);
	this->contextWindow->getWindow()->draw(this->contextPlayer->getTeam()[i].getSprite());
}

void CombatMenu::drawPokeText(int i)
{
	sf::Text txt;
	txt.setFont(this->contextWindow->getFont());

	// drawing pokemon name 
	txt.setString(this->contextPlayer->getTeam()[i].getName());
	txt.setCharacterSize(20);
	txt.setOutlineColor(sf::Color::Black);
	txt.setOutlineThickness(5);
	txt.setPosition(
		this->contextPlayer->getTeam()[i].getSprite().getPosition().x + this->assetSize + this->assetSize / 2.f,
		this->contextPlayer->getTeam()[i].getSprite().getPosition().y + 20
	);
	this->contextWindow->getWindow()->draw(txt);

	txt.setOutlineThickness(0);
	txt.setCharacterSize(15);
	txt.setColor(this->basicTextColor);

	//drawing pokemon level
	txt.setString("Level : " + std::to_string(this->contextPlayer->getTeam()[i].getLevel().level));
	txt.setPosition(
		this->contextPlayer->getTeam()[i].getSprite().getPosition().x + this->assetSize + this->assetSize / 2.f,
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
		this->contextPlayer->getTeam()[i].getSprite().getPosition().x + this->assetSize + this->assetSize / 2.f,
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
		drawPokeText(i);
	}
}

void CombatMenu::drawShape()
{
	this->mainShape.setFillColor(this->basicColor);
	this->mainShape.setPosition(this->mainPos);
	this->mainShape.setSize(this->mainSize);
	this->contextWindow->getWindow()->draw(this->mainShape);
}

void CombatMenu::drawSelectedPokemon()
{
	
	this->contextPlayer->getTeam()[activeIndex].getSprite().setPosition(this->selfPokemonPos);
	this->contextPlayer->getTeam()[activeIndex].getSprite().setScale(this->inGamePokemonScaleSize);
	this->contextWindow->getWindow()->draw(this->contextPlayer->getTeam()[activeIndex].getSprite());
}

void CombatMenu::navigate()
{
	this->activeCombat = true;
}

void CombatMenu::drawMenu()
{
	this->contextWindow->getWindow()->draw(this->bgSprite);
	this->drawEnemy();
	this->drawShape();
	this->drawPokeSlot();
	this->drawSelectedPokemon();
}
