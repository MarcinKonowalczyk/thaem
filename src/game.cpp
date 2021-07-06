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
#include <algorithm>
#include <random>
#include <utility>

static auto rng = std::default_random_engine {};

std::vector<std::string> deathMessages = {
    "Sorry, you died",
    "Sucks to suck",
    "Maybe next time",
    "Dont get hit",
    "Try harder",
    "...",
    "Dont get hit",
    "My God, there's blood everywhere!",
    "YOU DIED",
    "shark",
};
std::string deathMessage = "#";

typedef std::pair<std::string,std::string> messagePair;
std::vector<messagePair> zenMessages = {
    messagePair("Mind is like a mad monkey - always in", "search for a typewriter to write Shakespeare on"),
    messagePair("To seek is to suffer", ""),
    messagePair("Rest and be kind", ""),
    messagePair("Gently fold the whites", "making sure not to deflate them"),
    messagePair("Do not seek the truth", "truth is a lie"),
    messagePair("You're walking in the woods", "There's no one around and your phone is dead"),
    messagePair("Life is a balance of holding on and letting go", "Unless you're a mountain climber"),
    messagePair("Electricity is power", ""),
    messagePair("If I didn't have you", "someone else would do"),
    messagePair("God is dead", "Long live god")
};
messagePair zenMessage = messagePair("#","#");

int endlessCounter = 7;

void Game::setup() {
    // TODO: nothing to do here for now, but fix the font hack in the future
    std::string staatliches_regular_decoded = base64_decode(staatliches_regular_encoded);
    font._load((const unsigned char *)staatliches_regular_decoded.c_str());
}

void Game::draw(piksel::Graphics& g) {
    g.background(glm::vec4(GREY_3, 0.9f));
    g.textFont(font);

    // Update pops if in a level (and if any exist)
    switch (state) { LEVELS_SWITCH
        updatePops(pops, width, height);
    }

    // Update them when in a level
    switch (state) { LEVELS_SWITCH
        them.update(mousePosition, width, height, rightMousePressed, blueBullets, redBullets, blackBullets, pops, score);
        if (them.dead and !deathScreen) {
            deathMessage = *select_randomly(deathMessages.begin(), deathMessages.end(), rng);
            deathScreen = true;
        }
    }

    // Draw screens between levels
    std::string levelText = "###";
    std::string flavourText1 = "###";
    std::string flavourText2 = "###";

    switch (state) {
        case START: {
            g.push();
            g.strokeWeight(0);
            g.textSize(50);
            // g.text("THAEM", 10, height/2-20);
            g.fill(BLACK);
            g.text("TH", 10, height/2-20);
            g.fill(glm::mix(LINES_B,BLACK,0.2));
            g.text("A", 53.5, height/2-20);
            g.fill(glm::mix(LINES_R,BLACK,0.2));
            g.text("E", 75, height/2-20);
            g.fill(BLACK);
            g.text("M", 95.5, height/2-20);
            g.textSize(30);
            g.fill(glm::vec4(BLACK_3,0.3f));
            g.text("Click to start...", 10, height/2+15);
            g.pop();
        } break;
        case INTERVAL_1: {
            levelText = "Level 2";
            flavourText1 = "You might want to try the";
            flavourText2 = "other mouse button too";
        } break;
        case INTERVAL_2: {
            levelText = "Level 3";
            flavourText1 = "Some enemies hit";
            flavourText2 = "harder than others";
        } break;
        case INTERVAL_3: {
            levelText = "Level 4";
            flavourText1 = "Done with";
            flavourText2 = "the warmup?";
        } break;
        case INTERVAL_4: {
            levelText = "Level 5";
            flavourText1 = "Touchpad is";
            flavourText2 = "not reccomended";
        } break;
        case INTERVAL_5: {
            levelText = "Level 6";
            flavourText1 = "It's not about";
            flavourText2 = "the destination ...";
        } break;
        case INTERVAL_6: {
            levelText = "Level 7";
            flavourText1 = "... but about";
            flavourText2 = "the journey";
        } break;
        case ENDLESS_INTERVAL: {
            levelText = "Level " + std::to_string(endlessCounter);
            flavourText1 = zenMessage.first;
            flavourText2 = zenMessage.second;
        }
    }

    switch (state) { INTERVALS_SWITCH
            g.push();
            g.textSize(30);
            g.strokeWeight(0);
            g.fill(BLACK);
            g.text(levelText, 10, height/2-15);
            g.fill(glm::vec4(BLACK_3,0.3f));
            g.textSize(30);
            g.text(flavourText1, 10, height/2+15);
            g.text(flavourText2, 10, height/2+30+15);
            g.pop();
    }

    // Level states
    bool hasBlueBullets = false;
    bool hasRedBullets = false;
    bool hasBlackBullets = false;
    int spawnInterval = LEVEL1_SPAWN_INTERVAL;
    int scoreRequirement = LEVEL1_SCORE_REQUIREMENT;
    GameState nextState = START;
    int blueBulletLimit = BULLET_LIMIT;
    int redBulletLimit = BULLET_LIMIT;
    int blackBulletLimit  = BULLET_LIMIT;
    float blueDragMultiplier = 1.0f;
    float redDragMultiplier = 1.0f;

    switch (state) {
        case LEVEL_1: {
            spawnInterval = LEVEL1_SPAWN_INTERVAL;
            hasBlueBullets = true;
            scoreRequirement = LEVEL1_SCORE_REQUIREMENT;
            nextState = INTERVAL_1;
        } break;
        case LEVEL_2: {
            spawnInterval = LEVEL2_SPAWN_INTERVAL;
            hasBlueBullets = true;
            scoreRequirement = LEVEL2_SCORE_REQUIREMENT;
            nextState = INTERVAL_2;
        } break;
        case LEVEL_3: {
            spawnInterval = LEVEL3_SPAWN_INTERVAL;
            hasRedBullets = true;
            scoreRequirement = LEVEL3_SCORE_REQUIREMENT;
            nextState = INTERVAL_3;
        } break;
        case LEVEL_4: {
            spawnInterval = LEVEL4_SPAWN_INTERVAL;
            hasBlueBullets = true;
            hasRedBullets = true;
            redBulletLimit = LEVEL4_RED_LIMIT;
            scoreRequirement = LEVEL4_SCORE_REQUIREMENT;
            nextState = INTERVAL_4;
        } break;
        case LEVEL_5: {
            spawnInterval = LEVEL5_SPAWN_INTERVAL;
            hasBlueBullets = true;
            hasRedBullets = true;
            blueBulletLimit = LEVEL5_BLUE_LIMIT;
            redBulletLimit = LEVEL5_RED_LIMIT;
            blueDragMultiplier = LEVEL5_DRAG_MULTIPLIER;
            redDragMultiplier = LEVEL5_DRAG_MULTIPLIER;
            scoreRequirement = LEVEL5_SCORE_REQUIREMENT;
            nextState = INTERVAL_5;
        } break;
        case LEVEL_6: {
            spawnInterval = LEVEL6_SPAWN_INTERVAL;
            hasBlueBullets = true;
            hasBlackBullets = true;
            // blueBulletLimit = LEVEL5_BLUE_LIMIT;
            // redBulletLimit = LEVEL5_RED_LIMIT;
            scoreRequirement = LEVEL6_SCORE_REQUIREMENT;
            nextState = INTERVAL_6;
        } break;
        case ENDLESS: {
            hasBlueBullets = true;
            hasRedBullets = true;
            hasBlackBullets = true;
            float alpha = glm::min(20.0, (float)endlessCounter-8.0)/20.0;
            spawnInterval = ENDLESS_SPAWN_INTERVAL - slowStart4(alpha)*15;
            blueBulletLimit = ENDLESS_BLUE_LIMIT + slowStart2(alpha)*5;
            redBulletLimit = ENDLESS_RED_LIMIT + fastStart2(secondHalf(alpha))*5;
            blackBulletLimit = ENDLESS_RED_LIMIT + backAndForth(alpha)*5;
            scoreRequirement = ENDLESS_SCORE_REQUIREMENT + alpha*200;
            nextState = ENDLESS_INTERVAL;
        } break;
    }

    // Spawn bullets
    switch (state) { LEVELS_SWITCH
        if (spawnCounter == 0) { // Spawn new bullets
        // Spawn randomly, retry if failed with the other color
            if (hasBlueBullets and hasRedBullets and hasBlackBullets) {
                float choice = glm::linearRand(0.0, 1.0);
                bool success;
                if (choice < 0.33) {
                    success = spawnBullet(T_BLUE, blueBullets, width, height, blueBulletLimit);
                    if (!success) { success = spawnBullet(T_RED, redBullets, width, height, redBulletLimit); }
                    if (!success) { success = spawnBullet(T_BLACK, blackBullets, width, height, blackBulletLimit); }
                } else if (choice < 0.66) {
                    success = spawnBullet(T_RED, redBullets, width, height, redBulletLimit);
                    if (!success) { success = spawnBullet(T_BLACK, blackBullets, width, height, blackBulletLimit); }
                    if (!success) { success = spawnBullet(T_BLUE, blueBullets, width, height, blueBulletLimit); }
                } else {
                    success = spawnBullet(T_BLACK, blackBullets, width, height, blackBulletLimit);
                    if (!success) { success = spawnBullet(T_BLUE, blueBullets, width, height, blueBulletLimit); }
                    if (!success) { success = spawnBullet(T_RED, redBullets, width, height, redBulletLimit); }
                }
                if (success) { spawnCounter = spawnInterval; }
            } else if (hasBlueBullets and hasRedBullets) {
                float choice = glm::linearRand(0.0, 1.0);
                bool success;
                if (choice < 0.5) {
                    success = spawnBullet(T_BLUE, blueBullets, width, height, blueBulletLimit);
                    if (!success) { success = spawnBullet(T_RED, redBullets, width, height, redBulletLimit); }
                } else {
                    success = spawnBullet(T_RED, redBullets, width, height, redBulletLimit);
                    if (!success) { success = spawnBullet(T_BLUE, blueBullets, width, height, blueBulletLimit); }
                }
                if (success) { spawnCounter = spawnInterval; }
            } else if (hasBlueBullets and hasBlackBullets) {
                float choice = glm::linearRand(0.0, 1.0);
                bool success;
                if (choice < 0.5) {
                    success = spawnBullet(T_BLUE, blueBullets, width, height, blueBulletLimit);
                    if (!success) { success = spawnBullet(T_BLACK, blackBullets, width, height, blackBulletLimit); }
                } else {
                    success = spawnBullet(T_BLACK, blackBullets, width, height, blackBulletLimit);
                    if (!success) { success = spawnBullet(T_BLUE, blueBullets, width, height, blueBulletLimit); }
                }
                if (success) { spawnCounter = spawnInterval; }
            } else if (hasBlueBullets) {
                if (spawnBullet(T_BLUE, blueBullets, width, height, blueBulletLimit)) { spawnCounter = spawnInterval; }
            } else if (hasRedBullets) {
                if (spawnBullet(T_RED, redBullets, width, height, redBulletLimit)) { spawnCounter = spawnInterval; }
            }
        } else if ( spawnCounter > 0 ) {
            spawnCounter--;
        };

        // Handle winning a level
        if (score >= scoreRequirement and wipeCounter == 0 and !them.dead) {
            wipeCounter = WIPE_DURATION;
            queuedState = nextState;
        }
    }

    // Draw pops
    switch (state) {LEVELS_SWITCH
        for (Pop& pop : pops) {
            pop.draw(g);
        }
    }

    // Update and draw bullets
    if (hasBlueBullets) {
        if (!blueBullets.empty()) {
            for (Bullet& bullet : blueBullets) { bullet.update(mousePosition, width, height, rightMousePressed, blueBullets, redBullets, blackBullets, them.position, blueDragMultiplier, redDragMultiplier); }
            for (Bullet& bullet : blueBullets) { bullet.draw(g, rightMousePressed, mousePosition, them.position, blueBullets, redBullets, them.dead); }
        }
    }
    if (hasRedBullets) {
        if (!redBullets.empty()) { // Update and draw bullets
            for (Bullet& bullet : redBullets) { bullet.update(mousePosition, width, height, rightMousePressed, blueBullets, redBullets, blackBullets, them.position, blueDragMultiplier, redDragMultiplier); }
            for (Bullet& bullet : redBullets) { bullet.draw(g, rightMousePressed, mousePosition, them.position, blueBullets, redBullets, them.dead); }
        }
    }
    if (hasBlackBullets) {
        if (!blackBullets.empty()) { // Update and draw bullets
            for (Bullet& bullet : blackBullets) { bullet.update(mousePosition, width, height, rightMousePressed, blueBullets, redBullets, blackBullets, them.position, blueDragMultiplier, redDragMultiplier); }
            for (Bullet& bullet : blackBullets) { bullet.draw(g, rightMousePressed, mousePosition, them.position, blueBullets, redBullets, them.dead); }
        }
    }

    // Draw the them
    switch (state) { LEVELS_SWITCH
        them.draw(g, mousePosition, rightMousePressed);
    }

    // Print score if in a level
    switch (state) { LEVELS_SWITCH
            g.push();
            g.textSize(25);
            g.strokeWeight(0);
            g.fill(glm::vec4(BLACK_3,0.1));
            g.text(getScoreString(score) + " / " + getScoreString(scoreRequirement), 10, 28);
            g.pop();
    }

    // Draw death screen
    if (deathScreen) {
        g.push();
        g.strokeWeight(0);
        g.fill(glm::vec4(BLACK_3,0.3f));
        g.rect(0,0,width, height);
        g.textSize(30);
        g.strokeWeight(0);
        if (deathMessage == "YOU DIED") {
            g.fill(LINES_X);
        } else {
            g.fill(glm::vec4(BLACK_3,0.9));
        }
        g.text(deathMessage, 10, height/2-15);
        g.fill(glm::vec4(BLACK_3,0.9));
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
            if (queuedState == ENDLESS) {
                zenMessage = *select_randomly(zenMessages.begin(), zenMessages.end(), rng);
                if (state != ENDLESS) {
                    endlessCounter++;
                }
            }
            state = queuedState;
            queuedState = NONE;
            switch (state) {
                LEVELS_SWITCH {
                    setupCleanLevel();
                } break;
            }
        }
    }

    // Vector shuffle
    if (vectorShuffleCounter <= 0) {
        shuffleBulletVectors();
        vectorShuffleCounter = BULLET_VECTOR_SHUFFLE_INTERVAL;
    } else {
        vectorShuffleCounter--;
    }
}

void Game::mouseMoved(int x, int y) {
    mousePosition.x = x;
    mousePosition.y = y;
}

void Game::mousePressed(int button) {
    switch (state) { LEVELS_SWITCH
        if (button == RIGHT_MOUSE_BUTTON ) {
            rightMousePressed = true;
        } else if (button == LEFT_MOUSE_BUTTON) {
            them.addLink(mousePosition, score);
        }
    }

    if (button == LEFT_MOUSE_BUTTON) {
        switch (state) {
            case START: { wipeTo(LEVEL_1); } break;
            LEVELS_SWITCH { if (deathScreen) { wipeTo(state); } } break;
            case INTERVAL_1: { wipeTo(LEVEL_2); } break;
            case INTERVAL_2: { wipeTo(LEVEL_3); } break;
            case INTERVAL_3: { wipeTo(LEVEL_4); } break;
            case INTERVAL_4: { wipeTo(LEVEL_5); } break;
            case INTERVAL_5: { wipeTo(LEVEL_6); } break;
            case INTERVAL_6: { wipeTo(ENDLESS); } break;
            case ENDLESS_INTERVAL: {  wipeTo(ENDLESS); } break;
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

std::string Game::getScoreString(int scoreIn) {
    std::string scoreString = "";
    if (scoreIn <= 999) { scoreString += "0"; }
    if (scoreIn <= 99) { scoreString += "0"; }
    if (scoreIn <= 9) { scoreString += "0"; }
    scoreString += std::to_string(scoreIn);
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
    pops = std::vector<Pop>(0);
    them.links = std::vector<Link>(0);
}

void Game::wipeTo(GameState state) {
    wipeCounter = WIPE_DURATION;
    queuedState = state;
}

void Game::shuffleBulletVectors() {
    if (!blueBullets.empty()) {
        std::shuffle( blueBullets.begin(), blueBullets.end(), rng);
    }
    if (!redBullets.empty()) {
        std::shuffle( redBullets.begin(), redBullets.end(), rng);
    }
}