//#include "include/Game.h"
#include "include/data/DataManager.h"
#include <iostream>

using json = nlohmann::json;


//int main() {
//    Game::startGame();
//
//    Game::runGame();
//
//    return 0;
//}

int main()
{

    DataManager::getPokemon(1);
    return 0;
}
