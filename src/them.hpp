#ifndef THEM_HPP
#define THEM_HPP

#include "link.hpp"

#include <piksel/baseapp.hpp>
#include <glm/glm.hpp>
#include <deque>

class Them {
public:
    Them() :
        position(glm::vec2(0.0, 0.0)),
        velocity(glm::vec2(0.0, 0.0)),
        links(std::deque<Link>(0)),
        mouseLink(Link())
        {}
    void setPosition(float x, float y);
    void update(
        glm::vec2 mousePosition,
        float width, float height,
        bool rightMousePressed);
    void draw(
        piksel::Graphics& g,
        glm::vec2 mousePosition,
        bool rightMousePressed);
    void addLink(glm::vec2 position);
private:
    void updateLinks();
    glm::vec2 position;
    glm::vec2 velocity;
    std::deque<Link> links;
    Link mouseLink;
};

#endif /* THEM_HPP */