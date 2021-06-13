#ifndef GAME_HPP
#define GAME_HPP

#include <piksel/baseapp.hpp>
#include "them.hpp"
#include "bullet.hpp"

#include <vector>
#include <string>

enum GameState {
    NONE = 0,
    START,
    LEVEL_1,
    INTERVAL_1,
    LEVEL_2,
    INTERVAL_2,
    LEVEL_3
};

#define LEFT_MOUSE_BUTTON 0
#define RIGHT_MOUSE_BUTTON 1

#define WIDTH 640
#define HEIGHT 480
// #define NAME "as of yet untitled gamejam project"
#define GAME_NAME "THAEM"
// Theme: Joined together
// What does is mean?
// What does it mean for that connection to break?

class Game : public piksel::BaseApp {
public:
    Game() : piksel::BaseApp(WIDTH, HEIGHT, GAME_NAME)
        , state(START)
        , queuedState(NONE)
        , wipeCounter(0)
        , spawnCounter(30)
        , mousePosition(glm::vec2(WIDTH, HEIGHT))
        , them(Them())
        , rightMousePressed(false)
        , score(0)
        , blueBullets(std::vector<Bullet>(0))
        , redBullets(std::vector<Bullet>(0))
        , blackBullets(std::vector<Bullet>(0))
        , deathScreen(false)
        {}
    void setup();
    void draw(piksel::Graphics& g);
    void mouseMoved(int x, int y);
    void mousePressed(int button);
    void mouseReleased(int button);
    void keyPressed(int key);
private:
    std::string getScoreString();
    void setupCleanLevel();
    void wipeTo(GameState state);
    GameState state;
    GameState queuedState;
    unsigned int wipeCounter;
    unsigned int spawnCounter;
    glm::vec2 mousePosition;
    Them them;
    bool rightMousePressed;
    std::vector<Bullet> blueBullets;
    std::vector<Bullet> redBullets;
    std::vector<Bullet> blackBullets;
    /* Initialised in setup */
    piksel::Font font;
    unsigned int score;
    bool deathScreen;
};

#endif /* GAME_HPP */