#ifndef BULLET_HPP
#define BULLET_HPP

#include <piksel/baseapp.hpp>
#include <glm/glm.hpp>
#include <vector>

enum bulletType {
    T_BLACK,
    T_BLUE,
    T_RED
};

class Bullet {
public:
    Bullet() : 
        position(glm::vec2(0,0)),
        velocity(glm::vec2(0,0)),
        type(T_BLACK),
        radius(10),
        collision(false),
        durability(1)
        {}
    void update(
        glm::vec2 mousePosition,
        float width, float height,
        bool rightMousePressed,
        std::vector<Bullet> blueBullets
        );
    void draw(
        piksel::Graphics& g,
        bool rightMousePressed,
        glm::vec2 mousePosition,
        bool dead);
    void hit();
    glm::vec2 position;
    glm::vec2 velocity;
    bulletType type;
    float radius;
    bool collision;
    unsigned int durability;
};

bool spawnBlueBullet(
    std::vector<Bullet>& blueBullets,
    float width, float height);

#endif /* BULLET_HPP */