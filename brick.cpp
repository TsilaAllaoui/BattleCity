#include "brick.h"

Brick::Brick()
{
    pos.x = -900;
    pos.y = -900;
    pos.w = 20;
    pos.h = 20;
    sprite = IMG_Load("./data/images/brick.png");
    state = false;
    explo_frame=0;
    is_exploding=false;
}

Brick::Brick(int a,int b,SDL_Surface *p_screen)
{
    pos.x = a;
    pos.y = b;
    pos.w = 20;
    pos.h = 20;
    sprite = IMG_Load("./data/images/brick.png");
    state = false;
    explo_frame=0;
    is_exploding=false;
    screen = p_screen;
}

void Brick::draw()
{
    if (is_exploding)
    {
    SDL_Surface *explosion;
    SDL_Rect tmp;
    explosion = IMG_Load("./data/images/boom.png");
    if (explo_frame<=40)
       {
            tmp.h = 20;
            tmp.w = 16;
            tmp.x = explo_frame;
            tmp.y = 0;
            SDL_BlitSurface(explosion,&tmp,screen,&pos);
            SDL_Delay(10);
            explo_frame+=20;
       }
       if (explo_frame > 40)
       {
           is_exploding = 0;
           state = true;
           pos.x = rand()%885-900;
           pos.y = rand()%885-900;
       }
    }
    else
    {
        SDL_BlitSurface(sprite,NULL,screen,&pos);
    }
}

void Brick::destroy()
{
    is_exploding = true;
}

bool Brick::get_state()
{
    return state;
}

SDL_Rect Brick::get_coordinate()
{
	return pos;
}
