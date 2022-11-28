#include "include/view/MainWindow.h"

MainWindow::MainWindow() {
    this->window = new sf::RenderWindow();
    this->font = new sf::Font();

    initWindow();
}

MainWindow::~MainWindow() {
    delete this->window;
    delete this->font;
}

sf::RenderWindow* MainWindow::getWindow() { return this->window; }
sf::Font* MainWindow::getFont() { return this->font; }

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

void MainWindow::drawButton(
    sf::Vector2f dim,
    sf::Vector2f pos,
    std::string fontPath,
    std::string text,
    int textSize,
    sf::Color textCol,
    sf::Color shapeCol
)
{
    sf::Font font;
    if (!font.loadFromFile(fontPath))
        std::cout << "Couldn't load font " << fontPath << std::endl;
    else
    {
        Button button = Button(
            pos, dim, &font, text, textSize, textCol, shapeCol
        );
        button.display(this->window);
    }
}

