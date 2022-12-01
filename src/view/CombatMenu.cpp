#include "include/view/CombatMenu.h"

CombatMenu::CombatMenu(MainWindow* mainWindow, Player* player)
{
	this->contextWindow = mainWindow;
	this->contextPlayer = player;
	this->mainPos = { 1400,600 };
	this->mainSize = { 773, 450 };
	this->enemyPokemonPos = { 1100, 50 };
	this->selfPokemonPos = { 400,500 };
	this->inGamePokemonScaleSize = { 15.f, 15.f };
	this->statPokemonScaleSize = { 3.f, 3.f };
	this->selectedPokemonIdx = 0;
	this->selectedAttackIdx = 0;
	this->activeCombat = false;
	this->enemies = {};

	this->bgText = new sf::Texture();
	if (this->bgText->loadFromFile("assets/combat.png"))
	{
		this->bgSprite.setTexture(*this->bgText);
	}
	else throw("ERROR::LOADING_COMBAT_BACKGROUND");


	this->currentSelected = 0;
	this->currentView = ATTACKS;

	this->zoneCoords = { {1100,620 }, {1100, 770}, {1100, 920} };
	this->zoneSize = { 300, 130 };
	for (int i = 0; i < 3; i++)
	{
		sf::RectangleShape s;
		s.setPosition(this->zoneCoords[i]);
		s.setSize(this->zoneSize);
		s.setFillColor({ 127,127,127,200 });
		this->zones.push_back(s);
	}

	options = { "Attack", "Pokemons", "Flee" };
	texts.resize(3);
	sizes = { 27,27,27 };

	for (std::size_t i{}; i < texts.size(); ++i) {
		texts[i].setFont(this->contextWindow->getFont());
		texts[i].setString(options[i]);
		texts[i].setCharacterSize(sizes[i]);
		texts[i].setOutlineColor(sf::Color::Black);
		texts[i].setPosition(
			this->zoneCoords[i].x + this->zoneSize.x * 0.25,
			this->zoneCoords[i].y + this->zoneSize.y * 0.37
		);
	}
	texts[currentSelected].setOutlineThickness(10);
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
			it.getSprite().setScale(this->inGamePokemonScaleSize);
			it.getSprite().setPosition(this->enemyPokemonPos);
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

void CombatMenu::drawAttacks(Pokemon* pokemon)
{
	for (int i = 0; i < this->contextPlayer->getTeam()[selectedPokemonIdx].getCapacities().size() ; i++)
	{
		if (this->selectedAttackIdx == i)
			this->attackSlot.setFillColor(this->activeColor);
		else this->attackSlot.setFillColor(this->basicColor);

		sf::Vector2f slotPos;
		slotPos = {
			float(this->mainPos.x + 20),
			float(this->mainPos.y + (i*122) + 10)
		};
		sf::Vector2f slotSize;
		slotSize = {
			float(this->mainSize.x * 0.95),
			float(this->mainSize.y / 4.5)
		};
		this->attackSlot.setPosition(slotPos);
		this->attackSlot.setSize(slotSize);
		this->contextWindow->getWindow()->draw(this->attackSlot);
	}
}

void CombatMenu::drawTeam()
{
	const int assetSize = 40;
	for (int i = 0; i < this->contextPlayer->getNbPokemon(); i++)
	{
		if (this->selectedPokemonIdx == i)
			this->pokemonSlot.setFillColor(this->activeColor);
		else this->pokemonSlot.setFillColor(this->basicColor);

		sf::Vector2f slotPos;
		if (i - 2 < 1)
		{
			slotPos = {
				float(this->mainPos.x + (this->mainSize.x * 0.05) - 10),
				float(this->mainPos.y + this->mainSize.y * 0.05 + ((this->mainSize.y / 3) * i))
			};
		}
		else
		{
			slotPos = {
				float(this->mainPos.x + this->mainSize.x * 0.05 + (this->mainSize.y / 2) + 5),
				float(this->mainPos.y + this->mainSize.y * 0.05 + ((this->mainSize.y / 3) * (i - 3)))
			};
		}
		this->pokemonSlot.setPosition(slotPos);
		this->pokemonSlot.setSize(
			{ 225, 120 }
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
	this->contextPlayer->getTeam()[selectedPokemonIdx].getSprite().setPosition(this->selfPokemonPos);
	this->contextPlayer->getTeam()[selectedPokemonIdx].getSprite().setScale(this->inGamePokemonScaleSize);
	this->contextWindow->getWindow()->draw(this->contextPlayer->getTeam()[selectedPokemonIdx].getSprite());
}

void CombatMenu::drawSelectAction() {
	for (int i = 0; i < 3; i++) this->contextWindow->getWindow()->draw(zones[i]);
	for (auto t : texts) this->contextWindow->getWindow()->draw(t);
}

void CombatMenu::navigate(Sound* soundEffect, ViewTypes* currentView) {
	this->activeCombat = true;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
		texts[currentSelected].setOutlineThickness(0);
		if (currentSelected < 2) ++currentSelected;
		else currentSelected = 0;
		texts[currentSelected].setOutlineThickness(10);
		soundEffect->playASound(MENUEFFECT);
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
		texts[currentSelected].setOutlineThickness(0);
		if (currentSelected > 0) --currentSelected;
		else currentSelected = 2;
		texts[currentSelected].setOutlineThickness(10);
		soundEffect->playASound(MENUEFFECT);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
		*currentView = MENU;
		soundEffect->playASound(MENUEFFECT);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter)) {
		switch (currentSelected)
		{
		case 0:
			this->currentView = ATTACKS;
			break;
		case 1:
			this->currentView = TEAM;
			break;
		case 2:
			// flee feature
			break;
		default:
			break;
		}
	}
}

void CombatMenu::drawMenu()
{
	this->contextWindow->getWindow()->draw(this->bgSprite);
	this->drawEnemy();
	this->drawShape();
	this->drawSelectedPokemon();
	this->drawSelectAction();
	switch (this->currentView)
	{
	case ATTACKS:
		this->currentView = ATTACKS;
		this->drawAttacks(&this->contextPlayer->getTeam()[selectedPokemonIdx]);
		break;
	case TEAM:
		this->currentView = TEAM;
		this->drawTeam();
		break;
	default:
		break;
	}
}
