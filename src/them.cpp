// #include <glm/glm.hpp>

#include "them.hpp"
#include "defines.hpp"
#include "colors.hpp"
#include "interval_transforms.hpp"

#include <iostream>


void DEBUB_printVec2(glm::vec2 vec2) {
    std::cout << vec2.x << " " << vec2.y << std::endl;
}

void Them::update(glm::vec2 mousePosition, float width, float height) {
    glm::vec2 mouseVector = mousePosition - position;
    float mouseDistance = glm::length(mouseVector);
    if (mouseDistance < THEM_RADIUS ) {
        velocity = 0.9f*velocity + 0.1f*(0.01f*mouseVector);
    } else {
        glm::vec2 acceleration = glm::vec2(0,0);
        glm::vec2 mouseNormal = mouseVector / mouseDistance;
        float alpha = mouseDistance > MAX_MOUSE_DISTANCE ? 1.0 : mouseDistance/MAX_MOUSE_DISTANCE;
        acceleration += ACCELERATION_COEFFICIENT * alpha * mouseNormal;
        velocity += acceleration;
    }

    // Push back towards the play area
    if (position.x > width)  { velocity += glm::vec2(-1.0, 0.0); }
    else if (position.x < 0) { velocity += glm::vec2(+1.0, 0.0); }
    if (position.y > height) { velocity += glm::vec2(0.0, -1.0); }
    else if (position.y < 0) { velocity += glm::vec2(0.0, 1.0);  }


    // On jump change velocity rapidly
    if (queuedJump and jumpCounter == 0) {
        jumpCounter = JUMP_DURATION;
        queuedJump = false;
    }
    if (jumpCounter > 0) {
        if (jumpCounter == JUMP_DURATION) { // Just jumped
            if (mouseDistance > 0) {
                glm::vec2 mouseNormal = mouseVector / mouseDistance;
                // velocity = mouseNormal * glm::abs(glm::dot(velocity, mouseNormal));
                velocity = mouseNormal * (glm::length(velocity) + 4.0f);
            }
        }
        jumpCounter--;
    }

    // Handle drag at the very end
    float velocityMagnitude = glm::length(velocity);
    if (velocityMagnitude > 0) {
        glm::vec2 velocityNormal = velocity / velocityMagnitude;
        float dragMagnitude = 0.01 * velocityMagnitude * velocityMagnitude;
        if (mouseDistance < 40) {
            dragMagnitude *= 10;
        }
        velocity -= dragMagnitude * velocityNormal;
    }

    position += velocity;
};

void Them::draw(piksel::Graphics& g, glm::vec2 mousePosition) {
    g.push();

    g.strokeWeight(2);
    g.line(position.x, position.y, mousePosition.x, mousePosition.y);

    g.rectMode(piksel::DrawMode::CENTER);

    int themSize = 2*THEM_RADIUS;
    if (jumpCounter > 0) {
        float alpha = 1 - (float)jumpCounter/JUMP_DURATION;
        alpha = fastStart2(firstHalf(alpha)) + slowStart3(secondHalfBackwards(alpha));
        themSize += 2*THEM_RADIUS*alpha;

        int shadowSize = themSize + 2*THEM_RADIUS*alpha;
        float yOffset = fastStart2(alpha)*4;
        float xOffset = fastStart2(alpha)*2;
        g.strokeWeight(0);
        g.fill(glm::vec4(BLACK_3,0.1f));
        g.ellipse(position.x+xOffset, position.y+yOffset, shadowSize, shadowSize);
    }

    g.strokeWeight(2);
    g.stroke(BLACK);
    g.fill(WHITE);
    g.ellipse(position.x, position.y, themSize, themSize);

    // Draw velocity arrow
    g.strokeWeight(1);
    float velocityMagnitude = glm::length(velocity);
    if (velocityMagnitude > 0) {
        glm::vec2 velocityNormal = velocity / velocityMagnitude;
        glm::vec2 velocityOrthogonal = glm::vec2(velocityNormal.y, -velocityNormal.x);
        glm::vec2 velocityIndicator = velocityNormal * 50.0f;
        g.line(position.x, position.y,
            position.x + velocityIndicator.x,
            position.y + velocityIndicator.y);
    }

    g.pop();
};

void Them::jump() {
    if (jumpCounter == 0) {
        jumpCounter = JUMP_DURATION;
    } else { // Already in a jump
        queuedJump = true;
    }
}