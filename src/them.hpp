#ifndef THEM_HPP
#define THEM_HPP

#include <piksel/baseapp.hpp>
#include <glm/glm.hpp>

enum ThemState {
    ON_THE_GROUD = 0,
    IN_THE_AIR,
};

class Them {
public:
    Them() : height(0)
        , position(glm::vec2(0.0, 0.0))
        , velocity(glm::vec2(0.0, 0.0))
        , jumpCounter(0)
        , queuedJump(false)
        {}
    void update(glm::vec2 mousePosition, float width, float height);
    void draw(piksel::Graphics& g, glm::vec2 mousePosition);
    void jump();
    glm::vec2 position;
private:
    glm::vec2 velocity;
    float height;
    unsigned int jumpCounter;
    bool queuedJump;
};

#endif /* THEM_HPP */