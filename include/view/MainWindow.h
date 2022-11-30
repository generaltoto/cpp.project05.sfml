#ifndef CPP_SFML_MAINWINDOW_H
#define CPP_SFML_MAINWINDOW_H


#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <SFML/Audio.hpp>

#include "include/entities/TexturedElement.h"
#include "include/Structures.h"
#include "include/entities/Player.h"
#include <sstream>
#include "include/audio/Sound.h"

class MainWindow {

public:
    /// Menu to be dispalyed in the menu view.
    class Menu
    {
    protected:
        MainWindow* contextWindow;
        int currentSelected;

        const char* bgPath = "assets/menuBackground.jpg";
        sf::Texture bgAsset;
        sf::Sprite bg;

        std::vector<const char*> options;
        std::vector<sf::Vector2f> textCoords;
        std::vector<sf::Text> texts;
        std::vector<std::size_t> sizes;

        std::vector<sf::Vector2f> zoneCoords;
        sf::Vector2f zoneSize;
        std::vector<sf::RectangleShape> zones;

        void setValues();

    public:
        Menu(MainWindow* window);
        ~Menu();

        /// Navigates through the menu depending on the input 
        void navigateMenu(ViewTypes* currentView, Sound* soundEffect);

        /// Draws the menu
        void draw();
    };

    class InventoryMenu
    {
    protected:
        MainWindow* contextWindow;
        Player* contextPlayer;

        const char* bgPath = "assets/inventoryBackground.png";
        sf::Texture bgAsset;
        sf::Sprite bg;

        int currentSelected;
        bool healingPokemon;
        SprayType healingType;

        std::vector<sf::Vector2f> pZoneCoords;
        sf::Vector2f pZoneSize;
        std::vector<sf::RectangleShape> pZones;

        std::vector<sf::Vector2f> iZoneCoords;
        sf::Vector2f iPokeballZoneSize;
        sf::Vector2f iSprayZoneSize;
        std::vector<sf::RectangleShape> iZones;

        void setValues();

        void navigateItems();

        void navigatePokemons();

    public:
        InventoryMenu(MainWindow* window, Player* player);
        ~InventoryMenu();

        void navigate();

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