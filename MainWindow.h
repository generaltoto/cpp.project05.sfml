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

public:
    /// Menu to be dispalyed in the menu view.
    class Menu
    {
    private:
        MainWindow* contextWindow;
        void setValues();
        void NavigateMenu(ViewTypes* currentView);
        void drawAll();

    public:
        /// Currrently selected text 
        int currentSelected;

        /// Allows to control if a key is already pressed to prevent 
        /// actions from beeing run multiple times per frame
        bool pressed;

        /// All options that will be displayed in the menu
        std::vector<const char*> options;
        
        /// Coordinates of texts
        std::vector<sf::Vector2f> textCoords;

        /// SFML managed texts
        std::vector<sf::Text> texts;
        
        /// Font size for each text
        std::vector<std::size_t> sizes;

        Menu(MainWindow* window);
        ~Menu();

        /// Checks the player's input and draws
        void runMenu(ViewTypes* currentView);
    };

private:
    sf::RenderWindow* window;
    sf::VideoMode vMode;
    sf::Font* font;

    Menu* menu;

public:
    MainWindow();
    ~MainWindow();

    /// Returns the window
    sf::RenderWindow* getWindow();

    /// Return the used font
    sf::Font* getFont();

    void setMenu(Menu* menu);

    /// Initiates the windows and its parameters
    void initWindow();

    /// Renders our mainWindow.
    void render(ViewTypes* currentView);

    /// Displays the menu when ESC is pressed (paused = true)
    /// or when we launch the game (pause = false).
    void displayMenuView(ViewTypes* currentView);

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