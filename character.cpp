#include "character.h"

void GameCharacter :: start_moving(){
    x += vx * DELTA_T;
    double dy = 0.0;
    double tempVy = vy;
    vy += GRAVITY * DELTA_T;
    dy = (0.5*(vy + tempVy) + v0y) * DELTA_T;
    y += dy;
}

void GameCharacter :: draw(Window* window) {
    if(x > BACKGROUND_WIDTH){x = -CHARACTER_WIDTH;}
    if(x + CHARACTER_WIDTH < 0){x = BACKGROUND_WIDTH;}
    if(y - CHARACTER_HEIGHT < 0){y = CHARACTER_HEIGHT;}
    Rectangle dst_rect(Point(x-CHARACTER_WIDTH/2.0,y-CHARACTER_HEIGHT), CHARACTER_WIDTH, CHARACTER_HEIGHT);
    window->draw_img(imageURL, dst_rect);
}

void GameCharacter :: horizontal_move(int side){
    switch(side){
        case RIGHT:
            imageURL = CHARACTER_N_RIGHT_URL;
            vx = CHARACTER_SPEED;
        break;

        case LEFT:
            imageURL = CHARACTER_N_LEFT_URL;
            vx = -CHARACTER_SPEED;
        break;
        
        case NORMAL:
            vx=0.0;
        break;
    }
    
}

void GameCharacter :: show_score(Window* window) {
    std :: string Score = std :: to_string(score);
    window->show_text(Score, Point(20.0, 5.0), BLUE ,"FreeSans.ttf",36);
}