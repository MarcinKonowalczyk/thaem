#ifndef DEFINES_HPP
#define DEFINES_HPP

#define WIPE_DURATION 30 // 30 // in frames
#define JUMP_DURATION 30 // 30

// max mouse distance for acceleration calculation
#define THEM_RADIUS 10 // Size of the them, in pixels
#define MAX_MOUSE_DISTANCE 100

#define SLOW_ACCELERATION 0.05f
#define FAST_ACCELERATION 0.3f

#define DASH_LENGTH 10 // pixels
#define LINK_WOBBLE 0.5f // disk radius pixels
#define LINK_IFRAMES 30 // frames

#define LINK_LIMIT 10
#define BULLET_LIMIT 20

// Levels
#define LEVEL1_SPAWN_INTERVAL 120 // 120 // frames
#define LEVEL1_SCORE_REQUIREMENT 0 // 100

#define LEVEL2_SPAWN_INTERVAL 30 // 120 // frames
#define LEVEL2_SCORE_REQUIREMENT 0 // 400

#define LEVEL3_SPAWN_INTERVAL 45 // 120 // frames
#define LEVEL3_SCORE_REQUIREMENT 1000 // 500


// Bullet constants
#define BLACK_BULLET_RADIUS 10 // pixels
#define BLUE_BULLET_RADIUS 20 // pixels
#define RED_BULLET_RADIUS 30 // pixels

#define BLACK_BULLET_DRAG 0.01f
#define BLUE_BULLET_DRAG 0.02f
#define RED_BULLET_DRAG 0.1f

#define BLACK_BULLET_SCORE 20
#define BLUE_BULLET_SCORE 10
#define RED_BULLET_SCORE 30

#define BLUE_BULLET_MOUSE_ATTRACT 0.05f
#define BLUE_BULLET_FRIENDLY_REPELL 0.1f

#define RED_BULLET_THEM_ATTRACT 0.1f
#define RED_BULLET_FRIENDLY_REPELL 0.1f

#define LINK_DURABILITY 2
#define DURABILITY_INDICATOR_SIZE 5 // pixels
#define DURABILITY_INDICATOR_SPACING 7 // pixels

#endif /* DEFINES_HPP */
