#ifndef APP_HPP
#define APP_HPP

#include <piksel/baseapp.hpp>

enum AppState {
    NONE = 0,
    START,
    WIPE,
    GAME,
    RESTART,
};

#define LEFT_MOUSE_BUTTON 0
#define RIGHT_MOUSE_BUTTON 1

#define WIDTH 640
#define HEIGHT 480
#define NAME "untitled gamejam project"

class App : public piksel::BaseApp {
public:
    App() : piksel::BaseApp(WIDTH, HEIGHT, NAME)
        , state(START)
        , queuedState(NONE)
        , mousePosition(glm::vec2(WIDTH, HEIGHT)) {}
    void setup();
    void draw(piksel::Graphics& g);
    void mouseMoved(int x, int y);
    void mousePressed(int button);
    void keyPressed(int key);
private:
    AppState state;
    AppState queuedState;
    glm::vec2 mousePosition;
    piksel::Font font;
};
#endif /* APP_HPP */