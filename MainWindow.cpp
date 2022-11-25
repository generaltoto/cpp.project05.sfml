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
    displayMenuView();
}

void MainWindow::displayMenuView()
{
    TexturedElement background = TexturedElement(
        0, 0, "background", "assets/Menu.jpg"
    );
    background.resizeSprite(this->vMode.height, this->vMode.width);
    background.displayEntity(this->window);

    sf::Vector2f btnSize = { 200,50 };
    drawButton(
        btnSize,
        {
            (this->vMode.width / 2.f) - (btnSize.x / 2.f),
            (this->vMode.height / 2.f) - (btnSize.y / 2.f)
        },
        "assets/pixelFont.ttf",
        "Press ENTER to play",
        20,
        { 0,0,0,255 },
        { 127,127,127,127 }
    );
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

sf::RenderWindow* MainWindow::getWindow() {
    return this->window;
}

