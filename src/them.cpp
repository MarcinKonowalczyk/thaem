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
    glm::vec2 acceleration = glm::vec2(0.0, 0.0);

    glm::vec2 mouseVector = mousePosition - position;
    float mouseDistance = glm::length(mouseVector);
    if (mouseDistance > 0) {
        if (mouseDistance > 10) {
            glm::vec2 mouseNormal = mouseVector / mouseDistance;
            float alpha = mouseDistance > MAX_MOUSE_DISTANCE ? 1.0 : mouseDistance/MAX_MOUSE_DISTANCE;
            acceleration += 0.4f * alpha * mouseNormal;
        }
    }

    // Push back towards the play area
    if (position.x > width)  { acceleration += glm::vec2(-1.0, 0.0); }
    else if (position.x < 0) { acceleration += glm::vec2(+1.0, 0.0); }
    if (position.y > height) { acceleration += glm::vec2(0.0, -1.0); }
    else if (position.y < 0) { acceleration += glm::vec2(0.0, 1.0);  }

    velocity += acceleration;

    // On jump change velocity rapidly
    if (jumpCounter > 0) {
        if (jumpCounter == JUMP_DURATION) { // Just jumped
            if (mouseDistance > 0) {
                glm::vec2 mouseNormal = mouseVector / mouseDistance;
                // velocity = mouseNormal * glm::abs(glm::dot(velocity, mouseNormal));
                velocity = mouseNormal * glm::length(velocity);
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

    if (mouseDistance < 10) {
        velocity = glm::vec2(0,0);
    }

    position += velocity;
};

void Them::draw(piksel::Graphics& g, glm::vec2 mousePosition) {
    g.push();

    g.line(position.x, position.y, mousePosition.x, mousePosition.y);

    g.rectMode(piksel::DrawMode::CENTER);
    g.stroke(BLACK);
    g.fill(WHITE);

    int size = 20;
    if (jumpCounter > 0) {
        float alpha = 1 - (float)jumpCounter/JUMP_DURATION;
        alpha = fastStart2(firstHalf(alpha)) + slowStart3(secondHalfBackwards(alpha));
        size += 20*alpha;
    }
    g.ellipse(position.x, position.y, size, size);

    // Draw velocity arrow
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
    jumpCounter = JUMP_DURATION;
}