#ifndef BOARD_HPP
#define BOARD_HPP

#include <SFML/Graphics.hpp>
#include "Tetromino.hpp"
#include <vector>


class Board {

public:
    static constexpr int CELL_SIZE = 20;
    static constexpr int DEFAULT_WIDTH = 10; // Added these if you need static default values
    static constexpr int DEFAULT_HEIGHT = 20; // Same here
    static constexpr int BOARD_WIDTH_PIXELS = DEFAULT_WIDTH * CELL_SIZE;
    static constexpr int BOARD_HEIGHT_PIXELS = DEFAULT_HEIGHT * CELL_SIZE;

    int getWidth() const {
        return width;
    }

    int getHeight() const {
        return height;
    }
    sf::Vector2f getPosition() const {
        return position;
    }

    Board(int width = DEFAULT_WIDTH, int height = DEFAULT_HEIGHT); // Default values can be used
    bool isGameOver() const;
    void setAllBlocksGray();
    int getScore() const { return score; } 
    void reset();
    bool spawnTetromino(Tetromino& tetromino);
    void lockTetromino(const Tetromino& tetromino);
    int clearRows();
    bool isCollision(const Tetromino& tetromino) const;
    void draw(sf::RenderWindow& window) const;
    void setPosition(const sf::Vector2f& newPosition) {
    position = newPosition;}
    

private:
    std::vector<std::vector<sf::Color>> grid;
    const sf::Color EMPTY_COLOR = sf::Color::Black; // Empty cell color
    int width, height;
    void shiftRowsDownFrom(int startY);
    int rowsCleared = 0;
    int score = 0; 
    sf::Vector2f position;
};

#endif // BOARD_HPP

