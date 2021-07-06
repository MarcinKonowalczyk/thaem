#ifndef GAME_HPP
#define GAME_HPP

#include <piksel/baseapp.hpp>
#include "them.hpp"
#include "bullet.hpp"

#include <vector>
#include <string>
#include <random>
#include <iterator>

enum GameState {
    NONE = 0,
    START,
    LEVEL_1, INTERVAL_1,
    LEVEL_2, INTERVAL_2,
    LEVEL_3, INTERVAL_3,
    LEVEL_4, INTERVAL_4,
    LEVEL_5, INTERVAL_5,
    LEVEL_6, INTERVAL_6,
    ENDLESS, ENDLESS_INTERVAL
};

#define LEVELS_SWITCH case LEVEL_1: case LEVEL_2: case LEVEL_3: case LEVEL_4: case LEVEL_5: case LEVEL_6: case ENDLESS:
#define INTERVALS_SWITCH case INTERVAL_1: case INTERVAL_2: case INTERVAL_3: case INTERVAL_4: case INTERVAL_5: case INTERVAL_6: case ENDLESS_INTERVAL:

#define LEFT_MOUSE_BUTTON 0
#define RIGHT_MOUSE_BUTTON 1

#define WIDTH 960//640
#define HEIGHT 540//480
// Theme: Joined together
// What does is mean?
// What does it mean for that connection to break?

class Game : public piksel::BaseApp {
public:
    Game() : piksel::BaseApp(WIDTH, HEIGHT, "THAEM")
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
        , vectorShuffleCounter(0)
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
    void shuffleBulletVectors();
    unsigned int vectorShuffleCounter;
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

// https://stackoverflow.com/a/16421677/2531987
template<typename Iter, typename RandomGenerator>
Iter select_randomly(Iter start, Iter end, RandomGenerator& g) {
    std::uniform_int_distribution<> dis(0, std::distance(start, end) - 1);
    std::advance(start, dis(g));
    return start;
}

#endif /* GAME_HPP */