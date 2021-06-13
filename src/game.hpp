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
    LEVEL_1, INTERVAL_1,
    LEVEL_2, INTERVAL_2,
    LEVEL_3, INTERVAL_3,
    LEVEL_4, INTERVAL_4,
    LEVEL_5, INTERVAL_5,
    LEVEL_6, INTERVAL_6,
    ENDLESS
};

#define LEVELS_SWITCH case LEVEL_1: case LEVEL_2: case LEVEL_3: case LEVEL_4: case LEVEL_5: case LEVEL_6:
#define INTERVALS_SWITCH case INTERVAL_1: case INTERVAL_2: case INTERVAL_3: case INTERVAL_4: case INTERVAL_5: case INTERVAL_6:

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
    std::string getScoreString(int scoreIn);
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