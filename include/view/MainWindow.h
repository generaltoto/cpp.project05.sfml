#ifndef CPP_SFML_MAINWINDOW_H
#define CPP_SFML_MAINWINDOW_H


#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <SFML/Audio.hpp>

#include "include/entities/TexturedElement.h"
#include "include/view/Button.h"
#include "include/Structures.h"

class MainWindow {

public:
    /// Menu to be dispalyed in the menu view.
    class Menu
    {
    private:
        MainWindow* contextWindow;
        void setValues();


    public:
        /// Currrently selected text 
        int currentSelected;

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

        /// Navigates through the menu depending on the input 
        void navigateMenu(ViewTypes* currentView);

        /// Draws the menu
        void draw();
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

    /// Returns the window's video mode
    sf::VideoMode* getVideoMode();

    void setMenu(Menu* menu);

    /// Initiates the windows and its parameters
    void initWindow();

    /// Renders our mainWindow.
    void render(ViewTypes* currentView);

    /// Displays the menu when ESC is pressed (paused = true)
    /// or when we launch the game (pause = false).
    void displayMenuView(ViewTypes* currentView);

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