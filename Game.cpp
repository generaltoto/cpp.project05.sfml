#include "Game.h"

MainWindow* Game::mainWindow = nullptr;

void Game::startGame() {
    mainWindow = new MainWindow();
}

void Game::runGame() {
    Player sacha;
    MainWindow::Menu gameMenu(mainWindow);
    mainWindow->setMenu(&gameMenu);
    ViewTypes currentView = MENU;

    int frameCount = 0;
    sf::Event e{};
    
    while (mainWindow->getWindow()->isOpen())
    {
       mainWindow->getWindow()->clear(sf::Color(255, 127, 127, 255)); // clear old frame

        while (mainWindow->getWindow()->pollEvent(e))
        {
            switch (e.type) {
            case sf::Event::Closed:
                mainWindow->getWindow()->close();
                break;
            case sf::Event::KeyPressed:
                if (e.key.code == sf::Keyboard::Escape && currentView != MENU)
                    currentView = MENU;
                else gameMenu.navigateMenu(&currentView);
                break;
            default:
                break;
            }
        }
        frameCount++;
        switch (currentView)
        {
        case MENU:
            gameMenu.draw();
            break;
        case PLAY:
            sacha.updatePlayer(&frameCount);
            sacha.displayEntity(mainWindow->getWindow());
            break;
        case COMBAT:
            break;
        default:
            break;
        }

        mainWindow->getWindow()->display(); // indicates that the mainWindow is done rendering
    }
}

void Game::endGame() {
    delete mainWindow;
}