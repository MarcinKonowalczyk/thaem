#include "them.hpp"
#include "defines.hpp"
#include "colors.hpp"
#include "interval_transforms.hpp"
#include "link.hpp"

#include <iostream>
#include <glm/gtc/random.hpp>
#include <vector>

void Them::update(
    glm::vec2 mousePosition,
    float width, float height,
    bool rightMousePressed,
    std::vector<Bullet>& blueBullets,
    std::vector<Bullet>& redBullets,
    std::vector<Bullet>& blackBullets,
    std::vector<Pop>& pops,
    unsigned int& score) {
    
    updateLinks(rightMousePressed);

    // Collide with bullets
    if (!dead) {
        collisionCore(blueBullets, pops, score, BLUE_BULLET_SCORE, BLUE_BULLETS_DAMAGE);
        collisionCore(redBullets, pops, score, RED_BULLET_SCORE, RED_BULLETS_DAMAGE);
        collisionCore(blackBullets, pops, score, BLACK_BULLET_SCORE, BLACK_BULLETS_DAMAGE);
    }
    
    glm::vec2 wapoint;
    if (!links.empty() and not rightMousePressed) {
        wapoint = links.begin()->end;
    } else {
        wapoint = mousePosition;
    }

    glm::vec2 linkVector = wapoint - position;
    float linkDistance = glm::length(linkVector);

    if (linkDistance < THEM_RADIUS and !dead) {
        if (!links.empty() and not rightMousePressed) {
            links.erase(links.begin());
        } else {
            velocity = 0.9f*velocity + 0.1f*(0.01f*linkVector);
        }
    }

    glm::vec2 acceleration = glm::vec2(0,0);

    if (!dead) {
        acceleration += glm::diskRand(0.05);
    } else {
        acceleration += glm::diskRand(0.15);
    }

    if (linkDistance > 0 and !links.empty() and !dead) {
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

    if (!links.empty()) {
        links.front().start = position;
    }

    if (!links.empty() and not rightMousePressed) {
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

    // Draw path
    g.strokeWeight(2);
    glm::vec2 drawPosition = position;
    int lineCounter = 0;
    for (Link& link : links) {
        link.draw(g);
        lineCounter++;
    }

    // Dashed line to the mouse position
    if (!dead) {
        mouseLink.dashed = true;
        mouseLink.showDurability = false;
        if (rightMousePressed) {
            mouseLink.color = BLACK;
        } else {
            mouseLink.color = glm::mix(WHITE,BLACK,0.65);
        }
        mouseLink.draw(g);
    }

    glm::vec4 themColor = WHITE;
    // Draw Them
    g.rectMode(piksel::DrawMode::CENTER);
    if (dead) { g.strokeWeight(0);
    } else { g.strokeWeight(2);
    }
    g.stroke(BLACK);
    if (rightMousePressed) {
        g.fill(BLACK);
    } else {
        g.fill(themColor);
    }
    g.ellipse(position.x, position.y, 2*THEM_RADIUS, 2*THEM_RADIUS);
    g.pop();
};

void Them::addLink(glm::vec2 newPosition, unsigned int& score) {
    if (links.size() < LINK_LIMIT-1 and !dead) {
        Link newLink = Link();
        newLink.start = !links.empty() ? links.back().end : position;
        newLink.end = newPosition;
        newLink.durability = LINK_DURABILITY;
        links.push_back(newLink);
        if (score > LINK_SCORE_PENALTY) {
            score -= LINK_SCORE_PENALTY;
        }
    }
};

void Them::updateLinks(bool rightMousePressed) {
    if (links.empty()) { return; }

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

    // Dont do anything but wobble when dead
    if (dead) { return; }

    // Remove dead links
    // Careful! Mutating the vector while iterating over it.
    glm::vec2 previousEnd = position;
    for (auto link = links.begin(); link != links.end(); ++link) {
        if (link->durability <= 0) {
            link = links.erase(link);
            if (link == links.end()) { break; }
            link->start = previousEnd;
        }
        previousEnd = link->end;
    }

    // Decrement iframes counter
    for (Link& link : links) {
        if (link.iframesCounter > 0) { link.iframesCounter--; }
    }
}

bool Them::intersectsCircle(glm::vec2 center, float radius) {
    return glm::length(center - position) < (THEM_RADIUS+radius);
}

void Them::collisionCore(
        std::vector<Bullet>& bulletsVector,
        std::vector<Pop>& pops,
        unsigned int& score,
        int scoreIncrement,
        int damage
    ) {
    if (!bulletsVector.empty()) {
        // Intersections with them
        for (auto bullet = bulletsVector.begin(); bullet != bulletsVector.end(); ++bullet) {
            if (intersectsCircle(bullet->position, bullet->radius)) {
                dead = true;
                Pop pop = Pop(T_THEM_POP, position, velocity, THEM_POP_LIFETIME, THEM_POP_RADIUS);
                pops.push_back(pop);
            }
        }
        if (!links.empty()) {
            // Intersections with links
            for (auto bullet = bulletsVector.begin(); bullet != bulletsVector.end(); ++bullet) {
                for (auto link = links.begin(); link != links.end(); ++link) {
                    if (link->intersectsCircle(bullet->position, bullet->radius)) {
                        if (link->hit(damage)) {
                            bullet->hit();
                            score += scoreIncrement;
                        }
                    }
                }
            }
            // Erase bullets if needed
            for (auto bullet = bulletsVector.begin(); bullet != bulletsVector.end(); ++bullet) {
                if (bullet->durability <= 0) {
                    Pop pop = Pop((popType) bullet->type, bullet->position, bullet->velocity);
                    bullet = bulletsVector.erase(bullet);
                    pops.push_back(pop);
                    if (bullet == bulletsVector.end()) { break; }
                }
            }
        }
    }
}