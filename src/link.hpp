#ifndef LINK_HPP
#define LINK_HPP

#include <piksel/baseapp.hpp>
#include <glm/glm.hpp>

class Link {
public:
    Link() : 
        start(glm::vec2(0,0)),
        end(glm::vec2(100,100)),
        durability(2),
        color(glm::vec4(0.0, 0.0, 0.0, 1.0)),
        dashed(false),
        iframesCounter(0)
    {}
    void update();
    void draw(piksel::Graphics& g);
    bool intersectsCircle(glm::vec2 center, float radius);
    void hit();
    glm::vec2 start;
    glm::vec2 end;
    int durability;
    glm::vec4 color;
    bool dashed;
    unsigned int iframesCounter;
};

#endif /* LINK_HPP */