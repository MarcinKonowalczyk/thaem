#ifndef THEM_HPP
#define THEM_HPP

#include <piksel/baseapp.hpp>

#include "link.hpp"
#include "bullet.hpp"
#include "pop.hpp"

#include <glm/glm.hpp>
#include <vector>

class Them {
public:
    Them() :
        position(glm::vec2(0.0, 0.0)),
        velocity(glm::vec2(0.0, 0.0)),
        links(std::vector<Link>(0)),
        mouseLink(Link()),
        dead(false)
        {}
    void update(
        glm::vec2 mousePosition,
        float width, float height,
        bool rightMousePressed,
        std::vector<Bullet>& blueBullets,
        std::vector<Bullet>& redBullets,
        std::vector<Bullet>& blackBullets,
        std::vector<Pop>& pops,
        unsigned int& score);
    void draw(
        piksel::Graphics& g,
        glm::vec2 mousePosition,
        bool rightMousePressed);
    void addLink(glm::vec2 position, unsigned int& score);
    std::vector<Link> links;
    bool intersectsCircle(glm::vec2 center, float radius);
    bool dead;
    glm::vec2 position;
private:
    void updateLinks(bool rightMousePressed);
    void collisionCore(
        std::vector<Bullet>& bulletsVector,
        std::vector<Pop>& pops,
        unsigned int& score,
        int scoreIncrement,
        int damage
    );
    glm::vec2 velocity;
    Link mouseLink;
};

#endif /* THEM_HPP */