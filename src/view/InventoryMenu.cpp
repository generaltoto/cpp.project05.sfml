#include "include/view/MainWindow.h"

void MainWindow::InventoryMenu::setValues()
{
	this->currentSelected = 1;
	this->healingPokemon = false;

	if (!this->bgAsset.loadFromFile(INVENTORY_BG_ASSET_PATH))
		throw("ERROR::INVENTORY_BACKGROUND_LOADING");
	this->bg.setTexture(this->bgAsset);

	this->pZoneCoords = { {60, 100}, {60, 250}, {60, 400}, {60, 550}, {60, 700}, {60, 850} };
	this->pZoneSize = { 800, 125 };
	for (int i = 0; i < 6; i++)
	{
		sf::RectangleShape s;
		s.setPosition(this->pZoneCoords[i]);
		s.setSize(this->pZoneSize);
		s.setFillColor({ 127,127,127,127 });
		this->pZones.push_back(s);
	}

	this->iZoneCoords = { {1100, 100}, {1000, 320}, {1000, 595} };
	this->iPokeballZoneSize = { 640, 150 };
	this->iSprayZoneSize = { 840, 250 };
	for (int i = 0; i < 3; i++)
	{
		sf::RectangleShape s;
		s.setPosition(this->iZoneCoords[i]);
		if (i > 0) s.setSize(this->iSprayZoneSize);
		else s.setSize(this->iPokeballZoneSize);
		s.setFillColor({ 127,127,127,127 });
		this->iZones.push_back(s);
	}
	iZones[currentSelected].setOutlineThickness(10);
}

MainWindow::InventoryMenu::InventoryMenu(MainWindow* w, Player* p)
{
	this->contextWindow = w;
	this->contextPlayer = p;
	setValues();
}

MainWindow::InventoryMenu::~InventoryMenu()
{
	delete this->contextWindow, this->contextPlayer;
}

void MainWindow::InventoryMenu::navigate(Sound* soundEffect, Player* p, ViewTypes* currentView)
{
	if (healingPokemon) navigatePokemons(soundEffect, p);
	else navigateItems(soundEffect, currentView);
}

void MainWindow::InventoryMenu::navigateItems(Sound* soundEffect, ViewTypes* currentView)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
		iZones[currentSelected].setOutlineThickness(0);
		if (currentSelected < 2) ++currentSelected;
		else currentSelected = 1;
		iZones[currentSelected].setOutlineThickness(10);
		soundEffect->playASound(MENUEFFECT);
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
		iZones[currentSelected].setOutlineThickness(0);
		if (currentSelected > 1) --currentSelected;
		else currentSelected = 2;
		iZones[currentSelected].setOutlineThickness(10);
		soundEffect->playASound(MENUEFFECT);
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter)) {
		if (currentSelected == 1) healingType = HEAL;
		else if (currentSelected == 0) healingType = RESET;
		this->healingPokemon = true;
		this->currentSelected = 0;
		this->pZones[currentSelected].setOutlineThickness(10);
		soundEffect->playASound(MENUEFFECT);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
		*currentView = MENU;
		soundEffect->playASound(MENUEFFECT);
	}
}

void MainWindow::InventoryMenu::navigatePokemons(Sound* soundEffect, Player* p)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
		pZones[currentSelected].setOutlineThickness(0);
		if (currentSelected < 5) ++currentSelected;
		else currentSelected = 0;
		pZones[currentSelected].setOutlineThickness(10);
		soundEffect->playASound(MENUEFFECT);
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
		pZones[currentSelected].setOutlineThickness(0);
		if (currentSelected > 0) --currentSelected;
		else currentSelected = 5;
		pZones[currentSelected].setOutlineThickness(10);
		soundEffect->playASound(MENUEFFECT);
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
		healingPokemon == false;
		pZones[currentSelected].setOutlineThickness(0);
		this->healingPokemon = false;
		this->currentSelected = 1;
		iZones[currentSelected].setOutlineThickness(0);
		soundEffect->playASound(MENUEFFECT);
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter)) {
		p->healPokemon(healingType, p->getTeam()[currentSelected]);
		soundEffect->playASound(HEALEFFECT);
	}
}

void MainWindow::InventoryMenu::draw()
{
	this->contextWindow->getWindow()->draw(this->bg);
	for (auto& pZonesShape : pZones) this->contextWindow->getWindow()->draw(pZonesShape);
	const int pokemonAssetSz = 40;
	for (int i = 0; i < this->contextPlayer->getNbPokemon(); i++)
	{
		// drawing pokemon image
		this->contextPlayer->getTeam()[i].getSprite().setScale(3.f, 3.f);
		this->contextPlayer->getTeam()[i].getSprite().setPosition(
			this->pZoneCoords[i].x + this->pZoneSize.x * 0.05,
			this->pZoneCoords[i].y + this->pZoneSize.y * 0.1
		);
		this->contextWindow->getWindow()->draw(this->contextPlayer->getTeam()[i].getSprite());

		sf::Text txt;
		txt.setFont(this->contextWindow->getFont());

		// drawing pokemon name 
		txt.setString(this->contextPlayer->getTeam()[i].getName());
		txt.setCharacterSize(30);
		txt.setOutlineColor(sf::Color::Black);
		txt.setOutlineThickness(5);
		txt.setPosition(
			this->contextPlayer->getTeam()[i].getSprite().getPosition().x + pokemonAssetSz + 100,
			this->contextPlayer->getTeam()[i].getSprite().getPosition().y + 20
		);
		this->contextWindow->getWindow()->draw(txt);

		txt.setOutlineThickness(0);
		txt.setCharacterSize(20);

		//drawing pokemon level
		txt.setString("Level :    " + std::to_string(this->contextPlayer->getTeam()[i].getLevel().level));
		txt.setPosition(
			this->contextPlayer->getTeam()[i].getSprite().getPosition().x + pokemonAssetSz + 100,
			this->contextPlayer->getTeam()[i].getSprite().getPosition().y + 75
		);
		this->contextWindow->getWindow()->draw(txt);

		//drawing pokemon hp
		txt.setString("HP :    " + 
			std::to_string(this->contextPlayer->getTeam()[i].getHealthAndMax()[0]) + 
			"  /  " + 
			std::to_string(this->contextPlayer->getTeam()[i].getHealthAndMax()[1])
		);
		txt.setPosition(
			this->contextPlayer->getTeam()[i].getSprite().getPosition().x + pokemonAssetSz + 300,
			this->contextPlayer->getTeam()[i].getSprite().getPosition().y + 75
		);
		this->contextWindow->getWindow()->draw(txt);
	}

	for (auto& iZonesShape : iZones) this->contextWindow->getWindow()->draw(iZonesShape);
	const int itemAssetSz = 24;
	for (int i = 0; i < this->contextPlayer->getBag().size(); i++)
	{
		sf::IntRect spSize = { itemAssetSz * i, 0, itemAssetSz, itemAssetSz };
		sf::Texture t;
		sf::Sprite sp;
		if (t.loadFromFile(ITEMS_ASSET_PATH))
		{
			sp.setTexture(t);
			sp.setTextureRect(spSize);
			sp.scale(4.f, 4.f);
			if (i == 0)
				sp.setPosition(
					this->iZoneCoords[i].x + this->iPokeballZoneSize.x * 0.25, 
					this->iZoneCoords[i].y + this->iPokeballZoneSize.y * 0.20
				);
			else 
				sp.setPosition(
					this->iZoneCoords[i].x + this->iSprayZoneSize.x * 0.25,
					this->iZoneCoords[i].y + this->iSprayZoneSize.y * 0.20
				);
			this->contextWindow->getWindow()->draw(sp);

			sf::Text txt;
			txt.setFont(this->contextWindow->getFont());
			txt.setString("x" + std::to_string(this->contextPlayer->getBag()[i]));
			txt.setCharacterSize(55);
			txt.setOutlineColor(sf::Color::Black);
			txt.setPosition(
				sp.getPosition().x + itemAssetSz + 100, sp.getPosition().y + 20
			);
			this->contextWindow->getWindow()->draw(txt);
		}
		else throw("ERROR::LOADING_ITEMS_IMG");
	}
}
