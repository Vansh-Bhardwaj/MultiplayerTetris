// Game.hpp
#include <SFML/Graphics.hpp>
#include "MultiplayerManager.hpp"
#include "Board.hpp"
#include "Tetromino.hpp"

class Game {
public:
    Game();
    void handleEvent(const sf::Event& event);
    void update();
    void render(sf::RenderWindow& window);
    void switchToMultiplayerMode();
    void startNewGame();
    void setupGridSprites();
    bool isGameOver;
    sf::Font fontRegular;
    sf::Font fontMinecraft;
    bool isMultiplayerMode() const { return multiplayerMode; }

private:
    Board board;
    void drawGridToTexture(sf::RenderTexture &texture);
    std::unique_ptr<Tetromino> tetromino;
    std::unique_ptr<Tetromino> nextTetromino;
    sf::RenderTexture gridTexture1;
    sf::RenderTexture gridTexture2;
    sf::Sprite gridSprite1;
    sf::Sprite gridSprite2;
    int score;
    bool multiplayerMode;
    MultiplayerManager multiplayerManager;
    sf::Clock tetrominoFallTimer;
    void tryLockTetromino();
};
