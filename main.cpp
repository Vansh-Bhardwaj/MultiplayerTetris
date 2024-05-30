#include <SFML/Window.hpp>
#include <SFML/OpenGL.hpp>
#include <SFML/Graphics.hpp>
#include "Game.hpp"
#include "Board.hpp"
#include <iostream>

void drawGridToTexture(sf::RenderTexture &texture)
{
    texture.clear(sf::Color::Transparent); // Clear with a transparent background

    // Color for the grid lines (e.g., grey)
    sf::Color gridColor(128, 128, 128); // Grey color

    // Draw vertical lines
    for (int i = 0; i <= Board::DEFAULT_WIDTH; ++i)
    {
        float x = i * Board::CELL_SIZE;
        sf::RectangleShape line(sf::Vector2f(Board::BOARD_WIDTH_PIXELS, Board::BOARD_HEIGHT_PIXELS));
        line.setPosition(x, 0);
        line.setFillColor(gridColor);
        texture.draw(line);
    }

    // Draw horizontal lines
    for (int i = 0; i <= Board::DEFAULT_HEIGHT; ++i)
    {
        float y = i * Board::CELL_SIZE;
        sf::RectangleShape line(sf::Vector2f(Board::BOARD_WIDTH_PIXELS, Board::BOARD_HEIGHT_PIXELS));
        line.setPosition(0, y);
        line.setFillColor(gridColor);
        texture.draw(line);
    }

    texture.display();
}

int main() {
    sf::RenderWindow window(sf::VideoMode(1200, 600), "Tetris - SFML", sf::Style::Default, sf::ContextSettings(0, 0, 0, 3, 3));
    window.setVerticalSyncEnabled(true);
    Game game; // Game now handles grid sprites internally

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();

            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::M) {
                game.switchToMultiplayerMode(); // Toggle multiplayer mode
            }

            game.handleEvent(event); // Event handling
            
        }

        game.update(); // Update game logic

        window.clear(); // Clear the screen
        game.render(window); // Render the game

        window.display(); // Display the window contents
    }

    return 0;
}

