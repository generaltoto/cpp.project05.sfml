#include "include/view/MainWindow.h"

void MainWindow::InventoryMenu::setValues()
{
	this->currentSelected = 0;
	this->healingPokemon = false;

	if (!this->asset.loadFromFile(this->bgPath))
		throw("ERROR::INVENTORY_BACKGROUND_LOADING");
	else this->bg.setTexture(this->asset);

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
}

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
	for (int i = 0; i < 6; i++) this->contextWindow->getWindow()->draw(pZones[i]);
	for (int i = 0; i < 3; i++) this->contextWindow->getWindow()->draw(iZones[i]);
	const int assetSize = 24;
	for (int i = 0; i < this->contextPlayer->getBag().size(); i++)
	{
		sf::IntRect spSize = { assetSize * i, 0, assetSize, assetSize };
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
			txt.setFont(*this->contextWindow->getFont());
			txt.setString("x" + convertToString(this->contextPlayer->getBag()[i]));
			txt.setCharacterSize(55);
			txt.setOutlineColor(sf::Color::Black);
			txt.setPosition(
				sp.getPosition().x + assetSize + 100, sp.getPosition().y + 20
			);
			this->contextWindow->getWindow()->draw(txt);
		}
		else throw("ERROR::LOADING_ITEMS_IMG");
	}
}
