# ifndef CPP_SFML_GAME_H
# define CPP_SFML_GAME_H
# include "include/view/MainWindow.h"
# include "include/entities/Player.h"
# include "include/map/TileMap.h"
# include "include/map/MapGenerator.h"
# include "data/DataManager.h"
# include "include/audio/Music.h"
# include <iostream>

using json = nlohmann::json;


/// Links all the inner members and the displayers
class Game {

public:
    /// Instantiation of our mainWindow
    static MainWindow* mainWindow;

    /// List of all pokemons
    static Pokemon pokemons[809];

    /// List of all capacities
    static Capacity capacities[619];

    static void createPokemons(
        int index,
        int x,
        int y,
        std::string name,
        std::string path,
        std::vector<std::string> types,
        std::string caption,
        int level,
        std::vector<int> stats
    );

    static void createCapacity(
        int index,
        std::string name,
        int damage,
        std::string attackType,
        std::string type,
        int accuracy
    );

    /// Starts the game by calling all the initializers.
    static void startGame();

    /// Handles the main loop of the game.
    static void runGame();
};


#endif //CPP_SFML_GAME_H