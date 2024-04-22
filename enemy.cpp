#include "enemy.h"

void Enemy :: draw(Window* window) {
    Rectangle dst_rect(Point(x - ENEMY_WIDTH / 2.0, y - ENEMY_HEIGHT / 2.0), ENEMY_WIDTH, ENEMY_HEIGHT);
    window->draw_img("assets/pics/enemy.png", dst_rect);
}

void Enemy :: vertical_move() {
    y += UP_SCREEN_RATE;
}