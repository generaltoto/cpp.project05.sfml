#include "include/view/MainWindow.h"

void MainWindow::InventoryMenu::setValues()
{
	this->currentSelected = 1;
	this->healingPokemon = false;

	if (!this->bgAsset.loadFromFile(this->bgPath))
		throw("ERROR::INVENTORY_BACKGROUND_LOADING");
	else this->bg.setTexture(this->bgAsset);

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

void MainWindow::InventoryMenu::navigate()
{
	if (healingPokemon) navigatePokemons();
	else navigateItems();
}

void MainWindow::InventoryMenu::navigateItems()
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
	{
		iZones[currentSelected].setOutlineThickness(0);
		if (currentSelected < 2) ++currentSelected;
		else currentSelected = 1;
		iZones[currentSelected].setOutlineThickness(10);
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
	{
		iZones[currentSelected].setOutlineThickness(0);
		if (currentSelected > 1) --currentSelected;
		else currentSelected = 2;
		iZones[currentSelected].setOutlineThickness(10);
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter))
	{
		if (currentSelected == 1) healingType = HEAL;
		else if (currentSelected == 0) healingType = RESET;
		this->healingPokemon = true;
		this->currentSelected = 0;
		this->pZones[currentSelected].setOutlineThickness(10);
	}
}

void MainWindow::InventoryMenu::navigatePokemons()
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
		pZones[currentSelected].setOutlineThickness(0);
		if (currentSelected < 5) ++currentSelected;
		else currentSelected = 0;
		pZones[currentSelected].setOutlineThickness(10);
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
		pZones[currentSelected].setOutlineThickness(0);
		if (currentSelected > 0) --currentSelected;
		else currentSelected = 5;
		pZones[currentSelected].setOutlineThickness(10);
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
	{
		pZones[currentSelected].setOutlineThickness(0);
		this->healingPokemon = false;
		this->currentSelected = 1;
		iZones[currentSelected].setOutlineThickness(0);
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter))
	{
	}
}

/// Converts an int into string
extern std::string convertToString(int number)
{
	std::stringstream convert;
	convert << number;
	auto str = convert.str();
	return convert.str().c_str();
}

void MainWindow::InventoryMenu::draw()
{
	this->contextWindow->getWindow()->draw(this->bg);
	for (auto& pZonesShape : pZones) this->contextWindow->getWindow()->draw(pZonesShape);
	const int pokemonAssetSz = 40;
	for (int i = 0; i < this->contextPlayer->getTeam().size(); i++)
	{
		sf::Sprite sp = this->contextPlayer->getTeam()[i].getSprite();
		sp.setScale(2.f, 2.f);
		sp.setPosition(
			this->pZoneCoords[i].x + this->pZoneSize.x * 0.25,
			this->pZoneCoords[i].y + this->pZoneSize.y * 0.20
		);
		this->contextWindow->getWindow()->draw(sp);

		sf::Text txt;
		txt.setFont(this->contextWindow->getFont());
		txt.setString(this->contextPlayer->getTeam()[i].getName());
		txt.setCharacterSize(55);
		txt.setOutlineColor(sf::Color::Black);
		txt.setPosition(
			sp.getPosition().x + pokemonAssetSz + 100,
			sp.getPosition().y + 20
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
		if (t.loadFromFile("assets/items.png"))
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
			txt.setString("x" + convertToString(this->contextPlayer->getBag()[i]));
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
