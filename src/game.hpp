#ifndef GAME_HPP
#define GAME_HPP

#include <piksel/baseapp.hpp>
#include "them.hpp"

enum GameState {
    NONE = 0,
    START,
    GAME,
    RESTART,
};

#define LEFT_MOUSE_BUTTON 0
#define RIGHT_MOUSE_BUTTON 1

#define WIDTH 640
#define HEIGHT 480
#define NAME "as of yet untitled gamejam project"
// Theme: Joined together
// What does is mean?
// What does it mean for that connection to break?

class Game : public piksel::BaseApp {
public:
    Game() : piksel::BaseApp(WIDTH, HEIGHT, NAME)
        , state(START)
        , queuedState(NONE)
        , wipeCounter(0)
        , mousePosition(glm::vec2(WIDTH, HEIGHT))
        , them(Them())
        , rightMousePressed(false)
        {}
    void setup();
    void draw(piksel::Graphics& g);
    void mouseMoved(int x, int y);
    void mousePressed(int button);
    void mouseReleased(int button);
    void keyPressed(int key);
private:
    GameState state;
    GameState queuedState;
    unsigned int wipeCounter;
    glm::vec2 mousePosition;
    Them them;
    bool rightMousePressed;
    /* Initialised in setup */
    piksel::Font font;
};

#endif /* GAME_HPP */