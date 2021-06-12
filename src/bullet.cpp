#include "bullet.hpp"
#include <piksel/baseapp.hpp>
#include <glm/glm.hpp>

void Bullet::update(
        glm::vec2 mousePosition,
        float width, float height,
        bool rightMousePressed) {
    
    glm::vec2 acceleration = glm::vec2(0,0);

    switch (type) {
        case BT_BLACK: {

        } break;
        case BT_BLUE: {

        } break; 
        case BT_RED: {

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

    position += velocity;
};

void Bullet::draw(piksel::Graphics& g, bool rightMousePressed) {

};
