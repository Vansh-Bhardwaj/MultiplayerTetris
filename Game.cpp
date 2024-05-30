#include "Game.hpp"
#include "Board.hpp"
#include "Tetromino.hpp"
#include <ctime>
#include <iostream>

Game::Game()
    : isGameOver(false),
      multiplayerMode(false),
      score(0),
      tetromino(std::make_unique<Tetromino>(static_cast<Tetromino::TetrominoType>(rand() % 7))),
      nextTetromino(std::make_unique<Tetromino>(static_cast<Tetromino::TetrominoType>(rand() % 7))) {
    srand(static_cast<unsigned int>(time(nullptr))); // Seed the random number generator

    if (!fontRegular.loadFromFile("assets/BaiJamjuree-Regular.ttf")) {
        // Handle error
    }

    if (!fontMinecraft.loadFromFile("assets/Minecraft.ttf")) {
        // Handle error
    }
    // Set up grid sprites here if they are needed upon construction
    setupGridSprites();
}
void Game::drawGridToTexture(sf::RenderTexture &texture) {
    // Function implementation...
}

void Game::update() {
    // Use multiplayerMode directly as a variable
    if (multiplayerMode) {
        multiplayerManager.update(); 
    } else {
        if (!isGameOver)
        {
            if (tetrominoFallTimer.getElapsedTime().asSeconds() >= 0.55f)
            {
                tetromino->move(0, 1);

                if (board.isCollision(*tetromino))
                {
                    tetromino->move(0, -1);
                    tryLockTetromino();
                    if (isGameOver)
                    {
                        return;
                    }
                }
                tetrominoFallTimer.restart(); // Moved outside of the collision check
            }
        }
    }
}

void Game::render(sf::RenderWindow& window) {
    if (multiplayerMode) {
        // Draw both grids for multiplayer
        window.draw(gridSprite1);
        window.draw(gridSprite2);
        multiplayerManager.render(window);  // Render multiplayer game elements
    } else {
        // Draw single grid for singleplayer
        window.draw(gridSprite1);
        board.draw(window);  // Draw the single-player board

        if (tetromino) {
            tetromino->draw(window, sf::Vector2f(0, 0));
        }

        // Draw score and next tetromino text
        sf::Text scoreText, nextText;
        scoreText.setFont(fontMinecraft);
        scoreText.setString("Score: " + std::to_string(score));
        scoreText.setPosition(250, 50);
        scoreText.setCharacterSize(24);
        window.draw(scoreText);

        nextText.setFont(fontRegular);
        nextText.setString("Next:");
        nextText.setPosition(250, 100);
        nextText.setCharacterSize(20);
        window.draw(nextText);

        if (nextTetromino) {
            sf::Vector2i originalPos = nextTetromino->getPosition();
            nextTetromino->setPosition(12, 8);
            nextTetromino->draw(window, sf::Vector2f(250, 100));
            nextTetromino->setPosition(originalPos);
        }
    }
}

void Game::handleEvent(const sf::Event &event) {
    if (multiplayerMode) {
        multiplayerManager.handleEvent(event);
    } else {
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

}
void Game::switchToMultiplayerMode() {
    multiplayerMode = !multiplayerMode;
    if (multiplayerMode) {
        multiplayerManager.resetGame();
    }
    // We might need to set up the grid sprites again if they change between modes
    setupGridSprites();
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
void Game::setupGridSprites() {
    if (!gridTexture1.create(Board::BOARD_WIDTH_PIXELS, Board::BOARD_HEIGHT_PIXELS) ||
        !gridTexture2.create(Board::BOARD_WIDTH_PIXELS, Board::BOARD_HEIGHT_PIXELS)) {
        // Handle error
    }
    drawGridToTexture(gridTexture1);
    drawGridToTexture(gridTexture2);
    gridSprite1.setTexture(gridTexture1.getTexture());
    gridSprite2.setTexture(gridTexture2.getTexture());
    float middleGap = 200;
    gridSprite1.setPosition(0, 0);
    gridSprite2.setPosition(Board::BOARD_WIDTH_PIXELS + middleGap, 0);
}