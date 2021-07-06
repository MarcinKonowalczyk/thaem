#include "pop.hpp"
#include "defines.hpp"
#include "interval_transforms.hpp"
#include "colors.hpp"
// #include "dashed_line.hpp"

#include <piksel/baseapp.hpp>
#include <glm/glm.hpp>
#include <glm/gtc/random.hpp>
#include <vector>

void Pop::update(int width, int height) {
    glm::vec2 acceleration = glm::vec2(0,0);
    acceleration += glm::diskRand(0.05);
    float additionalBoundary = 0.5f*getCurrentAlpha()*radius;
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
    g.push();
    g.strokeWeight(0);
    float alpha = getCurrentAlpha();
    float r = radius*fastStart3(alpha);
    switch (type) {
        case T_BLUE_POP: {
            r += BLUE_BULLET_RADIUS;
            // g.fill(glm::vec4(glm::mix(LINES_B_3,GREY_3,slowStart3(alpha)),fastStart2(1-alpha)));
            g.fill(glm::vec4(LINES_B_3,1-fastStart2(alpha)));
        } break;
        case T_RED_POP: {
            r += RED_BULLET_RADIUS;
            g.fill(glm::vec4(LINES_R_3,1-fastStart2(alpha)));
        } break;
        case T_BLACK_POP: {
            r += BLACK_BULLET_RADIUS;
            g.fill(glm::vec4(BLACK_3,1-fastStart2(alpha)));
        } break;
        case T_THEM_POP: {
            r += THEM_RADIUS;
            g.fill(glm::vec4(BLACK_3,1-fastStart3(alpha)));
        }
    }
    g.ellipse(position.x, position.y, r, r);
    g.fill(glm::vec4(GREY_3, 0.9f)); // background color
    g.pop();
};

float Pop::getCurrentAlpha() {
    return ((max_lifetime-lifetime)/(float)max_lifetime);
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
