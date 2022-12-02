#include "include/view/MainWindow.h"

MainWindow::MainWindow(const sf::Font &font) {
    this->window = nullptr;
    this->font = font;

    initWindow();
}
MainWindow::~MainWindow() {
    delete this->window;
}

sf::RenderWindow* MainWindow::getWindow() { return this->window; }
sf::Font &MainWindow::getFont() { return this->font; }

sf::VideoMode* MainWindow::getVideoMode() { return &this->vMode; }

void MainWindow::initWindow() {
    this->vMode = sf::VideoMode::getDesktopMode();
    this->window = new sf::RenderWindow(
        this->vMode,
        "Pokemon RGB",
        sf::Style::Titlebar | sf::Style::Close
    );
    this->window->setPosition(sf::Vector2i(0, 0));
    if (!this->font.loadFromFile(FONT_ASSET_PATH)) throw("ERROR::FONT_LOADING");
}
