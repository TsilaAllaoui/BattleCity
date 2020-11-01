#include "bullet.h"

Bullet::Bullet()
{
    active = false;
    direction = UP;
    pos.x = 0;
    pos.y = 0;
    pos.h = 5;
    pos.w = 5;
    blit_pos.w = 5;
    blit_pos.h = 5;
    blit_pos.x = 0;
    blit_pos.y = 0;
    speed = 3;
    sprite = IMG_Load("./data/images/bullet.png");
}

Bullet::Bullet(int a,int b,SDL_Surface *p_screen,int way,vector <Brick> *p_brick,vector <Metal> *p_metal,Trophy *p_trophy)
{
    active = true;
    direction = way;
    pos.h = 5;
    pos.w = 5;
    blit_pos.w = 5;
    blit_pos.h = 5;
    blit_pos.x = 0;
    blit_pos.y = 0;
    speed = 3;
    sprite = IMG_Load("./data/images/bullet.png");
    screen = p_screen;
    add(a,b,way);
    brick = p_brick;
    metal = p_metal;
    trophy = p_trophy;
}

void Bullet::move()
{
    if (active)
    {
        SDL_Rect pos_trophy = trophy->get_coordinate();
        if (check_collision(pos, pos_trophy))
        {
            active = false;
            trophy->destroy();
        }
        if (brick->size() >= 0)
        for (int i=0; i<brick->size();i++)
        {
            SDL_Rect tmp = (*brick)[i].get_coordinate();
            if (check_collision(pos, tmp))
            {
                active = false;
                (*brick)[i].destroy();
            }
        }
        if (metal->size() >= 0)
        for (int i=0; i<metal->size();i++)
        {
            SDL_Rect tmp = (*metal)[i].get_coordinate();
            if (check_collision(pos, tmp))
            {
                active = false;
            }
        }
        if( pos.y > 0 && direction == UP)
            pos.y -= speed;
        else if( pos.y < HEIGHT && direction == DOWN)
            pos.y += speed;
        else if( pos.x > 0 && direction == LEFT)
            pos.x -= speed;
        else if( pos.y < WIDTH && direction == RIGHT)
            pos.x += speed;
        else active = false;
    }
}

void Bullet::draw()
{
    if (active)
    {
        if (direction == UP)
            blit_pos.x = 5;
        else if (direction == DOWN)
            blit_pos.x = 0;
        else if (direction == LEFT)
            blit_pos.x = 15;
        else if (direction == RIGHT)
            blit_pos.x = 10;
        SDL_BlitSurface(sprite,&blit_pos,screen,&pos);
    }
}
void Bullet::add(int x,int y,int way)
{
    if (way == UP)
    {
        pos.x = x + 14;
        pos.y = y;
        direction = UP;
    }
    else if (way == DOWN)
    {
        pos.x = x + 14;
        pos.y = y + 32;
        direction = DOWN;
    }
    if (way == LEFT)
    {
        pos.x = x;
        pos.y = y + 14 ;
        direction = LEFT;
    }
    if (way == RIGHT)
    {
        pos.x = x + 32;
        pos.y = y + 14;
        direction = RIGHT;
    }
}

bool Bullet::get_state()
{
    return active;
}

void Bullet::set_state(bool value)
{
    active = value;
}

SDL_Rect Bullet::get_coordinate()
{
    return pos;
}
