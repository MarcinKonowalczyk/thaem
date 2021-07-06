#ifndef GAME_HPP
#define GAME_HPP

// Whether to save frames
#ifndef __EMSCRIPTEN__
// #define SAVE_FRAMES
#endif /* __EMSCRIPTEN__ */

#include <piksel/baseapp.hpp>
#include "them.hpp"
#include "bullet.hpp"
#include "pop.hpp"

#include <vector>
#include <string>
#include <random>
#include <iterator>
#include <iostream>

#ifdef SAVE_FRAMES
#include <fstream>
#include <GLFW/glfw3.h>
#endif

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

#ifdef SAVE_FRAMES
#define WIDTH 400
#define HEIGHT 400
#else
#define WIDTH 960 // 640
#define HEIGHT 540 // 480
#endif /* SAVE_FRAMES  */

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
        , pops(std::vector<Pop>(0))
        , deathScreen(false)
        , vectorShuffleCounter(0)
        , frame_counter(0)
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
    unsigned int frame_counter;
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
    std::vector<Pop> pops;
    /* Initialised in setup */
    piksel::Font font;
    unsigned int score;
    bool deathScreen;
#ifdef SAVE_FRAMES
    void saveFrame(
    const int epoch_counter,
    unsigned int width, unsigned int height);
#endif /* SAVE_FRAMES */
};

// https://stackoverflow.com/a/16421677/2531987
template<typename Iter, typename RandomGenerator>
Iter select_randomly(Iter start, Iter end, RandomGenerator& g) {
    std::uniform_int_distribution<> dis(0, std::distance(start, end) - 1);
    std::advance(start, dis(g));
    return start;
}

#ifdef SAVE_FRAMES
// Save frames as portable pixel map
// http://paulbourke.net/dataformats/ppm/
inline void Game::saveFrame(const int epoch_counter,
    unsigned int width, unsigned int height) {

    // Construct filename
    std::string epoch_string = "";
    if (epoch_counter <= 9999) {epoch_string += "0";};
    if (epoch_counter <= 999) {epoch_string += "0";};
    if (epoch_counter <= 99) {epoch_string += "0";};
    if (epoch_counter <= 9) {epoch_string += "0";};
    epoch_string += std::to_string(epoch_counter);
    std::string filename = "./frames/" + epoch_string + ".png";

    size_t i, j, cur;
    const size_t format_nchannels = 3;

    std::ofstream fout;
    fout.open(filename.c_str(), std::ios::binary | std::ios::out);
    
    char header[1024];
    size_t header_size = snprintf(header, sizeof(header), "P6\n%d %d\n%d\n", width, height, 255);
    fout.write(header, header_size);
    
    size_t pixels_s = format_nchannels * sizeof(unsigned char) * width * height;
    auto pixels = (unsigned char*) malloc(pixels_s);
    glReadPixels(0, 0, width, height, GL_RGB, GL_UNSIGNED_BYTE, pixels);
    fout.write((char*) pixels, pixels_s);
    fout.flush();
    fout.close();
    free(pixels);
}
#endif /* SAVE_FRAMES */

#endif /* GAME_HPP */