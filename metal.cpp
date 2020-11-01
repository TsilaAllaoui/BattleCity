#include "metal.h"

Metal::Metal()
{

}

Metal::Metal(int a,int b,SDL_Surface *p_screen)
{
    pos.x = a;
    pos.y = b;
    pos.w = 20;
    pos.h = 20;
    sprite = IMG_Load("./data/images/metal.png");
    state = 0;
    explo_frame=0;
    is_exploding=0;
    screen = p_screen;
}

void Metal::draw()
{
    if (is_exploding)
    {
    SDL_Surface *explosion;
    SDL_Rect tmp;
    explosion = IMG_Load("./data/images/boom.png");
    if (explo_frame<=32)
       {
            tmp.h = pos.h;
            tmp.w = pos.w;
            tmp.x = explo_frame;
            tmp.y = 0;
            SDL_BlitSurface(explosion,&tmp,screen,&pos);
            SDL_Delay(10);
            explo_frame+=16;
       }
       if (explo_frame > 32)
       {
           is_exploding = 0;
           state = 1;
           pos.x = rand()%885-900;
           pos.y = rand()%885-900;
       }
    }
    else
    SDL_BlitSurface(sprite,NULL,screen,&pos);
}

void Metal::destroy(SDL_Surface *ecran)
{
    is_exploding = 1;
}

int Metal::get_state()
{
    return state;
}

SDL_Rect Metal::get_coordinate()
{
	return pos;
}

