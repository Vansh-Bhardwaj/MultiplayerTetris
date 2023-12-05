#include "Board.hpp"
#include <iostream>

Board::Board(int width, int height) : width(width), height(height) {
    grid.resize(height, std::vector<sf::Color>(width, EMPTY_COLOR));
}

void Board::reset() {
    for (int y = 0; y < height; y++)
        for (int x = 0; x < width; x++)
            grid[y][x] = EMPTY_COLOR;
}

bool Board::isGameOver() const {
    for (int x = 0; x < width; x++) {
        if (grid[0][x] != EMPTY_COLOR) {
            return true;
        }
    }
    return false;
}

void Board::lockTetromino(const Tetromino& tetromino) {
    std::vector<std::vector<int>> shape = tetromino.getShape();
    sf::Vector2i position = tetromino.getPosition();
    for (int y = 0; y < shape.size(); y++) {
        for (int x = 0; x < shape[y].size(); x++) {
            if (shape[y][x] && 
                position.x + x >= 0 && 
                position.x + x < width && 
                position.y + y >= 0 && 
                position.y + y < height) {
                    grid[position.y + y][position.x + x] = tetromino.getColor(tetromino.getType());
            }
        }
    }
    if (isGameOver()) {
        setAllBlocksGray();
    }
    clearRows();
}

void Board::shiftRowsDownFrom(int startY) {
    for (int yy = startY; yy > 0; yy--) {
        for (int x = 0; x < width; x++) {
            grid[yy][x] = grid[yy-1][x];
        }
    }
}


int Board::clearRows() {
    int rowsClearedThisCall = 0;
    for (int y = height - 1; y >= 0; y--) {
        bool fullRow = true;
        for (int x = 0; x < width; x++) {
            if (grid[y][x] == EMPTY_COLOR) {
                fullRow = false;
                break;
            }
        }
        if (fullRow) {
            shiftRowsDownFrom(y);
            rowsClearedThisCall++;
            rowsCleared++;  // Increment the cumulative counter
            score += 100;
            y++;  // Check the new row that we just moved down.
        }
    }
    
    std::cout << "Total rows cleared in this call: " << rowsClearedThisCall << std::endl;
    std::cout << "Cumulative rows cleared: " << rowsCleared << std::endl;  // Print the cumulative total
    return rowsClearedThisCall;  // Return the number of rows cleared in this call, useful for scoring.
}

bool Board::isCollision(const Tetromino& tetromino) const {
    std::vector<std::vector<int>> shape = tetromino.getShape();
    sf::Vector2i position = tetromino.getPosition();
    for (int y = 0; y < shape.size(); y++) {
        for (int x = 0; x < shape[y].size(); x++) {
            if (shape[y][x] == 1) {
                if (position.x + x < 0 || 
                    position.x + x >= width || 
                    position.y + y < 0 || 
                    position.y + y >= height ||
                    grid[position.y + y][position.x + x] != EMPTY_COLOR) {
                    return true;
                }
            }
        }
    }
    return false;
}

void Board::draw(sf::RenderWindow& window) const {
    const int cellSize = CELL_SIZE; 
    for (int y = 0; y < height; y++)
        for (int x = 0; x < width; x++) {
            sf::RectangleShape cell({cellSize - 1.0f, cellSize - 1.0f}); 
            cell.setPosition(x * cellSize, y * cellSize);
            cell.setFillColor(grid[y][x]);
            window.draw(cell);
        }
}

void Board::setAllBlocksGray() {
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            if (grid[y][x] != EMPTY_COLOR) { 
                grid[y][x] = sf::Color(128, 128, 128);
            }
        }
    }
}
