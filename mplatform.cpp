#include "mplatform.h"

void MovingPlatform :: draw(Window* window) {
    Rectangle dst_rect(Point(x - PLATFORM_WIDTH / 2.0, y - PLATFORM_HEIGHT / 2.0), PLATFORM_WIDTH, PLATFORM_HEIGHT);
    window->draw_img("assets/pics/mplatform.png", dst_rect);
}

void MovingPlatform :: move() {
    double leftCornerx = x - (PLATFORM_WIDTH / 2);
    double rightCornerx = x + (PLATFORM_WIDTH / 2);
    if (leftCornerx < BOARD_DISTANCE) {
        vx = MPF_SPEED;
    }
    if (BACKGROUND_WIDTH - rightCornerx < BOARD_DISTANCE) {
        vx = (-1) * MPF_SPEED;
    }
    horizontal_move();
}

void MovingPlatform :: vertical_move() {
    y += UP_SCREEN_RATE;
}