#ifndef BRICK_H
#define BRICK_H

#include "defs.h"

class Brick
{
    private:
        SDL_Rect pos;
        SDL_Surface *sprite, *screen;
        int explo_frame;
        bool state,is_exploding;
    public:
        Brick();
        Brick(int a,int b,SDL_Surface *p_screen);
        void draw();
        void destroy();
        bool get_state();
        SDL_Rect get_coordinate();
};

#endif // BRICK_H
