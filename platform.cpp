#include "platform.h"

bool Platform :: is_on_screen() {
    return ((y < BACKGROUND_HEIGHT) && (y > 0));
}

void Platform :: draw(Window* window) {
    Rectangle dst_rect(Point(x - PLATFORM_WIDTH / 2.0, y - PLATFORM_HEIGHT / 2.0), PLATFORM_WIDTH, PLATFORM_HEIGHT);
    window->draw_img(fileURL,dst_rect);
}

void Platform :: vertical_move() {
    y += UP_SCREEN_RATE;
}