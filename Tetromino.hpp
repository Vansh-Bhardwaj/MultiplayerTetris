#pragma once

#include <SFML/Graphics.hpp>
#include <vector>
class Board;

class Tetromino {
public:
    // Define the different types of tetrominoes
    enum class TetrominoType {
        I, J, L, O, S, T, Z
    };

    Tetromino(TetrominoType type);

    // Draw the tetromino on the given window
    void draw(sf::RenderWindow& window);

    void rotateClockwise(Board& board);

    // Function to get color based on tetromino type
    static sf::Color getColor(TetrominoType type);

    // Get position of the tetromino
    sf::Vector2i getPosition() const {
        return position;
    }

    // Get the type of the tetromino
    TetrominoType getType() const {
        return type;
    }

    // Get the shape of the tetromino based on type and rotation
    std::vector<std::vector<int>> getShape() const {
        return shape;
    }

    // Public function to move the tetromino
    void move(int xOffset, int yOffset) {
        position.x += xOffset;
        position.y += yOffset;
    }

    void setPosition(int x, int y) {
        position.x = x;
        position.y = y;
    }

    void setPosition(const sf::Vector2i& pos) {
        position = pos;
    }

private:
    TetrominoType type;                   // The type of this tetromino
    sf::Vector2i position;                // Position of the tetromino (top-left block)
    int rotation;                         // Current rotation state (0-3 for most tetrominoes)
    std::vector<std::vector<int>> rotateMatrixClockwise(const std::vector<std::vector<int>>& matrix);
    static const std::vector<std::vector<std::vector<int>>> tetrominoShapes;
    std::vector<std::vector<int>> shape;
};
