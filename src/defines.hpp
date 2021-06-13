#ifndef DEFINES_HPP
#define DEFINES_HPP

#define WIPE_DURATION 5 // 30 // in frames
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

#define LEVEL2_SPAWN_INTERVAL 30 // 30 // frames
#define LEVEL2_SCORE_REQUIREMENT 0 // 400

#define LEVEL3_SPAWN_INTERVAL 45 // 45 // frames
#define LEVEL3_SCORE_REQUIREMENT 0 // 800

#define LEVEL4_SPAWN_INTERVAL 30 // 120 // frames
#define LEVEL4_SCORE_REQUIREMENT 0 // 800
#define LEVEL4_RED_LIMIT 3;

#define LEVEL5_SPAWN_INTERVAL 45 // 120 // frames
#define LEVEL5_SCORE_REQUIREMENT 0 // 800
#define LEVEL5_BLUE_LIMIT 4
#define LEVEL5_RED_LIMIT 4
#define LEVEL5_DRAG_MULTIPLIER 0.3f

#define LEVEL6_SPAWN_INTERVAL 30 // 120 // frames
#define LEVEL6_SCORE_REQUIREMENT 100 // 800

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

#define RED_BULLET_THEM_ATTRACT 0.15f
#define RED_BULLET_FRIENDLY_REPELL 0.8f

#define LINK_DURABILITY 2
#define DURABILITY_INDICATOR_SIZE 5 // pixels
#define DURABILITY_INDICATOR_SPACING 7 // pixels

#endif /* DEFINES_HPP */
