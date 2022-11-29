#include "include/view/MainWindow.h"

MainWindow::MainWindow() {
    this->window = nullptr;
    this->font = new sf::Font();

    initWindow();
}
MainWindow::~MainWindow() {
    delete this->font;
    delete this->window;
}

sf::RenderWindow* MainWindow::getWindow() { return this->window; }
sf::Font* MainWindow::getFont() { return this->font; }

sf::VideoMode* MainWindow::getVideoMode() { return &this->vMode; }

void MainWindow::setMenu(Menu* menu) { this->menu = menu; }

void MainWindow::initWindow() {
    this->vMode = sf::VideoMode::getDesktopMode();
    this->window = new sf::RenderWindow(
        this->vMode,
        "Strange Game",
        sf::Style::Titlebar | sf::Style::Close
    );
    this->window->setPosition(sf::Vector2i(0, 0));
    if (!this->font->loadFromFile("assets/pixelFont.ttf")) throw("ERROR::FONT_LOADING");
}

void MainWindow::render(ViewTypes* currentView)
{
    if (*currentView == MENU) displayMenuView(currentView);
    else return;
}

void MainWindow::displayMenuView(ViewTypes* currentView) 
{ 
   
}
