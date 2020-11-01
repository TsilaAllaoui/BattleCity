#include "trophy.h"

Trophy::Trophy()
{

}

Trophy::Trophy(int a,int b, SDL_Surface *p_screen)
{
    pos.x = a;
    pos.y = b;
    pos.h = 32;
    pos.w = 32;
    sprite = IMG_Load("./data/images/trophy.png");
    is_alive = true;
    screen = p_screen;
}

void Trophy::draw()
{
    if (is_alive)
    {
        SDL_Rect tmp;
        tmp.h = 32;
        tmp.w = 32;
        tmp.x = 0;
        tmp.y = 0;
        SDL_BlitSurface(sprite,&tmp,screen,&pos);
    }
    else if (!is_alive)
    {
        SDL_Rect tmp;
        tmp.h = 32;
        tmp.w = 32;
        tmp.x = 33;
        tmp.y = 0;
        SDL_BlitSurface(sprite,&tmp,screen,&pos);
    }
}

void Trophy::destroy()
{
    is_alive = false;
}

bool Trophy::get_status()
{
    return is_alive;
}

SDL_Rect Trophy::get_coordinate()
{
    return pos;
}
