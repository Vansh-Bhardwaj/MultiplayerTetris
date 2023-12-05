#include "Game.hpp"
#include "Board.hpp"
#include "Tetromino.hpp"
#include <ctime>
#include <iostream>

Game::Game() : isGameOver(false) {
    srand(time(nullptr));  // Seed the random number generator
    tetromino = std::make_unique<Tetromino>(static_cast<Tetromino::TetrominoType>(std::rand() % 7));
    nextTetromino = std::make_unique<Tetromino>(static_cast<Tetromino::TetrominoType>(std::rand() % 7)); 

    if (!fontRegular.loadFromFile("assets/BaiJamjuree-Regular.ttf")) {
        // Handle error
    }

    if (!fontMinecraft.loadFromFile("assets/Minecraft.ttf")) {
        // Handle error
    }
    score = 0;
}

void Game::update() {
    if (!isGameOver) {
        if (tetrominoFallTimer.getElapsedTime().asSeconds() >= 0.55f) {
            tetromino->move(0, 1);

            if (board.isCollision(*tetromino)) {
                tetromino->move(0, -1);
                tryLockTetromino();
                if (isGameOver) {
                    return;
                }
            }
            tetrominoFallTimer.restart(); // Moved outside of the collision check
        }
    }
}



void Game::render(sf::RenderWindow& window) {
    board.draw(window);

    if (tetromino) {
        tetromino->draw(window);
    }

    sf::Text scoreText;
    scoreText.setFont(fontMinecraft);
    scoreText.setString("Score: " + std::to_string(score));
    scoreText.setPosition(250, 50);
    scoreText.setCharacterSize(24);
    window.draw(scoreText);

    sf::Text nextText;
    nextText.setFont(fontRegular);
    nextText.setString("Next:");
    nextText.setPosition(250, 100);
    nextText.setCharacterSize(20);
    window.draw(nextText);

    if (nextTetromino) {
        sf::Vector2i originalPos = nextTetromino->getPosition();
        nextTetromino->setPosition(12, 8);
        nextTetromino->draw(window);
        nextTetromino->setPosition(originalPos);
    }
}

void Game::handleEvent(const sf::Event &event) {
    if (event.type == sf::Event::KeyPressed) {
        switch (event.key.code) {
        case sf::Keyboard::Up:
        case sf::Keyboard::W:
            tetromino->rotateClockwise(board);
            if (board.isCollision(*tetromino)) {
                for (int i = 0; i < 3; i++) {
                    tetromino->rotateClockwise(board);
                }
            }
            break;

        case sf::Keyboard::Down:
        case sf::Keyboard::S:
            {
                while (!board.isCollision(*tetromino)) {
                    tetromino->move(0, 1);
                }
                tetromino->move(0, -1);
                tryLockTetromino();
                break;
            }


        case sf::Keyboard::Left:
        case sf::Keyboard::A:
            tetromino->move(-1, 0);
            if (board.isCollision(*tetromino)) {
                tetromino->move(1, 0);
            }
            break;

        case sf::Keyboard::Right:
        case sf::Keyboard::D:
            tetromino->move(1, 0);
            if (board.isCollision(*tetromino)) {
                tetromino->move(-1, 0);
            }
            break;
        }
    }
}

void Game::tryLockTetromino() {
    board.lockTetromino(*tetromino);
    
    int clearedRows = board.clearRows();
    score = board.getScore();

    tetromino = std::move(nextTetromino);
    nextTetromino = std::make_unique<Tetromino>(static_cast<Tetromino::TetrominoType>(std::rand() % 7));

    if (board.isCollision(*tetromino)) {
        isGameOver = true;
    }
}


void Game::startNewGame() {
    isGameOver = false;
}
