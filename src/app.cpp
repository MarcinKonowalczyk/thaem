#include "app.hpp"

#include "defines.hpp"
#include "colors.hpp"
#include "interval_transforms.hpp"

#include <iostream>

void App::setup() {
    int return_value = font.load("./data/Staatliches-Regular.ttf");
    them.position = glm::vec2(width/2, height/2);
}

void App::draw(piksel::Graphics& g) {

    // Draw current state
    switch (state) {
        case NONE: {
            std::cout << "oops... " << state << std::endl;
        } // 'break' is missing on purpose
        case START: {
            g.push();
            g.background(GREY);
            g.textFont(font);
            g.textSize(30);
            g.strokeWeight(0);
            g.fill(BLACK);
            g.text("Press (the mouse button) to start...", 10, height/2);
            g.pop();
        } break;
        case GAME: {
            g.background(glm::vec4(GREY_3, 0.9f));
            them.update(mousePosition, width, height);
            them.draw(g, mousePosition);
        } break;
        case RESTART: {
            // TODO
            exit(1);
        }
    }

    // Draw wipe
    if (wipeCounter > 0) {
        // Blend from 0 to 1 over the wipe duration
        float alpha = 1-(float)wipeCounter/WIPE_DURATION;
        
        g.push();
        g.fill(glm::vec4(0.0,0.0,0.0,0.9f));
        g.strokeWeight(0);
        g.rect(
            slowStart2(secondHalfHold(alpha))*width, 0,
            fastStart2(firstHalfHold(alpha))*width, height
        );
        g.pop();

        wipeCounter--; // dec the wipe counter

        // Switch to the queued state half way through the transition
        if ( wipeCounter < WIPE_DURATION/2 and queuedState != NONE ) {
            state = queuedState;
            queuedState = NONE;
        }
    }
}

void App::mouseMoved(int x, int y) {
    mousePosition.x = x;
    mousePosition.y = y;
}

void App::mousePressed(int button) {
    switch (state) {
        case START: {
            if (button == LEFT_MOUSE_BUTTON) {
                // Start a wipe and queue the next state
                wipeCounter = WIPE_DURATION;
                queuedState = GAME;
            }
        } break;
        case GAME: {
            if (button == LEFT_MOUSE_BUTTON) {
                them.jump();
            }
        } break;
        case RESTART: {
            // TODO
            exit(1);
        } break;
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