#include "enemy.h"
#include "platform.h"
#include "mplatform.h"
#include "bplatform.h"
#include "spring.h"
#include "character.h"
#include <iostream>
#include <vector>
#include <fstream>
using namespace std;

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
        delay(5000*DELTA_T);
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