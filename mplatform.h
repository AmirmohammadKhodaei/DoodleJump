#ifndef MPLATFORM_H
#define MPLATFORM_H
#include "rsdl.hpp"
#define PLATFORM_HEIGHT               37.0
#define BACKGROUND_HEIGHT             1024.0
#define MPF_SPEED                     200.0
#define DELTA_T                       0.02
#define PLATFORM_WIDTH                120.0
#define UP_SCREEN_RATE                4.0
#define BACKGROUND_WIDTH              640.0
#define BOARD_DISTANCE                4.0

class MovingPlatform {
    public :
        MovingPlatform(double x, double y){
            setx(x);
            sety(y);
        }
        void setx(double xc) {x = xc;}
        void sety(double yc) {y = yc;}
        double getx() {return x;}
        double gety() {return y;}
        void move();
        void draw(Window* window);
        bool is_on_screen(){return ((y - PLATFORM_HEIGHT <  BACKGROUND_HEIGHT) && (y > 0.0));}
        void vertical_move();
    private :
        double x, y, vx = MPF_SPEED;
        void horizontal_move() {
            double dx = 0;
            dx = vx * DELTA_T;
            x += dx;
        }
};

#endif
