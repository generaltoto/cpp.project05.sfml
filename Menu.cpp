#include "MainWindow.h"

MainWindow::Menu::Menu(MainWindow* window) {
    this->contextWindow = window;
    setValues();
}

MainWindow::Menu::~Menu() {
}

void MainWindow::Menu::setValues() {
    currentSelected = 0;
    pressed = false;

    options = { "Play", "Inventory", "Options", "Quit" };
    texts.resize(4);
    textCoords = { {885,60},{885,286.5},{885,423},{885,555} };
    sizes = { 36,36,36,36 };

    for (std::size_t i{}; i < texts.size(); ++i) {
        texts[i].setFont(*this->contextWindow->getFont());
        texts[i].setString(options[i]);
        texts[i].setCharacterSize(sizes[i]);
        texts[i].setOutlineColor(sf::Color::Black);
        texts[i].setPosition(textCoords[i]);
    }
    texts[currentSelected].setOutlineThickness(10);
}

void MainWindow::Menu::NavigateMenu(ViewTypes* currentView) {
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) && !pressed) {
        pressed = true;
        texts[currentSelected].setOutlineThickness(0);
        if (currentSelected < texts.size()) 
            ++currentSelected;
        else if (currentSelected == (texts.size() - 1))
            currentSelected = 0;
        texts[currentSelected].setOutlineThickness(10);
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && !pressed) {
        pressed = true;
        texts[currentSelected].setOutlineThickness(0);
        if (currentSelected > 1) --currentSelected;
        else if (currentSelected == 0) currentSelected = 3;
        texts[currentSelected].setOutlineThickness(10);
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter)) {
        switch (currentSelected)
        {
        case 0:
            *currentView = PLAY;
            break;
        case 3:
            this->contextWindow->getWindow()->close();
            break;
        default:
            break;
        }
    }
    pressed = false;
}

void MainWindow::Menu::drawAll() {
    for (auto t : texts) {
        this->contextWindow->getWindow()->draw(t);
    }
}

void MainWindow::Menu::runMenu(ViewTypes* currentView) {
    NavigateMenu(currentView);
    drawAll();
}