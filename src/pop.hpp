#ifndef POP_HPP
#define POP_HPP

#include <piksel/baseapp.hpp>
#include <glm/glm.hpp>
#include <vector>

#include "defines.hpp"

enum popType {
    T_BLACK_POP,
    T_BLUE_POP,
    T_RED_POP,
    // T_THEM_POP,
    // T_LINK_POP
};

class Pop {
public:
    Pop() : 
        position(glm::vec2(0,0)),
        velocity(glm::vec2(0,0)),
        type(T_BLACK_POP),
        radius(30),
        lifetime(POP_LIFETIME)
        {}
    void update(int width, int height);
    void draw(piksel::Graphics& g);
    glm::vec2 position;
    glm::vec2 velocity;
    popType type;
    float radius;
    unsigned int lifetime;
private:
    int getCurrentRadius();
};

Pop makePop(popType type, glm::vec2 position, glm::vec2 velocity);

void updatePops(std::vector<Pop>& pops, int width, int height);

#endif /* POP_HPP */