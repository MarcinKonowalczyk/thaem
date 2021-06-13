#ifndef DASHED_LINE_HPP
#define DASHED_LINE_HPP

#include <piksel/baseapp.hpp>
#include <glm/glm.hpp>

void drawDashedLine(piksel::Graphics& g, glm::vec2 start, glm::vec2 end, float dash_length);

#endif /* DASHED_LINE_HPP */