#ifndef TROPHY_H
#define TROPHY_H

#include "defs.h"

class Trophy
{
    private:
        SDL_Rect pos;
        SDL_Surface *sprite, *screen;
        bool is_alive;
    public:
        Trophy();
        Trophy(int a,int b, SDL_Surface *p_screen);
        void draw();
        void destroy();
        bool get_status();
        SDL_Rect get_coordinate();
};

#endif // TROPHY_H
