#include "include/view/MainWindow.h"

MainWindow::Menu::Menu(MainWindow* window) {
    this->contextWindow = window;
    setValues();
}

MainWindow::Menu::~Menu() {
}

void MainWindow::Menu::setValues() {
    this->currentSelected = 0;

    if (!this->bgAsset.loadFromFile(this->bgPath))
        throw("ERROR::INVENTORY_BACKGROUND_LOADING");
    else this->bg.setTexture(this->bgAsset);

    this->zoneCoords = { {710, 50}, {710, 308}, {710, 566}, {710, 824} };
    this->zoneSize = { 500, 208 };
    for (int i = 0; i < 4; i++)
    {
        sf::RectangleShape s;
        s.setPosition(this->zoneCoords[i]);
        s.setSize(this->zoneSize);
        s.setFillColor({ 127,127,127,200 });
        this->zones.push_back(s);
    }

    options = { "Play", "Inventory", "Options", "Quit" };
    texts.resize(4);
    sizes = { 36,36,36,36 };

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

void MainWindow::Menu::navigateMenu(ViewTypes* currentView, Sound* soundEffect) {
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
        texts[currentSelected].setOutlineThickness(0);
        if (currentSelected < 3) ++currentSelected;
        else currentSelected = 0;
        texts[currentSelected].setOutlineThickness(10);
        soundEffect->playASound(MENUEFFECT);
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
        texts[currentSelected].setOutlineThickness(0);
        if (currentSelected > 0) --currentSelected;
        else currentSelected = 3;
        texts[currentSelected].setOutlineThickness(10);
        soundEffect->playASound(MENUEFFECT);
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter)) {
        switch (currentSelected)
        {
        case 0:
            *currentView = PLAY;
            soundEffect->playASound(MENUEFFECT);
            break;
        case 1:
            *currentView = INVENTORY;
            soundEffect->playASound(MENUEFFECT);
            break;
        case 2:
           *currentView = SETTINGS;
           soundEffect->playASound(MENUEFFECT);
           break;
        case 3:
            this->contextWindow->getWindow()->close();
            break;
        default:
            break;
        }
    }
}

void MainWindow::Menu::draw() {
    this->contextWindow->getWindow()->draw(this->bg);
    for (int i = 0; i < 4; i++) this->contextWindow->getWindow()->draw(zones[i]);
    for (auto t : texts) this->contextWindow->getWindow()->draw(t);
}