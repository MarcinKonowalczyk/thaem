#ifndef APP_HPP
#define APP_HPP

#include <piksel/baseapp.hpp>
#include "them.hpp"

enum AppState {
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

class App : public piksel::BaseApp {
public:
    App() : piksel::BaseApp(WIDTH, HEIGHT, NAME)
        , state(START)
        , queuedState(NONE)
        , wipeCounter(0)
        , mousePosition(glm::vec2(WIDTH, HEIGHT))
        , them(Them())
        {}
    void setup();
    void draw(piksel::Graphics& g);
    void mouseMoved(int x, int y);
    void mousePressed(int button);
    void keyPressed(int key);
private:
    AppState state;
    AppState queuedState;
    unsigned int wipeCounter;
    glm::vec2 mousePosition;
    Them them;
    /* Initialised in setup */
    piksel::Font font;
};

#endif /* APP_HPP */