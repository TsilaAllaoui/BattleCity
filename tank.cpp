#include "tank.h"

Tank::Tank()
{

}

Tank::Tank(SDL_Surface *p_screen,vector <Brick> *p_brick,vector <Metal> *p_metal,bool *p_keys, Trophy *p_trophy)
{
    sprite = IMG_Load("./data/images/1P_tank.png");
    misc = IMG_Load("./data/images/misc.png");
    screen = p_screen;
    pos.x = WIDTH/2-92;
    pos.y = HEIGHT-32;
    pos.w = 32;
    pos.h = 32;
    blit_pos.h = 32;
    blit_pos.w = 32;
    blit_pos.x = 64;
    blit_pos.y = 0;
    brick = p_brick;
    metal = p_metal;
    is_appearing = true;
    is_invulnerable = true;
    speed = 1;
    keys = p_keys;
    anim_state = 0;
    appear_state = 0;
    invulnerable_state = 0;
    direction = UP;
    trophy = p_trophy;
}


void Tank::draw()
{
    if (!is_appearing)
    {
        if (anim_state == 0)
        {
            if (direction == UP || direction == LEFT)
                blit_pos.x = 64;
            else if (direction == DOWN || direction == RIGHT)
                blit_pos.x = 0;
            SDL_BlitSurface(sprite,&blit_pos,screen,&pos);
        }
        else if (anim_state)
        {
            if (direction == UP || direction == LEFT)
                blit_pos.x = 96;
            else if (direction == DOWN || direction == RIGHT)
                blit_pos.x = 32;
            SDL_BlitSurface(sprite,&blit_pos,screen,&pos);
        }
        if (is_invulnerable)
        {
            if (!invulnerable_t.get_state())
                invulnerable_t.start();
            if (!barrier_t.get_state())
                barrier_t.start();
            flash_blit.w = 32;
            flash_blit.h = 32;
            flash_blit.y = 0;
            if (invulnerable_state == 0)
            {
                flash_blit.x = 0;
                SDL_BlitSurface(misc,&flash_blit,screen,&pos);
                if (barrier_t.get_time() > 50)
                {
                    barrier_t.stop();
                    invulnerable_state = 1;
                }
            }
            else if (invulnerable_state == 1)
            {
                flash_blit.x = 32;
                SDL_BlitSurface(misc,&flash_blit,screen,&pos);
                if (barrier_t.get_time() > 50)
                {
                    barrier_t.stop();
                    invulnerable_state = 0;
                }
            }
            if (invulnerable_t.get_time() > 2000)
            {
                is_invulnerable = false;
                invulnerable_t.stop();
            }
        }
    }
    else
    {
        if (!flash_t.get_state())
            flash_t.start();
        if (!appearing_t.get_state())
            appearing_t.start();
        flash_blit.w = 32;
        flash_blit.h = 32;
        flash_blit.y = 0;
        if (appear_state == 0)
        {
            flash_blit.x = 64;
            SDL_BlitSurface(misc,&flash_blit,screen,&pos);
            if (flash_t.get_time() > 50)
            {
                flash_t.stop();
                appear_state = 1;
            }
        }
        else if (appear_state == 1)
        {
            flash_blit.x = 96;
            SDL_BlitSurface(misc,&flash_blit,screen,&pos);
            if (flash_t.get_time() > 50)
            {
                flash_t.stop();
                appear_state = 2;
            }
        }
        else if (appear_state == 2)
        {
            flash_blit.x = 128;
            SDL_BlitSurface(misc,&flash_blit,screen,&pos);
            if (flash_t.get_time() > 50)
            {
                flash_t.stop();
                appear_state = 0;
            }
        }
        if (appearing_t.get_time() > 2000)
        {
            is_appearing = false;
            appearing_t.stop();
        }
    }
    if (bullets.size() >= 0)
    for (int i=0; i<bullets.size(); i++)
        bullets[i].draw();
}

void Tank::move()
{
    if (!is_appearing)
    {
        if (keys[0])
        {
            if (!collision_up() && pos.y-speed > 0)
            {
                pos.y -= speed;
                if (anim_state == 1)
                    anim_state = 0;
                else if (anim_state == 0)
                    anim_state = 1;
            }
            blit_pos.y = 0;
            direction = UP;
        }
        else if (keys[1])
        {
            if (!collision_down() && pos.y+speed+32 < HEIGHT)
            {
                pos.y +=speed;
                if (anim_state == 1)
                    anim_state = 0;
                else if (anim_state == 0)
                    anim_state = 1;
            }
            blit_pos.y = 0;
            direction = DOWN;
        }
        else if (keys[2])
        {
            if (!collision_left() && pos.x-speed > 0)
            {
                pos.x -=speed;
                if (anim_state == 1)
                    anim_state = 0;
                else if (anim_state == 0)
                    anim_state = 1;
            }
            blit_pos.y = 32;
            direction = LEFT;
        }
        else if (keys[3])
        {
            if (!collision_right() && pos.x + speed + 32 < WIDTH)
            {
                pos.x +=speed;
                if (anim_state == 1)
                    anim_state = 0;
                else if (anim_state == 0)
                    anim_state = 1;
            }
            blit_pos.y = 32;
            direction = RIGHT;
        }
        if (keys[4])
        {
            if (!shoot_t.get_state())
            {
                shoot_t.start();
                bullets.push_back(Bullet(pos.x,pos.y,screen,direction,brick,metal,trophy));
            }
            if (shoot_t.get_time() > 750)
               shoot_t.stop();
        }
    }
    if (bullets.size() >= 0)
    for (int i=0; i<bullets.size(); i++)
        bullets[i].move();
}

bool Tank::collision_up()
{
    SDL_Rect pos_brick,pos_metal,pos_enem, pos_trophy;
    pos_trophy.x = WIDTH/2-16;
    pos_trophy.y = HEIGHT-32;
    if (check_collision(pos, pos_trophy))
    {
        pos.y += 2;
        return true;
    }
    for (int i=0; i<brick->size(); i++)
    {
        pos_brick.x = (*brick)[i].get_coordinate().x;
        pos_brick.y = (*brick)[i].get_coordinate().y;
        pos_brick.h = (*brick)[i].get_coordinate().h;
        pos_brick.w = (*brick)[i].get_coordinate().w;
        if (pos.y - speed == pos_brick.y + pos_brick.h && ((pos.x >= pos_brick.x && pos.x<= pos_brick.x + pos_brick.w)
                ||((pos.x + pos.w >= pos_brick.x && pos.x + pos.w <= pos_brick.x + pos_brick.w))
                ||(pos_brick.x >= pos.x && pos_brick.x<= pos.x + pos.w)
                ||(pos_brick.x + pos_brick.w >= pos.x && pos_brick.x + pos_brick.w <= pos.x + pos.w)))
            return true;
    }
    for (int j=0; j<metal->size(); j++)
    {
        pos_metal.x = (*metal)[j].get_coordinate().x;
        pos_metal.y = (*metal)[j].get_coordinate().y;
        pos_metal.h = (*metal)[j].get_coordinate().h;
        pos_metal.w = (*metal)[j].get_coordinate().w;
        if (pos.y - speed == pos_metal.y + pos_metal.h && ((pos.x >= pos_metal.x && pos.x<= pos_metal.x + pos_metal.w)
                ||((pos.x + pos.w >= pos_metal.x && pos.x + pos.w <= pos_metal.x + pos_metal.w))
                ||(pos_metal.x >= pos.x && pos_metal.x<= pos.x + pos.w)
                ||(pos_metal.x + pos_metal.w >= pos.x && pos_metal.x + pos_metal.w <= pos.x + pos.w)))
            return true;
    }
//    for (int i=0; i<12; i++)
//    {
//        pos_enemy.x = enemy[i].get_coordinate().x;
//        pos_enemy.y = enemy[i].get_coordinate().y;
//        pos_enemy.h = enemy[i].get_coordinate().h;
//        pos_enemy.w = enemy[i].get_coordinate().w;
//        if (check_collision(pos_enemy,pos))
//            return true;
//    }
    return false;
}
bool Tank::collision_down()
{
    SDL_Rect pos_brick,pos_metal,pos_enemy,pos_trophy;
    pos_trophy.x = WIDTH/2-16;
    pos_trophy.y = HEIGHT-32;
    if (check_collision(pos, pos_trophy))
    {
        pos.y -= 2;
        return true;
    }
    for (int i=0; i<brick->size(); i++)
    {
        pos_brick.x = (*brick)[i].get_coordinate().x;
        pos_brick.y = (*brick)[i].get_coordinate().y;
        pos_brick.h = (*brick)[i].get_coordinate().h;
        pos_brick.w = (*brick)[i].get_coordinate().w;
        if (pos.y + pos.h + speed == pos_brick.y && ((pos.x >= pos_brick.x && pos.x<= pos_brick.x + pos_brick.w)
                ||((pos.x + pos.w >= pos_brick.x && pos.x + pos.w <= pos_brick.x + pos_brick.w))
                ||(pos_brick.x >= pos.x && pos_brick.x<= pos.x + pos.w)
                ||(pos_brick.x + pos_brick.w >= pos.x && pos_brick.x + pos_brick.w <= pos.x + pos.w)))
            return true;
    }
    for (int j=0; j<metal->size(); j++)
    {
        pos_metal.x = (*metal)[j].get_coordinate().x;
        pos_metal.y = (*metal)[j].get_coordinate().y;
        pos_metal.h = (*metal)[j].get_coordinate().h;
        pos_metal.w = (*metal)[j].get_coordinate().w;
        if (pos.y + pos.h + speed == pos_metal.y && ((pos.x >= pos_metal.x && pos.x<= pos_metal.x + pos_metal.w)
                ||((pos.x + pos.w >= pos_metal.x && pos.x + pos.w <= pos_metal.x + pos_metal.w))
                ||(pos_metal.x >= pos.x && pos_metal.x<= pos.x + pos.w)
                ||(pos_metal.x + pos_metal.w >= pos.x && pos_metal.x + pos_metal.w <= pos.x + pos.w)))
            return true;
    }
//    for (int i=0; i<12; i++)
//    {
//        pos_enemy.x = enemy[i].get_coordinate().x;
//        pos_enemy.y = enemy[i].get_coordinate().y;
//        pos_enemy.h = enemy[i].get_coordinate().h;
//        pos_enemy.w = enemy[i].get_coordinate().w;
//            if (check_collision(pos_enemy,pos))
//            return true;
//    }
    return false;
}
bool Tank::collision_left()
{
    SDL_Rect pos_brick,pos_metal,pos_enemy,pos_trophy;
    pos_trophy.x = WIDTH/2-16;
    pos_trophy.y = HEIGHT-32;
    if (check_collision(pos, pos_trophy))
    {
        pos.x += 2;
        return true;
    }
    for (int i=0; i<brick->size(); i++)
    {
        pos_brick = (*brick)[i].get_coordinate();
        if (pos.x - speed == pos_brick.x + pos_brick.w && ((pos.y >= pos_brick.y && pos.y<= pos_brick.y + pos_brick.h)
                ||((pos.y + pos.h >= pos_brick.y && pos.y + pos.h <= pos_brick.y + pos_brick.h))
                ||(pos_brick.y >= pos.y && pos_brick.y<= pos.y + pos.h)
                ||(pos_brick.y + pos_brick.h >= pos.y && pos_brick.y + pos_brick.h <= pos.y + pos.h)))
            return true;
    }
    for (int i=0; i<metal->size(); i++)
    {
        pos_metal.x = (*metal)[i].get_coordinate().x;
        pos_metal.y = (*metal)[i].get_coordinate().y;
        pos_metal.h = (*metal)[i].get_coordinate().h;
        pos_metal.w = (*metal)[i].get_coordinate().w;
        if (pos.x - speed == pos_metal.x + pos_metal.w && ((pos.y >= pos_metal.y && pos.y<= pos_metal.y + pos_metal.h)
                ||((pos.y + pos.h >= pos_metal.y && pos.y + pos.h <= pos_metal.y + pos_metal.h))
                ||(pos_metal.y >= pos.y && pos_metal.y<= pos.y + pos.h)
                ||(pos_metal.y + pos_metal.h >= pos.y && pos_metal.y + pos_metal.h <= pos.y + pos.h)))
            return true;
    }
//    for (int i=0; i<12; i++)
//    {
//        pos_enemy.x = enemy[i].get_coordinate().x;
//        pos_enemy.y = enemy[i].get_coordinate().y;
//        pos_enemy.h = enemy[i].get_coordinate().h;
//        pos_enemy.w = enemy[i].get_coordinate().w;
//        if (check_collision(pos_enemy,pos))
//            return true;
//    }
    return false;
}
bool Tank::collision_right()
{
    SDL_Rect pos_brick,pos_metal,pos_enemy,pos_trophy;
    pos_trophy.x = WIDTH/2-16;
    pos_trophy.y = HEIGHT-32;
    if (check_collision(pos, pos_trophy))
    {
        pos.x -= 2;
        return true;
    }
    for (int i=0; i<brick->size(); i++)
    {
        pos_brick.x = (*brick)[i].get_coordinate().x;
        pos_brick.y = (*brick)[i].get_coordinate().y;
        pos_brick.h = (*brick)[i].get_coordinate().h;
        pos_brick.w = (*brick)[i].get_coordinate().w;
        if (pos.x + pos.w + speed == pos_brick.x && ((pos.y >= pos_brick.y && pos.y<= pos_brick.y + pos_brick.h)
                ||((pos.y + pos.h >= pos_brick.y && pos.y + pos.h <= pos_brick.y + pos_brick.h))
                ||(pos_brick.y >= pos.y && pos_brick.y<= pos.y + pos.h)
                ||(pos_brick.y + pos_brick.h >= pos.y && pos_brick.y + pos_brick.h <= pos.y + pos.h)))
            return true;
    }
    for (int i=0; i<metal->size(); i++)
    {
        pos_metal.x = (*metal)[i].get_coordinate().x;
        pos_metal.y = (*metal)[i].get_coordinate().y;
        pos_metal.h = (*metal)[i].get_coordinate().h;
        pos_metal.w = (*metal)[i].get_coordinate().w;
        if (pos.x + pos.w + speed == pos_metal.x && ((pos.y >= pos_metal.y && pos.y<= pos_metal.y + pos_metal.h)
                ||((pos.y + pos.h >= pos_metal.y && pos.y + pos.h <= pos_metal.y + pos_metal.h))
                ||(pos_metal.y >= pos.y && pos_metal.y<= pos.y + pos.h)
                ||(pos_metal.y + pos_metal.h >= pos.y && pos_metal.y + pos_metal.h <= pos.y + pos.h)))
            return true;
    }
//    for (int i=0; i<12; i++)
//    {
//        pos_enemy.x = enemy[i].get_coordinate().x;
//        pos_enemy.y = enemy[i].get_coordinate().y;
//        pos_enemy.h = enemy[i].get_coordinate().h;
//        pos_enemy.w = enemy[i].get_coordinate().w;
//            if (check_collision(pos_enemy,pos))
//            return true;
//    }
    return false;
}
