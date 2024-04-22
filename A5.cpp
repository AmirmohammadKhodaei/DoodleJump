#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <ctime>
#include <cstdlib>
#include "rsdl.hpp"
using namespace std;

#define BACKGROUND_WIDTH              640.0
#define BACKGROUND_HEIGHT             1024.0
#define PLATFORM_WIDTH                120.0
#define PLATFORM_HEIGHT               37.0
#define ENEMY_WIDTH                   138.0
#define ENEMY_HEIGHT                  184.0
#define SPRING_WIDTH                  56.0
#define SPRING_HEIGHT                 45.0
#define CHARACTER_WIDTH               124.0
#define CHARACTER_HEIGHT              120.0
#define DELTA_T                       0.02
#define BOARD_DISTANCE                4.0
#define MPF_SPEED                     200.0
#define UP_SCREEN                     50.0
#define CHARACTER_N_LEFT_URL          "assets/pics/leftN.png"
#define CHARACTER_N_RIGHT_URL         "assets/pics/rightN.png"
#define CHARACTER_J_RIGHT_URL         "assets/pics/rightJ.png"
#define CHARACTER_J_LEFT_URL          "assets/pics/leftJ.png"
#define BPLATFORM_URL_1               "assets/pics/bplatform1.png"
#define BPLATFORM_URL_2               "assets/pics/bplatform2.png"
#define BPLATFORM_URL_3               "assets/pics/bplatform3.png"
#define BPLATFORM_URL_4               "assets/pics/bplatform4.png"
#define BPLATFORM_HEIGHT_4            64.0
#define BPLATFORM_WIDTH_4             114.0
#define CHARACTER_SPEED              700.0
#define GRAVITY                       1900.0
#define CHARACTER_F_SPEED             -300.0
#define UP_SCREEN_RATE                4.0

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
        string imageURL = CHARACTER_N_RIGHT_URL;
        int score = 0;
};

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
    string Score = to_string(score);
    window->show_text(Score, Point(20.0, 5.0), BLUE ,"FreeSans.ttf",36);
}

class Platform {
    public :
        Platform(double x, double y){
            setx(x);
            sety(y);
        }
        void setx(double xc) {x = xc;}
        void sety(double yc) {y = yc;}
        void setURL(string newURL){fileURL = newURL;}
        double getx() {return x;}
        double gety() {return y;}
        void draw(Window* window);
        bool is_on_screen();
        void vertical_move();
    private :
        double x, y;
        string fileURL = "assets/pics/platform.png";
};

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

void MovingPlatform :: draw(Window* window) {
    Rectangle dst_rect(Point(x - PLATFORM_WIDTH / 2.0, y - PLATFORM_HEIGHT / 2.0), PLATFORM_WIDTH, PLATFORM_HEIGHT);
    window->draw_img("assets/pics/mplatform.png", dst_rect);
}

void MovingPlatform :: move() {
    double leftCornerx = x - (PLATFORM_WIDTH / 2);
    double rightCornerx = x + (PLATFORM_WIDTH / 2);
    if (leftCornerx < BOARD_DISTANCE) {
        vx = MPF_SPEED;
    }
    if (BACKGROUND_WIDTH - rightCornerx < BOARD_DISTANCE) {
        vx = (-1) * MPF_SPEED;
    }
    horizontal_move();
}

void MovingPlatform :: vertical_move() {
    y += UP_SCREEN_RATE;
}

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
        string imgURL = BPLATFORM_URL_1;
        int breakingStatus = FIRST;
};

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
     window->draw_img("assets/pics/bplatform" + to_string(breakingStatus) + ".png", dst_rect);
}

void BreakingPlatform :: vertical_move() {
    y += UP_SCREEN_RATE;
}

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

void Enemy :: draw(Window* window) {
    Rectangle dst_rect(Point(x - ENEMY_WIDTH / 2.0, y - ENEMY_HEIGHT / 2.0), ENEMY_WIDTH, ENEMY_HEIGHT);
    window->draw_img("assets/pics/enemy.png", dst_rect);
}

void Enemy :: vertical_move() {
    y += UP_SCREEN_RATE;
}

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

void Spring :: draw(Window* window) {
    Rectangle dst_rect(Point(x - SPRING_WIDTH / 2.0, y - SPRING_HEIGHT / 2.0), SPRING_WIDTH, SPRING_HEIGHT);
    window->draw_img("assets/pics/spring.png", dst_rect);
}

void Spring :: vertical_move() {
    y += UP_SCREEN_RATE;
}

void update(Window* window, vector<MovingPlatform> &movingPlatforms, vector<Platform> &platforms, GameCharacter &character,
 vector<Spring> &springs, vector<Enemy> &enemies, vector<BreakingPlatform> &breakingPlatforms, bool &isTheEnd);

void draw(Window* window, vector<MovingPlatform> &movingPlatforms ,vector<Platform> &platforms ,
vector<BreakingPlatform> &bPlatforms,vector<Enemy> &enemies ,vector<Spring> &springs , GameCharacter &character, bool &isTheEnd);

void readMap(vector <Platform> &platforms, vector <MovingPlatform> &movingPlatforms, vector <Enemy> &enemies, 
vector <BreakingPlatform> &breakingPlatforms, vector <Spring> &springs, int &numOfEntities, double &maxY);

void start_moving(vector <Platform> &platforms, vector <MovingPlatform> &movingPlatforms, vector <Enemy> &enemies, 
vector <BreakingPlatform> &breakingPlatforms, vector <Spring> &springs , GameCharacter &character);

int main() {
    double maxY = 0.0;
    bool isTheEnd = false;
    vector <Platform> platforms;
    vector <MovingPlatform> movingPlatforms;
    vector <BreakingPlatform> breakingPlatforms;
    vector <Enemy> enemies;
    vector <Spring> springs;
    GameCharacter character;
    int numOfEntities = 0;
    Window* window = new Window(BACKGROUND_WIDTH, BACKGROUND_HEIGHT, "doodle jump");

    readMap(platforms,movingPlatforms,enemies,breakingPlatforms,springs,numOfEntities,maxY);

    while (true){
        update(window, movingPlatforms, platforms, character, springs, enemies,breakingPlatforms, isTheEnd);
        draw(window, movingPlatforms, platforms, breakingPlatforms, enemies, springs , character, isTheEnd);
        delay(1000 * DELTA_T);
    }
    return 0;
}

void readMap(vector <Platform> &platforms, vector <MovingPlatform> &movingPlatforms, vector <Enemy> &enemies, 
vector <BreakingPlatform> &breakingPlatforms, vector <Spring> &springs, int &numOfEntities, double &maxY){
    double x=0.0, y=0.0;
    string entity;
    ifstream newfile ("map.txt",ios::in);
    if (!(newfile)) {
        exit(1);
    }
    newfile >> numOfEntities;
    while (newfile >> x >> y >> entity) {
        if (y > maxY) maxY = y;
        if (entity == "platform"){
            Platform platform((double)x , (double)(BACKGROUND_HEIGHT - y));
            platforms.push_back(platform);
        }
        if (entity == "mplatform") {
            MovingPlatform mPlatform((double)x ,(double)(BACKGROUND_HEIGHT - y));
            movingPlatforms.push_back(mPlatform);
        }
        if (entity == "bplatform"){
            BreakingPlatform bplatform(x , BACKGROUND_HEIGHT - y);
            breakingPlatforms.push_back(bplatform);
        }
        if (entity == "enemy") {
            Enemy enemy(x , BACKGROUND_HEIGHT - y);
            enemies.push_back(enemy);
        }
        if (entity == "spring") {
            Spring spring(x , BACKGROUND_HEIGHT - y);
            springs.push_back(spring);
        }
    }

}

void draw(Window* window, vector<MovingPlatform> &movingPlatforms ,vector<Platform> &platforms ,
vector<BreakingPlatform> &bPlatforms,vector<Enemy> &enemies ,vector<Spring> &springs,GameCharacter &character , bool &isTheEnd) {
    window->clear();
    
    
    if(!isTheEnd){
        window->draw_img("assets/pics/background.png");
        character.show_score(window);
        for (int i = 0; i < movingPlatforms.size(); i++) {
           if (movingPlatforms[i].is_on_screen()) {
                movingPlatforms[i].draw(window);
         }
      }
       for(int i = 0 ; i < platforms.size() ; i++){
         if(platforms[i].is_on_screen()){
              platforms[i].draw(window);
           }
        }
        for(int i = 0 ; i < bPlatforms.size() ; i++){
            if(bPlatforms[i].is_on_screen()){
                bPlatforms[i].draw(window);
            }
        }
        for(int i = 0 ; i < enemies.size() ; i++){
            if(enemies[i].is_on_screen()){
                enemies[i].draw(window);
            }
        }
        for(int i = 0  ; i < springs.size() ; i++){
            if(springs[i].is_on_screen()){
                springs[i].draw(window);
            }
        }
        character.draw(window);
    }
    
    if (isTheEnd) {
        window -> draw_img("assets/pics/Finish.png",Rectangle(Point(0 , 512-180),BACKGROUND_WIDTH , 359));
        string finalScore = to_string(character.get_score());
        window -> show_text(finalScore, Point(BACKGROUND_WIDTH / 2.0, BACKGROUND_HEIGHT/2.0), BLUE, "FreeSans.ttf", 36);
    }
    window->update_screen();
}

void update(Window* window, vector<MovingPlatform> &movingPlatforms, vector<Platform> &platforms, GameCharacter &character,
 vector<Spring> &springs, vector<Enemy> &enemies, vector<BreakingPlatform> &breakingPlatforms, bool &isTheEnd) {
    while (window->has_pending_event()) {

        Event e = window->poll_for_event();
        
        switch(e.get_type()) {
        case Event :: EventType :: QUIT:
            exit(0);
            break;
        case Event::KEY_PRESS:
           if(isTheEnd){
                exit(0);
            }
            switch(e.get_pressed_key()){
                case 'a':
                case 'A':
                    character.horizontal_move(GameCharacter::LEFT);
                    break;
                case 'd':
                case 'D':
                    character.horizontal_move(GameCharacter::RIGHT);
                    break;
            }
            break;
        case Event::KEY_RELEASE:
            switch(e.get_pressed_key()){
                case 'a':
                case 'A':
                case 'D':
                case 'd':
                    character.horizontal_move(GameCharacter::NORMAL);
                    break;
            }
            break;
        }
    }
    if(!isTheEnd){
        if((character.gety() - CHARACTER_HEIGHT) > BACKGROUND_HEIGHT) {
            isTheEnd = true;
        }
        for (int i = 0; i < movingPlatforms.size(); i++) {
            if (movingPlatforms[i].is_on_screen()){
                movingPlatforms[i].move();
            }
        }
        for(int i = 0 ; i < movingPlatforms.size() ; i++){
            if(character.isOnEntity(movingPlatforms[i].gety() , movingPlatforms[i].getx() , GameCharacter :: PLATFORM)){
            character.jump();
            }
        }
        for(int i = 0; i < platforms.size() ; i++){
        if(character.isOnEntity(platforms[i].gety() , platforms[i].getx(), GameCharacter :: PLATFORM)){
            character.jump();
            }
        }
        for(int i = 0; i < springs.size() ; i++){
        if(character.isOnEntity(springs[i].gety() , springs[i].getx(), GameCharacter :: SPRING)){
            character.jump(2.0 * CHARACTER_F_SPEED);
            }
        }
        for(int i = 0 ; i < enemies.size() ; i++){
        if(character.isOnEntity(enemies[i].gety() , enemies[i].getx() , GameCharacter :: ENEMY)){
           isTheEnd = true;
            }
        }
        for(int i = 0 ; i < breakingPlatforms.size() ; i++){
        if(character.isOnEntity(breakingPlatforms[i].gety() , breakingPlatforms[i].getx() , GameCharacter::PLATFORM)){
            breakingPlatforms[i].start_breaking();
            }
        }
        character.start_moving();
        start_moving(platforms, movingPlatforms, enemies, breakingPlatforms, springs, character);
    }

}

void start_moving(vector <Platform> &platforms, vector <MovingPlatform> &movingPlatforms, vector <Enemy> &enemies, 
vector <BreakingPlatform> &breakingPlatforms, vector <Spring> &springs , GameCharacter &character) {
    if ((character.gety() < BACKGROUND_HEIGHT / 2.0) && (character.getvy() < 0.0)) {
        character.increase_score();
        for (int i = 0; i < platforms.size(); i++) {
            platforms[i].vertical_move();
        }
        for (int i = 0; i < movingPlatforms.size(); i++) {
            movingPlatforms[i].vertical_move();
        }
        for (int i = 0; i < breakingPlatforms.size(); i++) {
            breakingPlatforms[i].vertical_move();
        }
        for (int i = 0; i < springs.size(); i++) {
            springs[i].vertical_move();
        }
        for (int i = 0; i < enemies.size(); i++) {
            enemies[i].vertical_move();
        }
    } 
}
