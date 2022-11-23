#ifndef CPP_SFML_MAINWINDOW_H
#define CPP_SFML_MAINWINDOW_H


#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <SFML/Audio.hpp>

#include "TexturedElement.h"
#include "Button.h"

class MainWindow {

private:
    sf::RenderWindow* window;
    sf::VideoMode vMode;

public:
    MainWindow();
    ~MainWindow();

    sf::RenderWindow* getWindow();

    /// Initiates the windows and its parameters
    void initWindow();

    /// Renders our mainWindow.
    void render();

    /// Displays the menu when ESC is pressed (paused = true)
    /// or when we launch the game (pause = false).
    void displayMenuView(bool paused);

    /// Draws a button depending on the following arguments
    void drawButton(
        sf::Vector2f dim,
        std::string fontPath,
        std::string text,
        sf::Color textCol,
        sf::Color shapeCol
    );
};


#endif //CPP_SFML_MAINWINDOW_H