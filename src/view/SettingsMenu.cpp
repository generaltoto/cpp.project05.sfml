#include "include/view/MainWindow.h"

MainWindow::SettingsMenu::SettingsMenu(MainWindow* window) {
	this->contextWindow = window;
	setValues();
}

MainWindow::SettingsMenu::~SettingsMenu() { }

void MainWindow::SettingsMenu::setValues() {
	this->currentSelected = 0;

	if (!this->bgAsset.loadFromFile(this->bgPath))
		throw("ERROR::INVENTORY_BACKGROUND_LOADING");
	else this->bg.setTexture(this->bgAsset);

   this->zoneCoords = { {600, 50}, {600, 308}, {600, 566}, {600, 824} };
   this->zoneSize = { 500, 208 };

   options = { "Music Volume", "Sounds Effects Volume", "Return"};
   texts.resize(3);
   textCoords = { {885,60},{885,286.5},{885,423} };
   sizes = { 36,36,36 };

   for (std::size_t i{}; i < texts.size(); ++i) {
      texts[i].setFont(*this->contextWindow->getFont());
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

void MainWindow::SettingsMenu::navigateSettings(ViewTypes* currentView, Sound* soundEffect, Music* music) {
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

   if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
      switch (currentSelected)
      {
      case 0:
         music->setVolume(music->getVolume()-5);
         soundEffect->playASound(MENUEFFECT);
         break;
      case 1:
         soundEffect->setVolume(soundEffect->getVolume() - 5);
         soundEffect->playASound(MENUEFFECT);
         break;
      default:
         break;
      }
   }

   if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
      switch (currentSelected)
      {
      case 0:
         music->setVolume(music->getVolume() + 5);
         soundEffect->playASound(MENUEFFECT);
         break;
      case 1:
         soundEffect->setVolume(soundEffect->getVolume() + 5);
         soundEffect->playASound(MENUEFFECT);
         break;
      default:
         break;
      }
   }

   if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter)) {
      switch (currentSelected)
      {
      case 2:
         *currentView = MENU;
         soundEffect->playASound(MENUEFFECT);
         break;
      default:
         break;
      }
   }
}

void MainWindow::SettingsMenu::draw() {
   this->contextWindow->getWindow()->draw(this->bg);
   for (auto t : texts) this->contextWindow->getWindow()->draw(t);
}

void MainWindow::SettingsMenu::updateDrawVol(Sound* soundEffect, Music* music) {

}