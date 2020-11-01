#ifndef TANK_H
#define TANK_H

#include "defs.h"

using namespace std;

class Metal;
class Brick;
class Bullet;
class Trophy;

class Tank
{
    private:
        SDL_Surface *sprite, *screen, *misc;
        SDL_Rect pos,blit_pos,flash_blit;
        bool is_appearing,is_invulnerable, *keys;
        int speed, anim_state, direction, appear_state, invulnerable_state;
        vector <Brick> *brick;
        vector <Metal> *metal;
        vector <Bullet> bullets;
        Timer invulnerable_t, appearing_t, barrier_t, flash_t, shoot_t;
        Trophy *trophy;
    public:
        Tank();
        Tank(SDL_Surface *p_screen, vector <Brick> *p_brick,vector <Metal> *p_metal, bool *p_keys, Trophy *trophy);
        void draw();
        void move();
        bool collision_up();
        bool collision_down();
        bool collision_left();
        bool collision_right();
};

#endif // TANK_H
