#include "link.hpp"
#include "defines.hpp"

#include <glm/glm.hpp>
#include <glm/gtc/random.hpp>
#include <iostream>

// void Link::update() {
//     glm::vec2 startWobble = glm::diskRand(LINK_WOBBLE);
//     start += startWobble;
//     if (previousLink != nullptr) {
//         previousLink->end += startWobble;
//     }
// }

void Link::draw(piksel::Graphics& g) {
    g.strokeWeight(durability);
    g.stroke(color); g.fill(color);
    // g.ellipse(start.x, start.y, 4,4);
    // g.ellipse(end.x, end.y, 4,4);
    if (not dashed) {
        g.line(start.x, start.y, end.x, end.y);
    } else {
    glm::vec2 dashedVector = end - start;
        float dashedVectorLength = glm::length(dashedVector);
        if (dashedVectorLength < DASH_LENGTH) {
            g.line(start.x, start.y, end.x, end.y);
        } else {
            glm::vec2 dashedVectorNormal = dashedVector / dashedVectorLength;
            glm::vec2 dash = (float) DASH_LENGTH * dashedVectorNormal;
            int i = 0;
            for (; i < (dashedVectorLength/DASH_LENGTH-1); i += 2) {
                g.line(
                    start.x + i*dash.x, start.y + i*dash.y,
                    start.x + (i+1)*dash.x, start.y + (i+1)*dash.y
                    );
            }
            // Draw the final little bit of the dashed line
            if (glm::fract(dashedVectorLength/(2*DASH_LENGTH)) < 0.5) {
                g.line(
                    start.x + i*dash.x, start.y + i*dash.y,
                    end.x, end.y
                );
            }
        }
    }
}

bool Link::intersectsCircle(glm::vec2 center, float radius) {
    glm::vec2 startCenterVector = center - start;
    float startCenterVectorLength = glm::length(startCenterVector);
    if (startCenterVectorLength == 0) { return true; }

    glm::vec2 startEndVector = end - start;
    float startEndVectorLength = glm::length(startEndVector);
    if (startEndVectorLength == 0) { return startCenterVectorLength < radius; }
    glm::vec2 startEndVectorNormal = startEndVector / startEndVectorLength;

    float projectedLength = glm::dot(startCenterVector, startEndVectorNormal);
    if (projectedLength < -radius) { return false; }
    if (projectedLength > startEndVectorLength+radius) { return false; }
    glm::vec2 projectedVector = startEndVectorNormal * projectedLength;
    glm::vec2 orthogonalVector = startCenterVector - projectedVector;
    float orthogonalVectorLength = glm::length(orthogonalVector);
    return orthogonalVectorLength < radius;
}

void Link::hit() {
    if (iframesCounter == 0) {
        durability--;
        iframesCounter = LINK_IFRAMES;
    }
}