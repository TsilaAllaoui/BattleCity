#ifndef METAL_H
#define METAL_H

#include "defs.h"

class Metal
{
    private:
        SDL_Rect pos;
        SDL_Surface *sprite, *screen;
        int state,explo_frame,is_exploding;
    public:
        Metal();
        Metal(int a,int b,SDL_Surface *p_screen);
        void draw();
        void destroy(SDL_Surface *ecran);
        int get_state();
        SDL_Rect get_coordinate();
};

#endif // METAL_H
