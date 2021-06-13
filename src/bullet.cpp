#include "bullet.hpp"
#include "defines.hpp"
#include "interval_transforms.hpp"
#include "colors.hpp"
#include "dashed_line.hpp"

#include <piksel/baseapp.hpp>
#include <glm/glm.hpp>
#include <glm/gtc/random.hpp>
#include <vector>

void Bullet::update(
        glm::vec2 mousePosition,
        float width, float height,
        bool rightMousePressed,
        std::vector<Bullet> blueBullets) {
    
    glm::vec2 acceleration = glm::vec2(0,0);

    acceleration += glm::diskRand(0.05);

    switch (type) {
        case T_BLACK: {
            // TODO
        } break;
        case T_BLUE: {
            glm::vec2 attractVector = mousePosition - position;
            float attractVectorLength = glm::length(attractVector);
            if (attractVectorLength > 0) {
                glm::vec2 attractVectorNormal = attractVector / attractVectorLength;
                acceleration += BLUE_BULLET_MOUSE_ATTRACT * attractVectorNormal;
            }
            for (Bullet& bullet : blueBullets) {
                glm::vec2 repellVector = bullet.position - position;
                float repellVectorLength = glm::length(repellVector);
                if (repellVectorLength > 0) {
                    glm::vec2 repellVectorNormal = repellVector / repellVectorLength;
                    float alpha = 1.0 - glm::min(repellVectorLength,100.0f)/100;
                    acceleration -= BLUE_BULLET_FRIENDLY_REPELL * repellVectorNormal * slowStart4(alpha);
                }
            }
        } break; 
        case T_RED: {
            // TODO
        } break;
    }

    float additionalBoundary = 0.5f*radius;
    if (collision) {
        if (position.x > width-additionalBoundary)  { acceleration += glm::vec2(-1.0, 0.0); }
        else if (position.x < additionalBoundary) { acceleration += glm::vec2(+1.0, 0.0); }
        if (position.y > height-additionalBoundary) { acceleration += glm::vec2(0.0, -1.0); }
        else if (position.y < additionalBoundary) { acceleration += glm::vec2(0.0, 1.0);  }
    } else { // Turn on collision after the bullet enters play area
        if (
            position.x <= width-additionalBoundary and
            position.x >= additionalBoundary and
            position.y <= height-additionalBoundary and
            position.y >= additionalBoundary
            ) { collision = true; }
        // TODO - test whether bullet outside of 2*play area, and destroy it ??
    }

    velocity += acceleration;

    // Handle drag at the very end
    float velocityMagnitude = glm::length(velocity);
    if (velocityMagnitude > 0) {
        glm::vec2 velocityNormal = velocity / velocityMagnitude;
        float dragMagnitude;
        switch (type) {
            case T_BLACK: {
                dragMagnitude = BLACK_BULLET_DRAG;
            } break;
            case T_BLUE: {
                dragMagnitude = BLUE_BULLET_DRAG;
            } break; 
            case T_RED: {
                dragMagnitude = RED_BULLET_DRAG;
            } break;
        }
        dragMagnitude *= (velocityMagnitude * velocityMagnitude);
        // TODO
        // if (linkDistance < 20) {
        //     dragMagnitude *= 10;
        // }
        velocity -= dragMagnitude * velocityNormal;
    }

    position += velocity;
};

void Bullet::draw(
    piksel::Graphics& g,
    bool rightMousePressed,
    glm::vec2 mousePosition,
    bool dead) {

    if (dead) {
        switch (type) {
            case T_BLACK: {
                // 
            } break;
            case T_BLUE: {
                g.strokeWeight(2);
                g.stroke(glm::vec4(BLACK_3,0.1));
                drawDashedLine(g, position, mousePosition, DASH_LENGTH);
            } break; 
            case T_RED: {
                // 
            } break;
        }
    }

    g.strokeWeight(0);
    int radius;
    switch (type) {
        case T_BLACK: {
            g.fill(BLACK);
            radius = BLACK_BULLET_RADIUS;
        } break;
        case T_BLUE: {
            g.fill(LINES_B);
            radius = BLUE_BULLET_RADIUS;
        } break; 
        case T_RED: {
            g.fill(LINES_R);
            radius = RED_BULLET_RADIUS;
        } break;
    }
    g.ellipse(position.x, position.y, radius, radius);
};

void Bullet::hit() {
    if (durability > 0) { durability--; }
}