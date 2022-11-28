# ifndef CPP_SFML_GAME_H
# define CPP_SFML_GAME_H
# include "include/view/MainWindow.h"
# include "include/entities/Player.h"
# include <iostream>
/// Links all the inner members and the displayers
class Game {

public:
    /// Instantiation of our mainWindow
    static MainWindow* mainWindow;

    /// Starts the game by calling all the initializers.
    static void startGame();

    /// Handles the main loop of the game.
    static void runGame();

    /// Closes everything at the end.
    static void endGame();
};


#endif //CPP_SFML_GAME_H