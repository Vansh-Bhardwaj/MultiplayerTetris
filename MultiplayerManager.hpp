#ifndef MULTIPLAYERMANAGER_HPP
#define MULTIPLAYERMANAGER_HPP

#include <SFML/Graphics.hpp>
#include "Board.hpp"
#include "Tetromino.hpp"
#include <memory>

class MultiplayerManager {
public:
    MultiplayerManager();
    void resetGame();
    void update();
    void render(sf::RenderWindow& window);
    void handleEvent(const sf::Event& event);
    sf::Font fontMinecraft;
    

private:
    Board player1Board, player2Board;
    std::unique_ptr<Tetromino> player1Tetromino, player2Tetromino;
    std::unique_ptr<Tetromino> player1NextTetromino, player2NextTetromino;
    int player1Score, player2Score;
    sf::Clock player1FallTimer, player2FallTimer;
    

    void updatePlayer(Board& board, std::unique_ptr<Tetromino>& tetromino,
                      std::unique_ptr<Tetromino>& nextTetromino, int& score, sf::Clock& fallTimer);
    void handlePlayerInput(const sf::Event& event, Board& board, std::unique_ptr<Tetromino>& tetromino, bool isPlayerOne);
    void renderBoard(sf::RenderWindow& window,  Board& board, const sf::Vector2f& position);
    void renderScore(sf::RenderWindow& window, int score, const sf::Vector2f& position);
    void renderNextTetromino(sf::RenderWindow& window,Tetromino* nextTetromino, const sf::Vector2f& position);
};

#endif // MULTIPLAYERMANAGER_HPP
