#include "them.hpp"
#include "defines.hpp"
#include "colors.hpp"
#include "interval_transforms.hpp"
#include "link.hpp"

#include <iostream>
#include <glm/gtc/random.hpp>
#include <deque>

void DEBUB_printVec2(glm::vec2 vec2) {
    std::cout << vec2.x << " " << vec2.y << std::endl;
}

void Them::update(
    glm::vec2 mousePosition,
    float width, float height,
    bool rightMousePressed) {
    bool hasLinks = links.size() > 0;
    
    updateLinks();

    glm::vec2 link;
    if (hasLinks and not rightMousePressed) {
        link = links[0].end;
    } else {
        link = mousePosition;
    }

    glm::vec2 linkVector = link - position;
    float linkDistance = glm::length(linkVector);

    if (linkDistance < THEM_RADIUS ) {
        if (hasLinks and not rightMousePressed) {
            links.pop_front();
        } else {
            velocity = 0.9f*velocity + 0.1f*(0.01f*linkVector);
        }
    }

    glm::vec2 acceleration = glm::vec2(0,0);

    acceleration += glm::diskRand(0.05);

    if (linkDistance > 0 and hasLinks) {
        glm::vec2 linkNormal = linkVector / linkDistance;
        float alpha = linkDistance > MAX_MOUSE_DISTANCE ? 1.0 : linkDistance/MAX_MOUSE_DISTANCE;
        acceleration += (rightMousePressed ? FAST_ACCELERATION : SLOW_ACCELERATION) * alpha * linkNormal;
    }

    // Push back towards the play area
    float additionalBoundary = 0.5f*THEM_RADIUS;
    if (position.x > width-additionalBoundary)  { acceleration += glm::vec2(-1.0, 0.0); }
    else if (position.x < additionalBoundary) { acceleration += glm::vec2(+1.0, 0.0); }
    if (position.y > height-additionalBoundary) { acceleration += glm::vec2(0.0, -1.0); }
    else if (position.y < additionalBoundary) { acceleration += glm::vec2(0.0, 1.0);  }

    velocity += acceleration;

    // Handle drag at the very end
    float velocityMagnitude = glm::length(velocity);
    if (velocityMagnitude > 0) {
        glm::vec2 velocityNormal = velocity / velocityMagnitude;
        float dragMagnitude = 0.01 * velocityMagnitude * velocityMagnitude;
        if (linkDistance < 20) {
            dragMagnitude *= 10;
        }
        velocity -= dragMagnitude * velocityNormal;
    }

    position += velocity;

    if (hasLinks) {
        links.front().start = position;
    }

    if (hasLinks and not rightMousePressed) {
        mouseLink.start = links.back().end;
    } else {
        mouseLink.start = position;
    }
    mouseLink.end = mousePosition;
};

void Them::draw(
    piksel::Graphics& g,
    glm::vec2 mousePosition,
    bool rightMousePressed) {
    g.push();
    bool hasLinks = links.size() > 0;

    // Draw path
    g.strokeWeight(2);
    glm::vec2 drawPosition = position;
    int lineCounter = 0;
    for (Link& link : links) {
        if (lineCounter == 0) {
            if (rightMousePressed) {
                link.color = BLACK;
            } else {
                link.color = LINES_B;
            }
        } else if (lineCounter == 1) {
            if (rightMousePressed) {
                link.color = BLACK;
            } else {
                link.color = LINES_R;
            }
        } else {
            link.color = BLACK;
        }
        link.draw(g);
        lineCounter++;
    }

    // Dashed line to the mouse position
    mouseLink.dashed = true;
    if (rightMousePressed) {
        mouseLink.color = BLACK;
    } else {
        mouseLink.color = glm::mix(WHITE,BLACK,0.65);
    }
    mouseLink.draw(g);

    glm::vec4 themColor = WHITE;
    int i = 0;
    for (auto it = links.begin(); it != links.end(); it++) {
        if (i++ > 1 and it->intersectsCircle(position,THEM_RADIUS)) {
            themColor = LINES_Y;
        }
    }
    // Draw Them
    g.rectMode(piksel::DrawMode::CENTER);
    g.strokeWeight(2);
    g.stroke(BLACK);
    if (rightMousePressed) {
        g.fill(BLACK);
    } else {
        g.fill(themColor);
    }
    g.ellipse(position.x, position.y, 2*THEM_RADIUS, 2*THEM_RADIUS);

    // Draw velocity arrow
    // g.strokeWeight(1);
    // float velocityMagnitude = glm::length(velocity);
    // if (velocityMagnitude > 0) {
    //     glm::vec2 velocityNormal = velocity / velocityMagnitude;
    //     glm::vec2 velocityOrthogonal = glm::vec2(velocityNormal.y, -velocityNormal.x);
    //     glm::vec2 velocityIndicator = velocityNormal * 50.0f;
    //     g.line(position.x, position.y,
    //         position.x + velocityIndicator.x,
    //         position.y + velocityIndicator.y);
    // }

    g.pop();
};

void Them::addLink(glm::vec2 newPosition) {
    bool hasLinks = links.size() > 0;
    if (links.size() < MAX_LINKS-1) {
        Link newLink = Link();
        newLink.start = hasLinks ? links.back().end : position;
        newLink.end = newPosition;
        // if (hasLinks) {
        //     links.back().setAsPreviousLinkOf(&newLink);
        // }
        links.push_back(newLink);
    }
};

void Them::setPosition(float x, float y) {
    position = glm::vec2(x,y);
}

void Them::updateLinks() {
    if (links.size() == 0) { return; }

    // Link wobble
    int i = 0;
    for (; i < links.size(); i ++) {
        glm::vec2 wobble = glm::diskRand(LINK_WOBBLE);
        links.at(i).start += wobble;
        if (i > 0) {
            links.at(i-1).end += wobble;
        }
    }
    links.at(--i).end += glm::diskRand(LINK_WOBBLE);

    // Hit links with the them
    for (int i = 0; i < links.size(); i++) {
        Link& link = links.at(i);
        if (i > 1 and link.intersectsCircle(position,THEM_RADIUS)) {
            link.hit();
        }
    }

    // Remove dead links
    std::deque<Link> newLinks = std::deque<Link>(0);
    glm::vec2 previousEnd = position;
    for (int i = 0; i < links.size(); i++) {
        Link& link = links.at(i);
        if (link.durability > 0) {
            link.start = previousEnd;
            newLinks.push_back(link);
        }
        previousEnd = links.at(i).end;
    }
    links = newLinks;

    // Decrement iframes counter
    for (int i = 0; i < links.size(); i++) {
        Link& link = links.at(i);
        if (link.iframesCounter > 0) {
            link.iframesCounter--;
        }
    }
}