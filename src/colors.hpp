#ifndef COLORS_HPP
#define COLORS_HPP

#include <glm/glm.hpp>

// Basic colors
#define WHITE_3 glm::vec3(1.0f, 1.0f, 1.0f)
#define GREY_3  glm::vec3(0.5f, 0.5f, 0.5f)
#define BLACK_3 glm::vec3(0.0f, 0.0f, 0.0f)
#define RED_3   glm::vec3(1.0f, 0.0f, 0.0f)
#define GREEN_3 glm::vec3(0.0f, 1.0f, 0.0f)
#define BLUE_3  glm::vec3(0.0f, 0.0f, 1.0f)

#define WHITE_4 glm::vec4(1.0f, 1.0f, 1.0f, 1.0f)
#define GREY_4  glm::vec4(0.5f, 0.5f, 0.5f, 1.0f)
#define BLACK_4 glm::vec4(0.0f, 0.0f, 0.0f, 1.0f)
#define RED_4   glm::vec4(1.0f, 0.0f, 0.0f, 1.0f)
#define GREEN_4 glm::vec4(0.0f, 1.0f, 0.0f, 1.0f)
#define BLUE_4  glm::vec4(0.0f, 0.0f, 1.0f, 1.0f)

#define WHITE WHITE_4
#define GREY  GREY_4
#define BLACK BLACK_4
#define RED   RED_4
#define GREEN GREEN_4
#define BLUE  BLUE_4

// Matlab "lines" colormap colors

#define LINES_0_3 glm::vec3(0.067f, 0.455f, 0.729f)
#define LINES_1_3 glm::vec3(0.843f, 0.329f, 0.149)
#define LINES_2_3 glm::vec3(0.925f, 0.690f, 0.208f)
#define LINES_3_3 glm::vec3(0.490f, 0.200f, 0.549f)
#define LINES_4_3 glm::vec3(0.471f, 0.671f, 0.227f)
#define LINES_5_3 glm::vec3(0.325f, 0.749f, 0.925f)
#define LINES_6_3 glm::vec3(0.651f, 0.09f, 0.196f)

#define LINES_0_4 glm::vec4(0.067f, 0.455f, 0.729f, 1.0f)
#define LINES_1_4 glm::vec4(0.843f, 0.329f, 0.149, 1.0f)
#define LINES_2_4 glm::vec4(0.925f, 0.690f, 0.208f, 1.0f)
#define LINES_3_4 glm::vec4(0.490f, 0.200f, 0.549f, 1.0f)
#define LINES_4_4 glm::vec4(0.471f, 0.671f, 0.227f, 1.0f)
#define LINES_5_4 glm::vec4(0.325f, 0.749f, 0.925f, 1.0f)
#define LINES_6_4 glm::vec4(0.651f, 0.09f, 0.196f, 1.0f)

#define LINES_0 LINES_0_4
#define LINES_1 LINES_1_4
#define LINES_2 LINES_2_4
#define LINES_3 LINES_3_4
#define LINES_4 LINES_4_4
#define LINES_5 LINES_5_4
#define LINES_6 LINES_6_4

// Same thing but now with color labels

#define LINES_B_3 LINES_0_3
#define LINES_R_3 LINES_1_3
#define LINES_Y_3 LINES_2_3
#define LINES_P_3 LINES_3_3
#define LINES_G_3 LINES_4_3
#define LINES_C_3 LINES_5_3
#define LINES_X_3 LINES_6_3

#define LINES_B_4 LINES_0_4
#define LINES_R_4 LINES_1_4
#define LINES_Y_4 LINES_2_4
#define LINES_P_4 LINES_3_4
#define LINES_G_4 LINES_4_4
#define LINES_C_4 LINES_5_4
#define LINES_X_4 LINES_6_4

#define LINES_B LINES_0 
#define LINES_R LINES_1
#define LINES_Y LINES_2
#define LINES_P LINES_3
#define LINES_G LINES_4
#define LINES_C LINES_5
#define LINES_X LINES_6

#endif /* COLORS_HPP */



