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
    bool paused = false;
    displayMenuView(paused);
}

void MainWindow::displayMenuView(bool paused)
{
    TexturedElement background = TexturedElement(
        0, 0, "background", "assets/Menu.jpg"
    );
    background.resizeSprite(this->vMode.height, this->vMode.width);
    background.displayEntity(this->window);

    if (paused)
    {
        drawButton(
            { 600, 300 },
            "assets/pixelFont.ttf",
            "Resume",
            { 0,0,0,255 },
            { 127,127,127,127 }
        );
    }
    else
    {
        drawButton(
            { 600, 300 },
            "assets/pixelFont.ttf",
            "Play",
            { 0,0,0,255 },
            { 127,127,127,127 }
        );
    }

    
}

void MainWindow::drawButton(
    sf::Vector2f dim,
    std::string fontPath,
    std::string text,
    sf::Color textCol,
    sf::Color shapeCol
)
{
    sf::Vector2f btnPos{
        this->vMode.width - dim.x / 2,
        this->vMode.height - dim.y / 2
    };

    sf::Font font;
    if (!font.loadFromFile(fontPath))
        std::cout << "Couldn't load font " << fontPath << std::endl;
    else
    {
        Button button = Button(btnPos, dim, &font, text, textCol, shapeCol);
        button.display(this->window);
    }
}

sf::RenderWindow* MainWindow::getWindow() {
    return this->window;
}

