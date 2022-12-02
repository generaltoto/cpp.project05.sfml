#pragma once
#include <SFML/Graphics.hpp>

#include "include/entities/TexturedElement.h"
#include "include/Structures.h"
#include "include/entities/Player.h"
#include "include/audio/Sound.h"
#include "include/audio/Music.h"

class MainWindow {

public:
    class Menu
    {
    protected:
        MainWindow* contextWindow;
        int currentSelected;

        sf::Texture bgAsset;
        sf::Sprite bg;

        std::vector<const char*> options;
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
        void navigate(
            bool activeCombat, ViewTypes* currentView, Sound* soundEffect
        );

        /// Draws the menu
        void draw();
    };

    class InventoryMenu
    {
    protected:
        MainWindow* contextWindow;
        Player* contextPlayer;

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

        void navigateItems(Sound* soundEffect, ViewTypes* currentView);

        void navigatePokemons(Sound* soundEffect, Player* p);

    public:
        InventoryMenu(MainWindow* window, Player* player);
        ~InventoryMenu();

        /// Allows to select the differents options in the inventory menu.
        void navigate(Sound* soundEffect, Player* p, ViewTypes* currentView);

        /// Draws the inventory menu.
        void draw();
    };

    class SettingsMenu {
    protected:
       MainWindow* contextWindow;
       int currentSelected;

       const char* bgPath = "assets/inventoryBackground.png";
       sf::Texture bgAsset;
       sf::Sprite bg;

       std::vector<const char*> options;
       std::vector<sf::Vector2f> textCoords;
       std::vector<sf::Text> texts;
       std::vector<std::size_t> sizes;

       std::vector<sf::Text> volText;
       std::vector<sf::Vector2f> volTextCoords;
       std::vector<std::size_t> volSizes;


       void setValues(Sound* soundEffect, Music* music);

    public:
       SettingsMenu(MainWindow* window, Sound* soundEffect, Music* music);
       ~SettingsMenu();

       /// Allows you to navigate in the settings.
       void navigate(ViewTypes* currentView, Sound* soundEffect, Music* music, Music* battleMusic);

       /// Updates the values of volumes to display.
       void updateDrawVol(Sound* soundEffect, Music* music);

       /// Displays the settings.
       void draw();
    };

private:
    sf::RenderWindow* window;
    sf::VideoMode vMode;
    sf::Font font;

public:
    MainWindow(const sf::Font&);
    ~MainWindow();

    /// Returns the window
    sf::RenderWindow* getWindow();

    /// Return the used font
    sf::Font &getFont();

    /// Returns the window's video mode
    sf::VideoMode* getVideoMode();

    /// Initiates the windows and its parameters
    void initWindow();
};
