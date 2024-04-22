#ifndef PLATFORM_H
#define PLATFORM_H
#include "rsdl.hpp"
#include <string>
#define BACKGROUND_HEIGHT             1024.0
#define PLATFORM_WIDTH                120.0
#define PLATFORM_HEIGHT               37.0
#define UP_SCREEN_RATE                4.0


class Platform {
    public :
        Platform(double x, double y){
            setx(x);
            sety(y);
        }
        void setx(double xc) {x = xc;}
        void sety(double yc) {y = yc;}
        void setURL(std :: string newURL){fileURL = newURL;}
        double getx() {return x;}
        double gety() {return y;}
        void draw(Window* window);
        bool is_on_screen();
        void vertical_move();
    private :
        double x, y;
        std :: string fileURL = "assets/pics/platform.png";
};
#endif
