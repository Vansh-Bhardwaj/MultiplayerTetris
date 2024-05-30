#include "MultiplayerManager.hpp"
#include "Game.hpp"
#include <iostream>
#include <memory>
#include <SFML/Graphics.hpp>
#include <SFML/System/Clock.hpp>
#include "Board.hpp"

// Constructor
MultiplayerManager::MultiplayerManager() 

    : player1Board(Board::DEFAULT_WIDTH, Board::DEFAULT_HEIGHT), 
      player2Board(Board::DEFAULT_WIDTH, Board::DEFAULT_HEIGHT),
      player1Score(0), player2Score(0) 
      {
        
        
    // Initialize Tetrominos for each player
    player1Tetromino = std::make_unique<Tetromino>(static_cast<Tetromino::TetrominoType>(std::rand() % 7));
    player2Tetromino = std::make_unique<Tetromino>(static_cast<Tetromino::TetrominoType>(std::rand() % 7));
    player1NextTetromino = std::make_unique<Tetromino>(static_cast<Tetromino::TetrominoType>(std::rand() % 7));
    player2NextTetromino = std::make_unique<Tetromino>(static_cast<Tetromino::TetrominoType>(std::rand() % 7));
}

// Reset game state for multiplayer
void MultiplayerManager::resetGame() {
    player1Board.reset();
    player2Board.reset();
    player1Score = player2Score = 0;
    player1Tetromino = std::make_unique<Tetromino>(static_cast<Tetromino::TetrominoType>(std::rand() % 7));
    player2Tetromino = std::make_unique<Tetromino>(static_cast<Tetromino::TetrominoType>(std::rand() % 7));
    player1NextTetromino = std::make_unique<Tetromino>(static_cast<Tetromino::TetrominoType>(std::rand() % 7));
    player2NextTetromino = std::make_unique<Tetromino>(static_cast<Tetromino::TetrominoType>(std::rand() % 7));
    player1FallTimer.restart();
    player2FallTimer.restart();
}

// Update state for multiplayer game
void MultiplayerManager::update() {
    updatePlayer(player1Board, player1Tetromino, player1NextTetromino, player1Score, player1FallTimer);
    updatePlayer(player2Board, player2Tetromino, player2NextTetromino, player2Score, player2FallTimer);
}

// Update individual player
void MultiplayerManager::updatePlayer(Board& board, std::unique_ptr<Tetromino>& tetromino, std::unique_ptr<Tetromino>& nextTetromino, int& score, sf::Clock& fallTimer) {
    if (fallTimer.getElapsedTime().asSeconds() >= 0.55f) {
        if (tetromino) {
            tetromino->move(0, 1);

            if (board.isCollision(*tetromino)) {
                tetromino->move(0, -1);
                board.lockTetromino(*tetromino);
                int rowsCleared = board.clearRows();
                score += rowsCleared * 100;
                tetromino = std::move(nextTetromino);
                nextTetromino = std::make_unique<Tetromino>(static_cast<Tetromino::TetrominoType>(std::rand() % 7));
            }
        }
        fallTimer.restart();
    }
}


// Render multiplayer game
void MultiplayerManager::render(sf::RenderWindow& window) {
    float middleGap = 200; // Adjust gap as necessary
    sf::Vector2f boardOffset(0, 0); // Starting position of the first board
    sf::Vector2f player1Position = boardOffset;
    sf::Vector2f player2Position = boardOffset + sf::Vector2f(Board::BOARD_WIDTH_PIXELS + middleGap, 0);

   // Draw the first player's board, score, and next tetromino
    renderBoard(window, player1Board, player1Position);
    renderScore(window, player1Score, player1Position - sf::Vector2f(0, 30));
    renderNextTetromino(window, player1NextTetromino.get(), player1Position + sf::Vector2f(Board::BOARD_WIDTH_PIXELS + 20, 100));

    // Draw the second player's board, score, and next tetromino
    renderBoard(window, player2Board, player2Position);
    renderScore(window, player2Score, player2Position - sf::Vector2f(0, 30));
    renderNextTetromino(window, player2NextTetromino.get(), player2Position + sf::Vector2f(Board::BOARD_WIDTH_PIXELS + 20, 100)); // Adjust X and Y as needed
}

// Render methods for board, score, and next tetromino
void MultiplayerManager::renderBoard(sf::RenderWindow& window, Board& board, const sf::Vector2f& position) {
    board.setPosition(position);
    board.draw(window);
}


void MultiplayerManager::renderScore(sf::RenderWindow& window, int score, const sf::Vector2f& position) {
    sf::Text scoreText;
    scoreText.setFont(fontMinecraft);
    scoreText.setString("Score: " + std::to_string(score));
    scoreText.setCharacterSize(24);
    scoreText.setFillColor(sf::Color::White);
    scoreText.setPosition(position);
    window.draw(scoreText);
}

void MultiplayerManager::renderNextTetromino(sf::RenderWindow& window, Tetromino* nextTetromino, const sf::Vector2f& position) {
    if (nextTetromino) {
        nextTetromino->draw(window, position);
    }
}
void MultiplayerManager::handleEvent(const sf::Event& event) {
    // Assuming you have separate methods to handle inputs for player 1 and player 2
    if (event.type == sf::Event::KeyPressed) {
        handlePlayerInput(event, player1Board, player1Tetromino, true); // Player 1 (WASD)
        handlePlayerInput(event, player2Board, player2Tetromino, false); // Player 2 (Arrow keys)
    }
}



void MultiplayerManager::handlePlayerInput(const sf::Event& event, Board& board, std::unique_ptr<Tetromino>& tetromino, bool isPlayerOne) {
    if (!tetromino) return;

    if (event.type == sf::Event::KeyPressed) {
        if (isPlayerOne) {
            switch (event.key.code) {
                case sf::Keyboard::W:
                    tetromino->rotateClockwise(board);
                    break;
                case sf::Keyboard::A:
                    tetromino->move(-1, 0);
                    break;
                case sf::Keyboard::S:
                    tetromino->move(0, 1);
                    break;
                case sf::Keyboard::D:
                    tetromino->move(1, 0);
                    break;
            }
        } else {
            switch (event.key.code) {
                case sf::Keyboard::Up:
                    tetromino->rotateClockwise(board);
                    break;
                case sf::Keyboard::Left:
                    tetromino->move(-1, 0);
                    break;
                case sf::Keyboard::Down:
                    tetromino->move(0, 1);
                    break;
                case sf::Keyboard::Right:
                    tetromino->move(1, 0);
                    break;
            }
        }
    }
}

