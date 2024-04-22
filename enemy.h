#ifndef ENEMY_H
#define ENEMY_H
#include "rsdl.hpp"
#define ENEMY_HEIGHT                  184.0
#define BACKGROUND_HEIGHT             1024.0
#define ENEMY_WIDTH                   138.0
#define UP_SCREEN_RATE                4.0

class Enemy {
    public :
        Enemy(double x , double y){
            setx(x);
            sety(y);
        }
        void setx(double xc) {x = xc;}
        void sety(double yc) {y = yc;}
        double getx() {return x;}
        double gety() {return y;}
        void draw(Window* window);
        bool is_on_screen(){return ((y - ENEMY_HEIGHT < BACKGROUND_HEIGHT)&&(y > 0.0));}
        void vertical_move();
    private :
        double x, y;
};

#endif