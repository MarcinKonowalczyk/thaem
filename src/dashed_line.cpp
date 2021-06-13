
#include "dashed_line.hpp"
#include <piksel/baseapp.hpp>

void drawDashedLine(piksel::Graphics& g, glm::vec2 start, glm::vec2 end, float dash_length) {
    glm::vec2 dashedVector = end - start;
    float dashedVectorLength = glm::length(dashedVector);
    if (dashedVectorLength < dash_length) {
        g.line(start.x, start.y, end.x, end.y);
    } else {
        glm::vec2 dashedVectorNormal = dashedVector / dashedVectorLength;
        glm::vec2 dash = (float) dash_length * dashedVectorNormal;
        int i = 0;
        for (; i < (dashedVectorLength/dash_length-1); i += 2) {
            g.line(
                start.x + i*dash.x, start.y + i*dash.y,
                start.x + (i+1)*dash.x, start.y + (i+1)*dash.y
                );
        }
        // Draw the final little bit of the dashed line
        if (glm::fract(dashedVectorLength/(2*dash_length)) < 0.5) {
            g.line(
                start.x + i*dash.x, start.y + i*dash.y,
                end.x, end.y
            );
        }
    }
}