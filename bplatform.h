#ifndef BPLATFORM_H
#define BPLATFORM_H
#include "rsdl.hpp"
#include <string>
#define PLATFORM_HEIGHT               37.0
#define PLATFORM_WIDTH                120.0
#define BACKGROUND_HEIGHT             1024.0
#define BPLATFORM_URL_1               "assets/pics/bplatform1.png"
#define BPLATFORM_HEIGHT_4            64.0
#define BPLATFORM_WIDTH_4             114.0
#define UP_SCREEN_RATE                4.0

class BreakingPlatform{
    public :
    enum BreakingStatus{FIRST = 1 , SECOND , THIRD , FOURTH};
        BreakingPlatform(double x, double y){
            setx(x);
            sety(y);
        }
        void setx(double xc) {x = xc;}
        void sety(double yc) {y = yc;}
        double gety(){return y;}
        double getx(){return x;}
        void draw(Window* window);
        bool is_on_screen(){return ((y - PLATFORM_HEIGHT <  BACKGROUND_HEIGHT)&&(y > 0.0));}
        void start_breaking();
        void vertical_move();
    private :
        int sampleSpeed = 0;
        double x, y;
        std :: string imgURL = BPLATFORM_URL_1;
        int breakingStatus = FIRST;
};

#endif
