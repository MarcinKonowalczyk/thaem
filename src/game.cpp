#include "game.hpp"
#include "defines.hpp"
#include "colors.hpp"
#include "interval_transforms.hpp"

#include <glm/glm.hpp>
#include <glm/gtc/random.hpp>

#include <iostream>
#include <string> 

void Game::setup() {
    int return_value = font.load("./data/Staatliches-Regular.ttf");
    // them.setPosition(width/2, height/2);
}

void Game::draw(piksel::Graphics& g) {

    // Draw current state
    switch (state) {
        case NONE: {
            std::cout << "oops... " << state << std::endl;
        } // 'break' is missing on purpose
        case START: {
            g.push();
            g.background(GREY);
            g.textFont(font);
            g.strokeWeight(0);
            g.fill(BLACK);
            g.textSize(50);
            g.text("THAEM", 10, height/2-20);
            g.textSize(30);
            g.fill(glm::vec4(BLACK_3,0.3f));
            g.text("Click to start...", 10, height/2+15);
            g.pop();
        } break;
        case LEVEL_1: {
            g.background(glm::vec4(GREY_3, 0.9f));
            them.update(mousePosition, width, height, rightMousePressed, blueBullets, redBullets, blackBullets, score);
            if (them.dead) { deathScreen = true; }
            
            // Spawn new bullets
            int bulletOffset = 10;
            if (spawnCounter == 0 and blueBullets.size() < BULLET_LIMIT) {
                spawnCounter = LEVEL1_SPAWN_INTERVAL;
                float choice = glm::linearRand(0.0, 1.0);
                Bullet newBullet = Bullet();
                newBullet.type = T_BLUE;
                if (choice < 0.25) { // Left
                    float bulletHeight = glm::linearRand(0.0f - bulletOffset, (float)height - bulletOffset);
                    newBullet.position = glm::vec2(-bulletOffset, bulletHeight);
                    newBullet.velocity = glm::vec2(1.0, 0.0);
                } else if (choice < 0.5) { // Top
                    float bulletWidth = glm::linearRand(0.0f - bulletOffset, (float)width - bulletOffset);
                    newBullet.position = glm::vec2(bulletWidth, -bulletOffset);
                    newBullet.velocity = glm::vec2(0.0, 1.0);
                } else if (choice < 0.75) { // Right
                    float bulletHeight = glm::linearRand(0.0f + bulletOffset, (float)height - bulletOffset);
                    newBullet.position = glm::vec2(width + bulletOffset, bulletHeight);
                    newBullet.velocity = glm::vec2(-1.0, 0.0);
                } else { // Bottom
                    float bulletWidth = glm::linearRand(0.0f + bulletOffset, (float)width - bulletOffset);
                    newBullet.position = glm::vec2(bulletWidth, height + bulletOffset);
                    newBullet.velocity = glm::vec2(0.0, -1.0);
                }
                blueBullets.push_back(newBullet);
            }
            spawnCounter--;

            // Update and draw bullets
            if (!blueBullets.empty()) {
                for (Bullet& bullet : blueBullets) { bullet.update(mousePosition, width, height, rightMousePressed, blueBullets); }
                for (Bullet& bullet : blueBullets) { bullet.draw(g, rightMousePressed, mousePosition, them.dead); }
            }

            them.draw(g, mousePosition, rightMousePressed);
        } break;
        case INTERVAL_1: {
            g.push();
            g.background(GREY);
            g.textFont(font);
            g.textSize(30);
            g.strokeWeight(0);
            g.fill(BLACK);
            // g.text("THAEM", 10, height/2-15);
            g.text("Click to start...", 10, height/2+15);
            g.pop();
        } break;
        case LEVEL_2: {

        } break;
    }

    // Print score if in a level
    switch (state) {
        case LEVEL_1:
        case LEVEL_2: {
            g.push();
            g.textFont(font);
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
        g.textFont(font);
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
            if (state == LEVEL_1 or state == LEVEL_2) {
                setupCleanLevel();
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
        case START: {
            if (button == LEFT_MOUSE_BUTTON) {
                // Start a wipe and queue the next state
                wipeCounter = WIPE_DURATION;
                queuedState = LEVEL_1;
            }
        } break;
        case LEVEL_1: {
            if (button == LEFT_MOUSE_BUTTON) {
                them.addLink(mousePosition);
            } else if (button == RIGHT_MOUSE_BUTTON ) {
                rightMousePressed = true;
            }
            if (deathScreen and button == LEFT_MOUSE_BUTTON) {
                wipeCounter = WIPE_DURATION;
                queuedState = LEVEL_1;
            }
        } break;
    }
}

void Game::mouseReleased(int button) {
    if (state == LEVEL_1 and button == RIGHT_MOUSE_BUTTON) {
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