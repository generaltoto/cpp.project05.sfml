#ifndef CPP_SFML_MAINWINDOW_H
#define CPP_SFML_MAINWINDOW_H


#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>

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
};


#endif //CPP_SFML_MAINWINDOW_H