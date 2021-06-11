#include "app.hpp"
#include "defines.hpp"

#include <iostream>

#define WHITE glm::vec4(1.0f, 1.0f, 1.0f, 1.0f)
#define GREY glm::vec4(0.5f, 0.5f, 0.5f, 1.0f)
#define BLACK glm::vec4(0.0f, 0.0f, 0.0f, 1.0f)

void App::setup() {
    int return_value = font.load("./data/Staatliches-Regular.ttf");
    std::cout << return_value << std::endl;
}

void App::draw(piksel::Graphics& g) {
    static uint wipeCounter = 0;
    switch (state) {
        case START: {
            g.push();
            g.background(GREY);
            g.textFont(font);
            g.textSize(30);
            g.strokeWeight(0);
            g.fill(BLACK);
            g.text("Hello", 10, height/2);
            g.pop();
        } break;
        case GAME: {
            g.push();
            g.background(glm::vec4(0.5f, 0.5f, 0.5f, 0.9f));
            g.rect(mousePosition.x, mousePosition.y, 100, 100);
            g.pop();
        } break;
        case WIPE: {
            if (wipeCounter == 0) {
                wipeCounter = WIPE_DURATION + 1;
            }
            
            // Draw the wipe
            float alpha = 1-(float)wipeCounter/WIPE_DURATION;
            g.push();
            g.fill(BLACK);
            g.strokeWeight(0);
            g.rect(0,0,alpha*width,height);
            g.pop();
            wipeCounter--; // dec the wipe counter
            if (wipeCounter == 0) { // Switch to the queued state
                state = queuedState;
                queuedState = NONE;
            }
        } break;
    }
}

void App::mouseMoved(int x, int y) {
    mousePosition.x = x;
    mousePosition.y = y;
}

void App::mousePressed(int button) {
    if (state == START) {
        if (button ==LEFT_MOUSE_BUTTON) {
            state = WIPE;
            queuedState = GAME;
        }
    }
}

void App::keyPressed(int key) {
    if (key == 256) {
        #ifndef __EMSCRIPTEN__
        exit(0);
        #endif /* __EMSCRIPTEN__ */
    }
    std::cout << key << std::endl;
}