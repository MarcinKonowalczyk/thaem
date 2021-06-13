#include "game.hpp"
#include "defines.hpp"
#include "colors.hpp"
#include "interval_transforms.hpp"
#include "Staatliches-Regular.hpp"

#include <glm/glm.hpp>
#include <glm/gtc/random.hpp>
#include <cpp-base64/base64.h>

#include <iostream>
#include <string> 

void Game::setup() {
    // std::string staatliches_regular_decoded = base64_decode(staatliches_regular_encoded);
    // font = piksel::Font();
    // font._load((const unsigned char*) staatliches_regular_decoded.c_str());
}

void Game::draw(piksel::Graphics& g) {
    g.background(glm::vec4(GREY_3, 0.9f));
    // Draw current state
    switch (state) {
        case NONE: {
            std::cout << "oops... " << state << std::endl;
        } // 'break' is missing on purpose
        case START: {
            g.push();
            // g.textFont(font);
            g.strokeWeight(0);
            g.fill(BLACK);
            g.textSize(50);
            g.text(GAME_NAME, 10, height/2-20);
            g.textSize(30);
            g.fill(glm::vec4(BLACK_3,0.3f));
            g.text("Click to start...", 10, height/2+15);
            g.pop();
        } break;
        case LEVEL_1: {
            them.update(mousePosition, width, height, rightMousePressed, blueBullets, redBullets, blackBullets, score);
            if (them.dead) { deathScreen = true; }
            
            // Spawn new bullets
            int bulletOffset = 10;
            if (spawnCounter == 0) {
                if (spawnBlueBullet(blueBullets, width, height)) { spawnCounter = LEVEL1_SPAWN_INTERVAL; }
            } else if ( spawnCounter > 0 ) {
                spawnCounter--;
            };

            // Update and draw bullets
            if (!blueBullets.empty()) {
                for (Bullet& bullet : blueBullets) { bullet.update(mousePosition, width, height, rightMousePressed, blueBullets); }
                for (Bullet& bullet : blueBullets) { bullet.draw(g, rightMousePressed, mousePosition, them.dead); }
            }

            them.draw(g, mousePosition, rightMousePressed);

            if (score >= LEVEL1_SCORE_REQUIREMENT and wipeCounter == 0 and !them.dead) {
                wipeCounter = WIPE_DURATION;
                queuedState = INTERVAL_1;
            }
        } break;
        case INTERVAL_1: {
            g.push();
            // g.textFont(font);
            g.textSize(30);
            g.strokeWeight(0);
            g.fill(BLACK);
            g.text("Level 2", 10, height/2-15);
            g.fill(glm::vec4(BLACK_3,0.3f));
            g.textSize(30);
            g.text("You might wan to try the", 10, height/2+15);
            g.text("other mouse button too", 10, height/2+30+15);
            g.pop();
        } break;
        case LEVEL_2: {
            them.update(mousePosition, width, height, rightMousePressed, blueBullets, redBullets, blackBullets, score);
            if (them.dead) { deathScreen = true; }
            
            // Spawn new bullets
            int bulletOffset = 10;
            if (spawnCounter == 0) {
                if (spawnBlueBullet(blueBullets, width, height)) { spawnCounter = LEVEL2_SPAWN_INTERVAL; }
            } else if ( spawnCounter > 0 ) {
                spawnCounter--;
            };

            // Update and draw bullets
            if (!blueBullets.empty()) {
                for (Bullet& bullet : blueBullets) { bullet.update(mousePosition, width, height, rightMousePressed, blueBullets); }
                for (Bullet& bullet : blueBullets) { bullet.draw(g, rightMousePressed, mousePosition, them.dead); }
            }
            
            them.draw(g, mousePosition, rightMousePressed);

            if (score >= LEVEL2_SCORE_REQUIREMENT and wipeCounter == 0 and !them.dead) {
                wipeCounter = WIPE_DURATION;
                queuedState = INTERVAL_2;
            }
        } break;
        case INTERVAL_2: {
            g.push();
            // g.textFont(font);
            g.textSize(30);
            g.strokeWeight(0);
            g.fill(BLACK);
            g.text("Level 3", 10, height/2-15);
            g.fill(glm::vec4(BLACK_3,0.3f));
            g.textSize(30);
            g.text("...", 10, height/2+15);
            g.pop();
        } break;
    }

    // Print score if in a level
    switch (state) {
        case LEVEL_1:
        case LEVEL_2: {
            g.push();
            // g.textFont(font);
            g.textSize(30);
            g.strokeWeight(0);
            g.fill(glm::vec4(BLACK_3,0.1));
            g.text(getScoreString(), 8, 30);
            g.pop();
        }
        default:;
    }

    // Draw death screen
    if (deathScreen) {
        g.push();
        g.strokeWeight(0);
        g.fill(glm::vec4(BLACK_3,0.3f));
        g.rect(0,0,width, height);
        // g.textFont(font);
        g.textSize(30);
        g.strokeWeight(0);
        g.fill(BLACK);
        g.text("Sorry, you died", 10, height/2-15);
        g.text("Click to try again", 10, height/2+15);
        g.pop();
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
            switch (state) {
                case LEVEL_1:
                case LEVEL_2:
                case LEVEL_3: {
                    setupCleanLevel();
                } break;
            }
        }
    }
}

void Game::mouseMoved(int x, int y) {
    mousePosition.x = x;
    mousePosition.y = y;
}

void Game::mousePressed(int button) {
    switch (state) {
        case LEVEL_3:
        case LEVEL_2: {
            if (button == RIGHT_MOUSE_BUTTON ) {
                rightMousePressed = true;
            }
        } // nobreak
        case LEVEL_1: { // Enable the right mouse button only after 1st level
            if (button == LEFT_MOUSE_BUTTON) {
                them.addLink(mousePosition);
            }
        } break;
    }

    if (button == LEFT_MOUSE_BUTTON) {
        switch (state) {
            case START: {
                wipeTo(LEVEL_1);
            } break;
            case LEVEL_1: { if (deathScreen) { wipeTo(LEVEL_1); } } break;
            case INTERVAL_1: { wipeTo(LEVEL_2); } break;
            case LEVEL_2: { if (deathScreen) { wipeTo(LEVEL_2); } } break;
            case INTERVAL_2: { wipeTo(LEVEL_3); } break;
            case LEVEL_3: { if (deathScreen) { wipeTo(LEVEL_3); } } break;
        }
    }
}

void Game::mouseReleased(int button) {
    if (button == RIGHT_MOUSE_BUTTON) {
        rightMousePressed = false;
    }
}

void Game::keyPressed(int key) {
#ifndef __EMSCRIPTEN__
    if (key == 256) {
        exit(0);
    }
    std::cout << key << std::endl;
#endif /* __EMSCRIPTEN__ */
}

std::string Game::getScoreString() {
    std::string scoreString = "";
    if (score <= 999) { scoreString += "0"; }
    if (score <= 99) { scoreString += "0"; }
    if (score <= 9) { scoreString += "0"; }
    scoreString += std::to_string(score);
    return scoreString;
}

void Game::setupCleanLevel() {
    them.dead = false;
    them.position = glm::vec2(width/2,height/2);
    deathScreen = false;
    score = 0;
    blueBullets = std::vector<Bullet>(0);
    redBullets = std::vector<Bullet>(0);
    blackBullets = std::vector<Bullet>(0);
    them.links = std::vector<Link>(0);
}

void Game::wipeTo(GameState state) {
    wipeCounter = WIPE_DURATION;
    queuedState = state;
}