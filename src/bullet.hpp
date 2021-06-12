#ifndef BULLET_HPP
#define BULLET_HPP

#include <piksel/baseapp.hpp>
#include <glm/glm.hpp>
#include "colors.hpp"

enum bulleType {
    BT_BLACK = 0,
    BT_BLUE,
    BT_RED
};

class Bullet {
public:
    Bullet() : 
        position(glm::vec2(0,0)),
        velocity(glm::vec2(0,0)),
        type(BT_BLACK),
        radius(10),
        collision(false)
        {}
    void update(
        glm::vec2 mousePosition,
        float width, float height,
        bool rightMousePressed
        );
    void draw(
        piksel::Graphics& g,
        bool rightMousePressed);
    glm::vec2 position;
    glm::vec2 velocity;
    bulleType type;
    float radius;
    bool collision;
};

#endif /* BULLET_HPP */