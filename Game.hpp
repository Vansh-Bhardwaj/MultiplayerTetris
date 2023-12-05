#include <SFML/Graphics.hpp>
#include <memory> // for std::unique_ptr
#include "Board.hpp"
#include "Tetromino.hpp"

class Game {
public:
    Game();

    void handleEvent(const sf::Event& event);
    void update();
    void render(sf::RenderWindow& window);
    void startNewGame(); // You mentioned this in the error list, so I've added it here
    bool isGameOver;

private:
    Board board;
    std::unique_ptr<Tetromino> tetromino; // Change Tetromino to unique_ptr to match the Game.cpp usage
    sf::Clock tetrominoFallTimer;
    std::unique_ptr<Tetromino> nextTetromino;
    int score;
    void tryLockTetromino();
    sf::Font fontRegular;
    sf::Font fontMinecraft;

    // ... other game state variables and methods ...
};
