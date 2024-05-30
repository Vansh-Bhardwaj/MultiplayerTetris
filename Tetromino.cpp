#include "Tetromino.hpp"
#include "Board.hpp"
#include <ctime>
#include <cstdlib>

// Define the tetromino shapes in a 4x4 matrix
const std::vector<std::vector<std::vector<int>>> Tetromino::tetrominoShapes = {
    // I shape
    {
        {1, 0, 0, 0},
        {1, 0, 0, 0},
        {1, 0, 0, 0},
        {1, 0, 0, 0}
    },
    // J shape
    {
        {0, 1, 0, 0},
        {0, 1, 0, 0},
        {1, 1, 0, 0},
        {0, 0, 0, 0}
    },
    // L shape
    {
        {1, 0, 0, 0},
        {1, 0, 0, 0},
        {1, 1, 0, 0},
        {0, 0, 0, 0}
    },
    // O shape
    {
        {1, 1, 0, 0},
        {1, 1, 0, 0},
        {0, 0, 0, 0},
        {0, 0, 0, 0}
    },
    // S shape
    {
        {0, 1, 1, 0},
        {1, 1, 0, 0},
        {0, 0, 0, 0},
        {0, 0, 0, 0}
    },
    // T shape
    {
        {0, 1, 0, 0},
        {1, 1, 1, 0},
        {0, 0, 0, 0},
        {0, 0, 0, 0}
    },
    // Z shape
    {
        {1, 1, 0, 0},
        {0, 1, 1, 0},
        {0, 0, 0, 0},
        {0, 0, 0, 0}
    }
};

Tetromino::Tetromino(TetrominoType type) : type(type), position(4, 0), rotation(0) {shape = tetrominoShapes[static_cast<int>(type)];}

void Tetromino::draw(sf::RenderWindow& window, const sf::Vector2f& boardPosition) {
    for (int y = 0; y < 4; y++) {
        for (int x = 0; x < 4; x++) {
            if (shape[y][x] == 1) {
                sf::RectangleShape rect(sf::Vector2f(Board::CELL_SIZE, Board::CELL_SIZE));
                rect.setFillColor(getColor(type));
                rect.setPosition(boardPosition.x + (position.x + x) * Board::CELL_SIZE, 
                                 boardPosition.y + (position.y + y) * Board::CELL_SIZE);
                window.draw(rect);
            }
        }
    }
}



std::vector<std::vector<int>> Tetromino::rotateMatrixClockwise(const std::vector<std::vector<int>>& matrix) {
    int N = matrix.size();
    std::vector<std::vector<int>> result(N, std::vector<int>(N));

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            result[j][N - 1 - i] = matrix[i][j];
        }
    }
    return result;
}

void Tetromino::rotateClockwise(Board& board) {
    if (type == TetrominoType::O) {
        return; // 'O' tetromino doesn't need rotation.
    }

    // Store the old shape and position to revert if needed
    auto oldShape = shape;
    auto oldPosition = position;

    // Perform the rotation
    shape = rotateMatrixClockwise(shape);

    // Adjust Tetromino position based on 'active' blocks
    for (int y = 0; y < 4; y++) {
        for (int x = 0; x < 4; x++) {
            if (shape[y][x] == 1) {
                while (position.x + x < 0) position.x++; // Move right if too far left
                while (position.x + x >= board.getWidth()) position.x--; // Move left if too far right
            }
        }
    }

    // If there's a collision after adjustments, revert the rotation and position
    if (board.isCollision(*this)) {
        shape = oldShape;
        position = oldPosition;
    }
}






sf::Color Tetromino::getColor(TetrominoType type) {
    switch (type) {
        case TetrominoType::I: return sf::Color::Cyan;
        case TetrominoType::J: return sf::Color::Blue;
        case TetrominoType::L: return sf::Color::White;
        case TetrominoType::O: return sf::Color::Yellow;
        case TetrominoType::S: return sf::Color::Green;
        case TetrominoType::T: return sf::Color::Magenta;
        case TetrominoType::Z: return sf::Color::Red;
        default: return sf::Color::Black;  
    }
}


