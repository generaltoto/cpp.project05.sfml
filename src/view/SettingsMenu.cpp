#include "include/view/MainWindow.h"

MainWindow::SettingsMenu::SettingsMenu(MainWindow* window, Sound* soundEffect, Music* music) {
	this->contextWindow = window;
	setValues(soundEffect, music);
}

MainWindow::SettingsMenu::~SettingsMenu() { }

void MainWindow::SettingsMenu::setValues(Sound* soundEffect, Music* music) {
	this->currentSelected = 0;

	if (!this->bgAsset.loadFromFile(this->bgPath))
		throw("ERROR::INVENTORY_BACKGROUND_LOADING");
	else this->bg.setTexture(this->bgAsset);

   options = { "Music Volume", "Sounds Effects Volume", "Return"};
   texts.resize(3);
   textCoords = { {400,250},{400,450},{400,650} };
   sizes = { 36,36,36 };

   for (std::size_t i{}; i < texts.size(); ++i) {
      texts[i].setFont(this->contextWindow->getFont());
      texts[i].setString(options[i]);
      texts[i].setCharacterSize(sizes[i]);
      texts[i].setOutlineColor(sf::Color::Black);
      texts[i].setPosition(textCoords[i]);
   }
   texts[currentSelected].setOutlineThickness(10);

   volText.resize(2);
   volTextCoords = { {900,250},{1050,450} };
   volSizes = { 36,36 };

   for (std::size_t i{}; i < volText.size(); ++i) {
      volText[i].setFont(this->contextWindow->getFont());
      volText[i].setCharacterSize(sizes[i]);
      volText[i].setOutlineColor(sf::Color::Black);
      volText[i].setPosition(volTextCoords[i]);
      volText[i].setOutlineThickness(10);
   }
   volText[1].setString(std::to_string(int(soundEffect->getVolume())));
   volText[0].setString(std::to_string(int(music->getVolume())));
}

void MainWindow::SettingsMenu::navigate(ViewTypes* currentView, Sound* soundEffect, Music* music) {
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
         music->setVolume(music->getVolume()-5.f);
         soundEffect->playASound(MENUEFFECT);
         updateDrawVol(soundEffect, music);
         break;
      case 1:
         soundEffect->setVolume(soundEffect->getVolume() - 5.f);
         soundEffect->playASound(MENUEFFECT);
         updateDrawVol(soundEffect, music);
         break;
      default:
         break;
      }
   }

   if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
      switch (currentSelected)
      {
      case 0:
         music->setVolume(music->getVolume() + 5.f);
         soundEffect->playASound(MENUEFFECT);
         updateDrawVol(soundEffect, music);
         break;
      case 1:
         soundEffect->setVolume(soundEffect->getVolume() + 5.f);
         soundEffect->playASound(MENUEFFECT);
         updateDrawVol(soundEffect, music);
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

   if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
      *currentView = MENU;
      soundEffect->playASound(MENUEFFECT);
   }
}

void MainWindow::SettingsMenu::draw() {
   this->contextWindow->getWindow()->draw(this->bg);
   for (auto t : texts) this->contextWindow->getWindow()->draw(t);
   for (auto t : volText) this->contextWindow->getWindow()->draw(t);
}

void MainWindow::SettingsMenu::updateDrawVol(Sound* soundEffect, Music* music) {
   volText[1].setString(std::to_string(int(soundEffect->getVolume())));
   volText[0].setString(std::to_string(int(music->getVolume())));
}