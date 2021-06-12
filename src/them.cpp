// #include <glm/glm.hpp>

#include "them.hpp"
#include "defines.hpp"
#include "colors.hpp"
#include "interval_transforms.hpp"

#include <iostream>
#include <glm/gtc/random.hpp>

void DEBUB_printVec2(glm::vec2 vec2) {
    std::cout << vec2.x << " " << vec2.y << std::endl;
}

void Them::update(
    glm::vec2 mousePosition,
    float width, float height,
    bool rightMousePressed) {

    bool hasWaypoints = waypoints.size() > 0;

    for (glm::vec2& waypoint : waypoints ) {
        waypoint += glm::diskRand(0.5);
    }

    glm::vec2 waypoint;
    if (hasWaypoints and not rightMousePressed) {
        waypoint = waypoints[0];
    } else {
        waypoint = mousePosition;
    }

    glm::vec2 waypointVector = waypoint - position;
    float waypointDistance = glm::length(waypointVector);

    if (waypointDistance < THEM_RADIUS ) {
        if (hasWaypoints and not rightMousePressed) {
            waypoints.pop_front();
        } else {
            velocity = 0.9f*velocity + 0.1f*(0.01f*waypointVector);
        }
    }

    glm::vec2 acceleration = glm::vec2(0,0);

    acceleration += glm::diskRand(0.05);

    if (waypointDistance > 0 and hasWaypoints) {
        glm::vec2 waypointNormal = waypointVector / waypointDistance;
        float alpha = waypointDistance > MAX_MOUSE_DISTANCE ? 1.0 : waypointDistance/MAX_MOUSE_DISTANCE;
        acceleration += (rightMousePressed ? FAST_ACCELERATION : SLOW_ACCELERATION) * alpha * waypointNormal;
    }


    // Push back towards the play area
    if (position.x > width)  { acceleration += glm::vec2(-1.0, 0.0); }
    else if (position.x < 0) { acceleration += glm::vec2(+1.0, 0.0); }
    if (position.y > height) { acceleration += glm::vec2(0.0, -1.0); }
    else if (position.y < 0) { acceleration += glm::vec2(0.0, 1.0);  }

    velocity += acceleration;

    // Handle drag at the very end
    float velocityMagnitude = glm::length(velocity);
    if (velocityMagnitude > 0) {
        glm::vec2 velocityNormal = velocity / velocityMagnitude;
        float dragMagnitude = 0.01 * velocityMagnitude * velocityMagnitude;
        if (waypointDistance < 40) {
            dragMagnitude *= 10;
        }
        velocity -= dragMagnitude * velocityNormal;
    }

    position += velocity;
};

void Them::draw(
    piksel::Graphics& g,
    glm::vec2 mousePosition,
    bool rightMousePressed) {
    g.push();
    bool hasWaypoints = waypoints.size() > 0;

    // Draw path
    g.strokeWeight(2);
    glm::vec2 drawPosition = position;
    int lineCounter = 0;
    for (glm::vec2& waypoint : waypoints) {
        if (lineCounter == 0) {
            if (rightMousePressed) {
                g.stroke(BLACK); g.fill(BLACK);
            } else {
                g.stroke(LINES_B); g.fill(LINES_B);
            }
        } else if (lineCounter == 1) {
            if (rightMousePressed) {
                g.stroke(BLACK); g.fill(BLACK);
            } else {
                g.stroke(LINES_R); g.fill(LINES_R);
            }
        } else {
            g.stroke(BLACK); g.fill(BLACK);
        }
        g.ellipse(waypoint.x, waypoint.y, 4,4);
        g.line(drawPosition.x, drawPosition.y, waypoint.x, waypoint.y);
        drawPosition = waypoint;
        lineCounter++;
    }

    // Dashed line to the mouse position
    if (rightMousePressed) { drawPosition = position; }
    glm::vec2 dashedVector = mousePosition - drawPosition;
    float dashedVectorLength = glm::length(dashedVector);
    if (rightMousePressed) {
        g.stroke(BLACK); g.fill(BLACK);
    } else {
        g.stroke(glm::mix(WHITE,BLACK,0.65)); g.fill(glm::mix(WHITE,BLACK,0.65));
    }
    if (dashedVectorLength < DASH_LENGTH) {
        g.line(drawPosition.x, drawPosition.y, mousePosition.x, mousePosition.y);
    } else {
        glm::vec2 dashedVectorNormal = dashedVector / dashedVectorLength;
        glm::vec2 dash = (float) DASH_LENGTH * dashedVectorNormal;
        int i = 0;
        for (; i < (dashedVectorLength/DASH_LENGTH-1); i += 2) {
            g.line(
                drawPosition.x + i*dash.x, drawPosition.y + i*dash.y,
                drawPosition.x + (i+1)*dash.x, drawPosition.y + (i+1)*dash.y
                );
        }
        // Draw the final little bit of the dashed line
        if (glm::fract(dashedVectorLength/(2*DASH_LENGTH)) < 0.5) {
            g.line(
                drawPosition.x + i*dash.x, drawPosition.y + i*dash.y,
                mousePosition.x, mousePosition.y
            );
        }
    }


    g.rectMode(piksel::DrawMode::CENTER);

    g.strokeWeight(2);
    g.stroke(BLACK);
    if (rightMousePressed) {
        g.fill(BLACK);
    } else {
        g.fill(WHITE);
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

void Them::addWaypoint(glm::vec2 position) {
    waypoints.push_back(position);
};

void Them::setPosition(float x, float y) {
    position = glm::vec2(x,y);
}