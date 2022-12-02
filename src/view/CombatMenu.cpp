#include "include/view/CombatMenu.h"

CombatMenu::CombatMenu(MainWindow* mainWindow, Player* player)
{
	this->contextWindow = mainWindow;
	this->contextPlayer = player;
	this->mainPos = { 1400,600 };
	this->mainSize = { 773, 450 };
	this->attackerPokemonPos = { 1100, 50 };
	this->selfPokemonPos = { 400,500 };
	this->inGamePokemonScaleSize = { 15.f, 15.f };
	this->statPokemonScaleSize = { 3.f, 3.f };
	this->activePokemonIdx = 0;
	this->selectedAttackIdx = 4;
	this->selectedPokemonIdx = 7;
	this->activeCombat = false;
	this->enemies = nullptr;

	this->bgText = new sf::Texture();
	if (this->bgText->loadFromFile(COMBAT_ASSET_PATH))
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
		texts[i].setCharacterSize(sizes[int(i)]);
		texts[i].setOutlineColor(sf::Color::Black);
		texts[i].setPosition(
			this->zoneCoords[i].x + this->zoneSize.x * 0.25,
			this->zoneCoords[i].y + this->zoneSize.y * 0.37
		);
	}
	texts[currentSelected].setOutlineThickness(10);
}

void CombatMenu::loadAttacker(Pokemon* p, bool* loaded)
{
	enemies = p;
	*loaded = true;
}

void CombatMenu::drawAttacker()
{
	if (this->enemies)
	{
		this->enemies->getSprite().setScale(this->inGamePokemonScaleSize);
		this->enemies->getSprite().setPosition(this->attackerPokemonPos);
		contextWindow->getWindow()->draw(this->enemies->getSprite());

		drawAttackerSlot(enemies);
	}
}

void CombatMenu::drawAttackerSlot(Pokemon* pokemon)
{
	//creating stats zone
	sf::Vector2f statsPos = { 0,50 };
	sf::Vector2f statsSize = { 650, 150 };

	sf::RectangleShape s;
	s.setPosition(statsPos);
	s.setSize(statsSize);
	s.setFillColor({ 245,245,245,245 });
	contextWindow->getWindow()->draw(s);

	pokemon->getSprite().setScale(statPokemonScaleSize);
	pokemon->getSprite().setPosition(
		statsPos.x + statsSize.x * 0.025,
		statsPos.y + statsSize.y * 0.05
	);
	contextWindow->getWindow()->draw(pokemon->getSprite());

	sf::Text txt;
	txt.setFont(contextWindow->getFont());

	// drawing pokemon name 
	txt.setString(pokemon->getName());
	txt.setCharacterSize(30);
	txt.setOutlineColor(sf::Color::Black);
	txt.setOutlineThickness(5);
	txt.setPosition(
		pokemon->getSprite().getPosition().x + this->assetSize + 100,
		pokemon->getSprite().getPosition().y + 20
	);
	contextWindow->getWindow()->draw(txt);

	txt.setOutlineThickness(0);
	txt.setCharacterSize(20);
	txt.setFillColor(sf::Color::Black);

	//drawing pokemon level
	txt.setString("Level :    " + std::to_string(pokemon->getLevel().level));
	txt.setPosition(
		pokemon->getSprite().getPosition().x + this->assetSize + 100,
		pokemon->getSprite().getPosition().y + 90
	);
	contextWindow->getWindow()->draw(txt);

	//drawing pokemon hp
	txt.setString("HP :    " +
		std::to_string(pokemon->getHealthAndMax()[0]) +
		"  /  " +
		std::to_string(pokemon->getHealthAndMax()[1])
	);
	txt.setPosition(
		pokemon->getSprite().getPosition().x + this->assetSize + 300,
		pokemon->getSprite().getPosition().y + 90
	);
	contextWindow->getWindow()->draw(txt);

}

void CombatMenu::drawDefenderSlot(Pokemon* pokemon)
{
	//creating stats zone
	sf::Vector2f statsPos = { 0,250 };
	sf::Vector2f statsSize = { 650, 150 };

	sf::RectangleShape s;
	s.setPosition(statsPos);
	s.setSize(statsSize);
	s.setFillColor({ 245,245,245,245 });
	contextWindow->getWindow()->draw(s);

	pokemon->getSprite().setScale(statPokemonScaleSize);
	pokemon->getSprite().setPosition(
		statsPos.x + statsSize.x * 0.025,
		statsPos.y + statsSize.y * 0.05
	);
	contextWindow->getWindow()->draw(pokemon->getSprite());

	sf::Text txt;
	txt.setFont(contextWindow->getFont());

	// drawing pokemon name 
	txt.setString(pokemon->getName());
	txt.setCharacterSize(30);
	txt.setOutlineColor(sf::Color::Black);
	txt.setOutlineThickness(5);
	txt.setPosition(
		pokemon->getSprite().getPosition().x + this->assetSize + 100,
		pokemon->getSprite().getPosition().y + 20
	);
	contextWindow->getWindow()->draw(txt);

	txt.setOutlineThickness(0);
	txt.setCharacterSize(20);
	txt.setFillColor(sf::Color::Black);

	//drawing pokemon level
	txt.setString("Level :    " + std::to_string(pokemon->getLevel().level));
	txt.setPosition(
		pokemon->getSprite().getPosition().x + this->assetSize + 100,
		pokemon->getSprite().getPosition().y + 90
	);
	contextWindow->getWindow()->draw(txt);

	//drawing pokemon hp
	txt.setString("HP :    " +
		std::to_string(pokemon->getHealthAndMax()[0]) +
		"  /  " +
		std::to_string(pokemon->getHealthAndMax()[1])
	);
	txt.setPosition(
		pokemon->getSprite().getPosition().x + this->assetSize + 300,
		pokemon->getSprite().getPosition().y + 90
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
	txt.setFillColor(this->basicTextColor);

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

void CombatMenu::drawAttacksSlots(Pokemon* pokemon)
{
	for (int i = 0; i < this->contextPlayer->getTeam()[activePokemonIdx].getCapacities().size() ; i++)
	{
		if (this->selectedAttackIdx == i)
			this->attackSlot.setFillColor(this->activeColor);
		else this->attackSlot.setFillColor(this->basicColor);

		sf::Vector2f slotPos;
		slotPos = {
			float(this->mainPos.x + 20),
			float(this->mainPos.y + (i* (this->mainSize.y / 5.2)) + 20)
		};
		sf::Vector2f slotSize;
		slotSize = {
			float(this->mainSize.x * 0.6),
			float(this->mainSize.y / 5.5)
		};
		this->attackSlot.setPosition(slotPos);
		this->attackSlot.setSize(slotSize);
		this->contextWindow->getWindow()->draw(this->attackSlot);
		drawAttacksText(this->contextPlayer->getTeam()[activePokemonIdx].getCapacities()[i], i);
	}
}

void CombatMenu::drawAttacksText(Capacity capa, int i) {
	sf::Text txt;
	txt.setFont(this->contextWindow->getFont());

	// drawing capacity name 
	txt.setString(capa.name);
	txt.setCharacterSize(20);
	txt.setOutlineColor(sf::Color::Black);
	txt.setOutlineThickness(5);
	txt.setPosition(
		this->attackSlot.getPosition().x + (this->attackSlot.getSize().x/6),
		this->attackSlot.getPosition().y + (this->attackSlot.getSize().y / 2.5)
	);
	this->contextWindow->getWindow()->draw(txt);

	txt.setOutlineThickness(0);
	txt.setCharacterSize(15);
	txt.setFillColor(this->basicTextColor);

	//drawing capacity pp
	txt.setString("PP : " +
		std::to_string(capa.current) +
		"/" +
		std::to_string(capa.pp)
	);
	txt.setPosition(
		this->attackSlot.getPosition().x + (this->attackSlot.getSize().x / 1.5),
		this->attackSlot.getPosition().y + (this->attackSlot.getSize().y / 2.5)
	);
	this->contextWindow->getWindow()->draw(txt);
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
	this->contextPlayer->getTeam()[activePokemonIdx].getSprite().setPosition(this->selfPokemonPos);
	this->contextPlayer->getTeam()[activePokemonIdx].getSprite().setScale(this->inGamePokemonScaleSize);
	this->contextWindow->getWindow()->draw(this->contextPlayer->getTeam()[activePokemonIdx].getSprite());

	drawDefenderSlot(&this->contextPlayer->getTeam()[activePokemonIdx]);
}

void CombatMenu::drawSelectAction() {
	for (int i = 0; i < 3; i++) this->contextWindow->getWindow()->draw(zones[i]);
	for (auto t : texts) this->contextWindow->getWindow()->draw(t);
}

void CombatMenu::navigate(Sound* soundEffect, ViewTypes* currentView, bool* loadedEnemies) {
	this->activeCombat = true;
	if (sideNavigate == 0) 
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) 
		{
			texts[currentSelected].setOutlineThickness(0);
			if (currentSelected < 2) ++currentSelected;
			else currentSelected = 0;
			texts[currentSelected].setOutlineThickness(10);
			soundEffect->playASound(MENUEFFECT);
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) 
		{
			texts[currentSelected].setOutlineThickness(0);
			if (currentSelected > 0) --currentSelected;
			else currentSelected = 2;
			texts[currentSelected].setOutlineThickness(10);
			soundEffect->playASound(MENUEFFECT);
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) 
		{
			soundEffect->playASound(MENUEFFECT);
			if (currentSelected == 0 && this->currentView == ATTACKS) 
			{
				this->selectedAttackIdx = 0;
				this->sideNavigate = 1;
			}
			else if (currentSelected == 1 && this->currentView == TEAM) 
			{
				this->selectedPokemonIdx = 0;
				this->sideNavigate = 2;
			}
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) 
		{
			*currentView = MENU;
			soundEffect->playASound(MENUEFFECT);
			this->activeCombat = isCombatActive(soundEffect);
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter)) {
			auto const flee = (this->contextPlayer->getTeam()[activePokemonIdx].currentStats[VIT] * 32) / (
				enemies[0].currentStats[VIT] %255) + 30;
			switch (currentSelected)
			{
			case 0:
				this->currentView = ATTACKS;
				break;
			case 1:
				this->currentView = TEAM;
				break;
			case 2:
				if (flee >= 255 || rand() % 255 <= flee) {
					this->activeCombat = false;
					*loadedEnemies = false;
					this->enemies = nullptr;
					*currentView = PLAY;
					return;
				}
				this->enemies[0].pokemonIAChoseAttack(enemies, &this->contextPlayer->getTeam()[activePokemonIdx]);
				soundEffect->playASound(ATKEFFECT);
				sleep_for(seconds(1));
				isCombatActive(soundEffect);
				break;
			default:
				break;
			}
		}
		if (enemies == nullptr) {
			this->activeCombat = false;
			*loadedEnemies = false;
			*currentView = PLAY;
			return;
		}
	}
	else if (sideNavigate == 1) {
		navigateAttacks(soundEffect);
	}
	else {
		navigatePokemon(soundEffect);
	}
}

void CombatMenu::navigateAttacks(Sound* soundEffect) {
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
		if (selectedAttackIdx < this->contextPlayer->getTeam()[activePokemonIdx].getCapacities().size()-1) ++selectedAttackIdx;
		else selectedAttackIdx = 0;
		soundEffect->playASound(MENUEFFECT);
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
		if (selectedAttackIdx > 0) --selectedAttackIdx;
		else selectedAttackIdx = this->contextPlayer->getTeam()[activePokemonIdx].getCapacities().size()-1;
		soundEffect->playASound(MENUEFFECT);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
		soundEffect->playASound(MENUEFFECT);
		this->selectedAttackIdx = 4;
		this->sideNavigate = 0;
		return;
	}
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Enter)) {
		this->sideNavigate = 0;
		soundEffect->playASound(MENUEFFECT);
		sleep_for(seconds(1));
		attackTurn(soundEffect);
		this->selectedAttackIdx = 4;
	}
}

void CombatMenu::navigatePokemon(Sound* soundEffect) {
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
		if (selectedPokemonIdx < this->contextPlayer->getNbPokemon()-1) ++selectedPokemonIdx;
		else selectedPokemonIdx = 0;
		soundEffect->playASound(MENUEFFECT);
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
		if (selectedPokemonIdx > 0) --selectedPokemonIdx;
		else selectedPokemonIdx = this->contextPlayer->getNbPokemon() - 1;
		soundEffect->playASound(MENUEFFECT);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
		soundEffect->playASound(MENUEFFECT);
		this->selectedPokemonIdx = 7;
		this->sideNavigate = 0;
		return;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter)) {
		soundEffect->playASound(MENUEFFECT);
		sleep_for(seconds(1));
		if (selectedPokemonIdx != activePokemonIdx) {
			activePokemonIdx = selectedPokemonIdx;
			this->enemies[0].pokemonIAChoseAttack(enemies, &this->contextPlayer->getTeam()[activePokemonIdx]);
			soundEffect->playASound(ATKEFFECT);
			isCombatActive(soundEffect);
		}
		else return;
	}
}

void CombatMenu::attackTurn(Sound* soundEffect) {
	this->contextPlayer->getTeam()[activePokemonIdx].pokemonAttack(
		&this->contextPlayer->getTeam()[activePokemonIdx], enemies, this->selectedAttackIdx - 1
	);
	soundEffect->playASound(ATKEFFECT);
	sleep_for(seconds(2));
	this->enemies[0].pokemonIAChoseAttack(enemies, &this->contextPlayer->getTeam()[activePokemonIdx]);
	soundEffect->playASound(ATKEFFECT);
	sleep_for(seconds(1));
	isCombatActive(soundEffect);
}

bool CombatMenu::isCombatActive(Sound* soundEffect) {
	if (this->enemies == nullptr) return false;

	if (this->enemies->currentHealth <= 0 && this->contextPlayer->getTeam()[activePokemonIdx].currentHealth > 0) {
		this->enemies = nullptr;
		this->contextPlayer->getTeam()[activePokemonIdx].levelUp(150);
		for (int i = 0; i < this->contextPlayer->getNbPokemon(); i++) {
			this->contextPlayer->getTeam()[i].levelUp(150);
		}
		soundEffect->playASound(WINCOMBAT);
		sleep_for(seconds(2));
		return false;
	}

	if (this->contextPlayer->getTeam()[activePokemonIdx].currentHealth <= 0)
	{
		if (this->contextPlayer->getNbPokemon() - 1 == activePokemonIdx) {
			soundEffect->playASound(WINCOMBAT);
			sleep_for(seconds(3));
			this->contextWindow->getWindow()->close();
			return false;
		}
		for (int i = activePokemonIdx; i < this->contextPlayer->getNbPokemon(); i++) {
			this->contextPlayer->getTeam()[i] = this->contextPlayer->getTeam()[i + 1];
		}
		if (activePokemonIdx < this->contextPlayer->getNbPokemon()) activePokemonIdx++;
		return true;
	}

	activePokemonIdx = 0;
	return true;
}

void CombatMenu::drawMenu() {
	this->contextWindow->getWindow()->draw(this->bgSprite);
	this->drawAttacker();
	this->drawShape();
	this->drawSelectedPokemon();
	this->drawSelectAction();
	switch (this->currentView)
	{
	case ATTACKS:
		this->currentView = ATTACKS;
		this->drawAttacksSlots(&this->contextPlayer->getTeam()[activePokemonIdx]);
		break;
	case TEAM:
		this->currentView = TEAM;
		this->drawTeam();
		break;
	default:
		break;
	}
}
