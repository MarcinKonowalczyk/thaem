#ifndef BULLET_HPP
#define BULLET_HPP

#include <piksel/baseapp.hpp>
#include <glm/glm.hpp>
#include <vector>

enum bulletType {
    T_BLUE,
    T_RED,
    T_BLACK
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
        std::vector<Bullet>& blueBullets,
        std::vector<Bullet>& redBullets,
        std::vector<Bullet>& blackBullets,
        glm::vec2 themPosition,
        float blueDragMultiplier,
        float redDragMultiplier
        );
    void draw(
        piksel::Graphics& g,
        bool rightMousePressed,
        glm::vec2 mousePosition,
        float width, float height,
        glm::vec2 themPosition,
        std::vector<Bullet>& blueBullets,
        std::vector<Bullet>& redBullets,
        bool dead
        );
    void hit();
    glm::vec2 position;
    glm::vec2 velocity;
    bulletType type;
    float radius;
    bool collision;
    unsigned int durability;
private:
    glm::vec2 repellCore(
        Bullet& other,
        float repellCoefficient)
        ;
};

Bullet makeBullet(float width, float height);

bool spawnBullet(
    bulletType type,
    std::vector<Bullet>& bulletsVector,
    float width, float height,
    int bulletLimit
    );

#endif /* BULLET_HPP */