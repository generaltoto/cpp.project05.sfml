#include "MainWindow.h"

MainWindow::Menu::Menu(MainWindow* window) {
    this->contextWindow = window;
    setValues();
}

MainWindow::Menu::~Menu() {
}

void MainWindow::Menu::setValues() {
    currentSelected = 0;
    pressed = theselect = false;

    options = { "Play", "Inventory", "Options", "Quit" };
    texts.resize(4);
    textCoords = { {885,60},{915,286.5},{885,423},{900,555},{934.5,685.5} };
    sizes = { 30,42,36,36,36 };

    for (std::size_t i{}; i < texts.size(); ++i) {
        texts[i].setFont(*this->contextWindow->getFont());
        texts[i].setString(options[i]);
        texts[i].setCharacterSize(sizes[i]);
        texts[i].setOutlineColor(sf::Color::Black);
        texts[i].setPosition(textCoords[i]);
    }
    texts[1].setOutlineThickness(10);
    currentSelected = 1;
}

void MainWindow::Menu::NavigateMenu() {
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) && !pressed) {
        if (currentSelected < 4) {
            ++currentSelected;
            pressed = true;
            texts[currentSelected].setOutlineThickness(10);
            texts[currentSelected - 1].setOutlineThickness(0);
            pressed = false;
            theselect = false;
        }
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && !pressed) {
        if (currentSelected > 1) {
            --currentSelected;
            pressed = true;
            texts[currentSelected].setOutlineThickness(10);
            texts[currentSelected + 1].setOutlineThickness(0);
            pressed = false;
            theselect = false;
        }
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter) && !theselect) {
        theselect = true;
        if (currentSelected == 4) 
            this->contextWindow->getWindow()->close();
    }
}

void MainWindow::Menu::drawAll() {
    for (auto t : texts) {
        this->contextWindow->getWindow()->draw(t);
    }
}

void MainWindow::Menu::runMenu() {
    NavigateMenu();
    drawAll();
}