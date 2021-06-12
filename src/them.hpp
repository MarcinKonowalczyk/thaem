#ifndef THEM_HPP
#define THEM_HPP

#include <piksel/baseapp.hpp>
#include <glm/glm.hpp>
#include <deque>

class Them {
public:
    Them() : position(glm::vec2(0.0, 0.0))
        , velocity(glm::vec2(0.0, 0.0))
        , waypoints(std::deque<glm::vec2>(0))
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
    void addWaypoint(glm::vec2 position);
private:
    glm::vec2 position;
    glm::vec2 velocity;
    std::deque<glm::vec2> waypoints;
};

#endif /* THEM_HPP */