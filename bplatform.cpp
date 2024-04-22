#include "bplatform.h"

void BreakingPlatform::start_breaking(){
        if(breakingStatus < FOURTH){
            breakingStatus = FOURTH;
        }
}

void BreakingPlatform :: draw(Window* window) {
    Rectangle dst_rect(Point(x - PLATFORM_WIDTH / 2.0, y - PLATFORM_HEIGHT / 2.0), PLATFORM_WIDTH, PLATFORM_HEIGHT);
    switch(breakingStatus){
        case FOURTH:
            dst_rect.x = x - BPLATFORM_WIDTH_4 / 2.0;
            dst_rect.y = y - BPLATFORM_HEIGHT_4 / 2.0;
            dst_rect.w = BPLATFORM_WIDTH_4;
            dst_rect.h = BPLATFORM_HEIGHT_4;
            break;
        default:
            break;
    }
     window->draw_img("assets/pics/bplatform" + std :: to_string(breakingStatus) + ".png", dst_rect);
}

void BreakingPlatform :: vertical_move() {
    y += UP_SCREEN_RATE;
}