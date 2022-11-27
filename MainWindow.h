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

    public:
        int currentSelected;
        bool pressed, theselect;

        std::vector<const char*> options;
        std::vector<sf::Vector2f> textCoords;
        std::vector<sf::Text> texts;
        std::vector<std::size_t> sizes;

    protected:
        void setValues();
        void NavigateMenu();
        void drawAll();

    public:
        Menu(MainWindow* window);
        ~Menu();
        void runMenu();
    };

private:
    sf::RenderWindow* window;
    sf::VideoMode vMode;
    sf::Font* font;

    Menu* menu;

public:
    MainWindow();
    ~MainWindow();

    sf::RenderWindow* getWindow();

    sf::Font* getFont();

    void setMenu(Menu* menu);

    /// Initiates the windows and its parameters
    void initWindow();

    /// Renders our mainWindow.
    void render(ViewTypes* currentView);

    /// Displays the menu when ESC is pressed (paused = true)
    /// or when we launch the game (pause = false).
    void displayMenuView();

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