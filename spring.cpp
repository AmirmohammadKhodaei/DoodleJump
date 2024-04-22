#include "spring.h"

void Spring :: draw(Window* window) {
    Rectangle dst_rect(Point(x - SPRING_WIDTH / 2.0, y - SPRING_HEIGHT / 2.0), SPRING_WIDTH, SPRING_HEIGHT);
    window->draw_img("assets/pics/spring.png", dst_rect);
}

void Spring :: vertical_move() {
    y += UP_SCREEN_RATE;
}