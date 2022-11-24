#include "Game.h"

MainWindow* Game::mainWindow = nullptr;

void Game::startGame() {
    mainWindow = new MainWindow();
    mainWindow->initWindow();
}

void Game::runGame() {
    Player sacha;
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
                if (e.key.code == sf::Keyboard::Escape)
                    mainWindow->getWindow()->close();
                else if (e.key.code == sf::Keyboard::Up) {
                   sacha.move(0,1);
                }
                else if (e.key.code == sf::Keyboard::Down) {
                   sacha.move(0, -1);
                   if (frameCount % 20 == 0) {
                      sacha.nextAnimation();
                      frameCount = 0;
                   }
                }
                else if (e.key.code == sf::Keyboard::Right) {
                   sacha.move(1, 0);
                }
                else if (e.key.code == sf::Keyboard::Left) {
                   sacha.move(-1, 0);
                }
                break;
            default:
                break;
            }
            std::cout << sacha.getPos('x') << sacha.getPos('y') << std::endl;
        }
        
        frameCount++;
        sacha.displayEntity(mainWindow->getWindow());

        mainWindow->render();

        mainWindow->getWindow()->display(); // indicates that the mainWindow is done rendering
    }
}

void Game::endGame() {
    delete mainWindow;
}