#include "pop.hpp"
#include "defines.hpp"
// #include "interval_transforms.hpp"
#include "colors.hpp"
// #include "dashed_line.hpp"

#include <piksel/baseapp.hpp>
#include <glm/glm.hpp>
#include <glm/gtc/random.hpp>
#include <vector>

void Pop::update(int width, int height) {
    glm::vec2 acceleration = glm::vec2(0,0);
    acceleration += glm::diskRand(0.05);
    float additionalBoundary = 0.5f*getCurrentRadius();
    if (position.x > width-additionalBoundary)  { acceleration += glm::vec2(-1.0, 0.0); }
    else if (position.x < additionalBoundary) { acceleration += glm::vec2(+1.0, 0.0); }
    if (position.y > height-additionalBoundary) { acceleration += glm::vec2(0.0, -1.0); }
    else if (position.y < additionalBoundary) { acceleration += glm::vec2(0.0, 1.0);  }

    velocity += acceleration;

    // Handle drag at the very end
    float velocityMagnitude = glm::length(velocity);
    if (velocityMagnitude > 0) {
        glm::vec2 velocityNormal = velocity / velocityMagnitude;
        float dragMagnitude = POP_DRAG * (velocityMagnitude * velocityMagnitude);
        velocity -= dragMagnitude * velocityNormal;
    }
    position += velocity;
    if (lifetime > 0) { lifetime--; }
};


void Pop::draw(piksel::Graphics& g) {
    g.strokeWeight(0);
    int r = getCurrentRadius();
    g.ellipse(position.x, position.y, r, r);
};

int Pop::getCurrentRadius() {
    return ((POP_LIFETIME-lifetime)/(float)POP_LIFETIME)*radius;
};

Pop makePop(popType type, glm::vec2 position, glm::vec2 velocity) {
    Pop pop = Pop();
    pop.type = type;
    pop.position = position;
    pop.velocity = velocity;
    return pop;
};

void updatePops(std::vector<Pop>& pops, int width, int height) {
    for (auto pop = pops.begin(); pop != pops.end(); ++pop) {
        pop->update(width, height);
        if (pop->lifetime <= 0) {
            pop = pops.erase(pop);
            if (pop == pops.end()) { break; }
        }
    }
}
