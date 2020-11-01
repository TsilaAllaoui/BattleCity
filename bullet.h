#ifndef BULLET_H
#define BULLET_H

#include "defs.h"

using namespace std;

class Bullet
{
    private:
        SDL_Surface *sprite, *screen;
        SDL_Rect pos, blit_pos;
        float speed;
        bool active;
        int direction;
        vector <Brick> *brick;
        vector <Metal> *metal;
        Trophy *trophy;
    public:
        Bullet();
        Bullet(int a,int b,SDL_Surface *p_screen,int way,vector <Brick> *p_brick,vector <Metal> *p_metal, Trophy *p_trophy);
        void move();
        void draw();
        void add(int x,int y,int way);
        void set_state(bool value);
        bool get_state();
        SDL_Rect get_coordinate(void);
};

#endif // SHOOT_H
