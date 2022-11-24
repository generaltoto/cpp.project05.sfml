#ifndef CPP_SFML_MAINWINDOW_H
#define CPP_SFML_MAINWINDOW_H


#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <SFML/Audio.hpp>

#include "TexturedElement.h"
#include "Button.h"
#include "Structures.h"

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
    void render(ViewType view, bool isPaused);

    /// Displays the menu when ESC is pressed (paused = true)
    /// or when we launch the game (pause = false).
    void displayMenuView(ViewType view, bool isPaused);

    void drawText(
        unsigned int x, unsigned int y,
        std::string fontPath, 
        std::string text, 
        sf::Color textColor
    );

    /// Draws a button depending on the following arguments
    void drawButton(
        sf::Vector2f dim,
        sf::Vector2f pos,
        std::string fontPath,
        std::string text,
        int textSize,
        sf::Color textCol,
        sf::Color shapeCol
    );
};


#endif //CPP_SFML_MAINWINDOW_H