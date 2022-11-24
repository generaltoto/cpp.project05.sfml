#include "Game.h"

MainWindow* Game::mainWindow = nullptr;

void Game::startGame() {
    mainWindow = new MainWindow();
    mainWindow->initWindow();
}

void Game::runGame() {
    ViewType currentView;
    ViewType lastView;
    
    sf::Event e{};
    while (mainWindow->getWindow()->isOpen())
    {
        while (mainWindow->getWindow()->pollEvent(e))
        {
            switch (e.type) {
            case sf::Event::Closed:
                mainWindow->getWindow()->close();
                break;
            case sf::Event::KeyPressed:
                if (e.key.code == sf::Keyboard::Enter)
                    if (currentView != MENU) currentView = MENU;
                    else currentView = lastView;
                if (e.key.code == sf::Keyboard::Up)

                break;
            default:
                break;
            }
        }

        mainWindow->getWindow()->clear(sf::Color(255, 127, 127, 255)); // clear old frame

        if (lastView != MENU) mainWindow->render(currentView, false);
        else mainWindow->render(currentView, true);

        mainWindow->getWindow()->display(); // indicates that the mainWindow is done rendering
    }
}

void Game::endGame() {
    delete mainWindow;
}