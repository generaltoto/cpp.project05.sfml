#include "MainWindow.h"

MainWindow::MainWindow() {
    this->window = nullptr;
}

MainWindow::~MainWindow() {
    delete this->window;
}

void MainWindow::initWindow() {
    this->vMode = sf::VideoMode::getDesktopMode();
    this->window = new sf::RenderWindow(
        this->vMode,
        "Strange Game",
        sf::Style::Titlebar | sf::Style::Close
    );
}

void MainWindow::render() 
{
    TexturedElement* background = new TexturedElement(
        0,0,"background","assets/Menu.jpg"
    );
    background->displayEntity(this->window);
}

void MainWindow::displayMenuView(bool paused)
{

}

sf::RenderWindow* MainWindow::getWindow() {
    return this->window;
}

