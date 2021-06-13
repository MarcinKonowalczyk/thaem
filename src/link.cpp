#include "link.hpp"
#include "defines.hpp"
#include "colors.hpp"
#include "dashed_line.hpp"

#include <glm/glm.hpp>
#include <glm/gtc/random.hpp>
#include <iostream>

void Link::draw(piksel::Graphics& g) {
    
    if (showDurability) {
        glm::vec2 lineVector = end - start;
        float lineVectorLength = glm::length(lineVector);
        if (lineVectorLength > (durability*DURABILITY_INDICATOR_SPACING+THEM_RADIUS) ) {
            glm::vec2 lineVectorNormal = lineVector / lineVectorLength;
            g.push();
            g.strokeWeight(0);
            g.fill(BLACK);

            for (int i = 0; i < durability; i++) {
                float pointPosition;
                if (durability % 2 == 0) { // Even
                    pointPosition = lineVectorLength/2 - DURABILITY_INDICATOR_SPACING/2 - (durability/2-1)*DURABILITY_INDICATOR_SPACING + i*DURABILITY_INDICATOR_SPACING;
                } else {
                    pointPosition = lineVectorLength/2 - (durability-1)/2*DURABILITY_INDICATOR_SPACING + i*DURABILITY_INDICATOR_SPACING;
                }
                glm::vec2 pointVector = start + lineVectorNormal * pointPosition;
                g.ellipse(pointVector.x, pointVector.y, DURABILITY_INDICATOR_SIZE, DURABILITY_INDICATOR_SIZE);
            }
            g.pop();
        }

        // TODO ??
        // int stepSize = 5;
        // glm::vec2 lineVector = end - start;
        // float lineVectorLength = glm::length(lineVector);
        // if (lineVectorLength > stepSize) {
        //     glm::vec2 lineVectorNormal = lineVector / lineVectorLength;
        //     for (int i = 0; i < lineVectorLength/stepSize; i++) {
        //         float alpha = i / 
        //     }
        // }
    }

    g.strokeWeight(2);
    g.stroke(BLACK); g.fill(BLACK);
    if (not dashed) {
        g.line(start.x, start.y, end.x, end.y);
    } else {
        glm::vec2 dashedVector = end - start;
        float dashedVectorLength = glm::length(dashedVector);
        if (dashedVectorLength < DASH_LENGTH) {
            g.line(start.x, start.y, end.x, end.y);
        } else {
            drawDashedLine(g, start, end, DASH_LENGTH);
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

bool Link::hit(int damage) {
    if (iframesCounter == 0) {
        if (durability > damage) { durability--; }
        else { durability -= damage; }
        iframesCounter = LINK_IFRAMES;
        return true;
    } else {
        return false;
    }
}