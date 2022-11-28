#include "include/Game.h"

MainWindow* Game::mainWindow = nullptr;

void Game::startGame() {
    mainWindow = new MainWindow();
}

void Game::runGame() {
    Player sacha;

    MainWindow::Menu gameMenu(mainWindow);
    mainWindow->setMenu(&gameMenu);
    ViewTypes currentView = MENU;
   

    TileMap map;
    MapGenerator* mapGen = new MapGenerator(
        mainWindow->getVideoMode()->width, mainWindow->getVideoMode()->height
    );
    sf::View view;
    view.setCenter(sf::Vector2f((32 * mapGen->GetEntry()) / 0.6f, 32 * (MAPHEIGHT - 1) / 0.6f));
    view.setSize(sf::Vector2f(mainWindow->getVideoMode()->width/2, mainWindow->getVideoMode()->height/2));

    sacha.SetMapPosition(mapGen->GetEntry(), MAPHEIGHT-1);

    //2.9 pour 64 * 64   11.6 pour 256 * 256
    if (!map.load("assets/pixil-frame-0.png", sf::Vector2u(32, 32), mapGen->GetLevel2(), MAPWIDTH, MAPHEIGHT, 0.6))
        throw("ERROR::MAP_LOADING");

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
            sacha.updatePlayer(&frameCount, &view, mapGen->GetLevel2());
            mainWindow->getWindow()->setView(view);
            mainWindow->getWindow()->draw(map);
            sacha.setPos(view.getCenter().x - 4, view.getCenter().y - 33);
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