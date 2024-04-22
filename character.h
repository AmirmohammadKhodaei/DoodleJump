#ifndef CHARACTER_H
#define CHARACTER_H
#include "rsdl.hpp"
#include <string>

#define UP_SCREEN_RATE                4.0
#define CHARACTER_F_SPEED             -300.0
#define PLATFORM_WIDTH                120.0
#define PLATFORM_HEIGHT               37.0
#define SPRING_WIDTH                  56.0
#define SPRING_HEIGHT                 45.0
#define ENEMY_WIDTH                   138.0
#define ENEMY_HEIGHT                  184.0
#define CHARACTER_WIDTH               124.0
#define CHARACTER_HEIGHT              120.0
#define BACKGROUND_WIDTH              640.0
#define BACKGROUND_HEIGHT             1024.0
#define CHARACTER_N_RIGHT_URL         "assets/pics/rightN.png"
#define GRAVITY                       2500.0
#define DELTA_T                       0.02
#define CHARACTER_SPEED               800.0
#define CHARACTER_N_LEFT_URL          "assets/pics/leftN.png"

class GameCharacter {
    public :
        enum Sides{RIGHT , LEFT , NORMAL};
        enum EntityType{PLATFORM, SPRING, ENEMY};
        void setx(double xc) {x = xc;}
        void sety(double yc) {y = yc;}
        int getSide(){return side;}
        double getx() {return x;}
        double gety() {return y;}
        double getvy() {return vy;}
        int get_score(){return score;}
        void show_score(Window* window);
        void draw(Window *window);
        void horizontal_move(int side);
        void start_moving();
        void increase_score(){score += UP_SCREEN_RATE;}
        void decrease_score() {score -= UP_SCREEN_RATE;}
        void jump(double v = CHARACTER_F_SPEED) {vy = v;}  
        bool isOnEntity(double y, double x, int entityType) {
            bool checkx = false;
            bool checky = false;
            double entityWidth;
            double entityHeight;
            switch(entityType){
                case PLATFORM :
                    entityWidth = PLATFORM_WIDTH;
                    entityHeight = PLATFORM_HEIGHT;
                    break;
                case SPRING :
                    entityWidth = SPRING_WIDTH;
                    entityHeight = SPRING_HEIGHT;
                    break;
                case ENEMY :
                    entityWidth = ENEMY_WIDTH;
                    entityHeight = ENEMY_HEIGHT;
                    break;
            }
            if(this -> x - CHARACTER_WIDTH / 2.0 < x + entityWidth / 2.0){
                if(this -> x + CHARACTER_WIDTH / 2.0 > x - entityWidth /2.0){
                    checkx = true;
                }
            }
            if (this -> y - CHARACTER_HEIGHT < y) {
                if (this -> y > y - entityHeight){
                   checky = true;
                }
            }
            if (entityType == ENEMY) {
                return ((checkx) && (checky));
            }
            else {
                return ((vy > 0.0) && (checkx) && (checky));
            }
        }
    private :
        double x = BACKGROUND_WIDTH / 2.0 , y = BACKGROUND_HEIGHT / 2.0 + CHARACTER_HEIGHT, vx = 0.0, vy = 0.0, v0y = CHARACTER_F_SPEED;
        int side = Sides::NORMAL;
        std :: string imageURL = CHARACTER_N_RIGHT_URL;
        int score = 0;
};

#endif
