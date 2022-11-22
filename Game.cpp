#include "Game.h"

MainWindow* Game::mainWindow = nullptr;

void Game::startGame() {
    mainWindow = new MainWindow();
    mainWindow->initWindow();
}

void Game::runGame() {
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
                if (e.key.code == sf::Keyboard::Escape)
                    mainWindow->getWindow()->close();
                break;
            default:
                break;
            }
        }

        mainWindow->getWindow()->clear(sf::Color(255, 127, 127, 255)); // clear old frame

        // draw game between these two

        mainWindow->getWindow()->display(); // indicates that the mainWindow is done rendering
    }
}

void Game::endGame() {
    delete mainWindow;
}