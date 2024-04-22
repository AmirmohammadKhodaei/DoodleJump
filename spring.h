#ifndef SPRING_H
#define SPRING_H
#include "rsdl.hpp"
#define SPRING_HEIGHT                 45.0
#define SPRING_WIDTH                  56.0
#define BACKGROUND_HEIGHT             1024.0
#define UP_SCREEN_RATE                4.0

class Spring {
    public :
        Spring(double x, double y){
            setx(x);
            sety(y);
        }
        void setx(double xc) {x = xc;}
        void sety(double yc) {y = yc;}
        double getx() {return x;}
        double gety() {return y;}
        void draw(Window* window);
        bool is_on_screen(){return ((y - SPRING_HEIGHT < BACKGROUND_HEIGHT)&&(y > 0.0));}
        void vertical_move();
    private :
        double x, y;
};

#endif