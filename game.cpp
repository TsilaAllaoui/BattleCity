#include "game.h"

Game::Game()
{
    SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO);
    screen = SDL_SetVideoMode(WIDTH,HEIGHT,32,SDL_HWSURFACE | SDL_DOUBLEBUF);
    game_mode = ONEPLAYER;
}

void Game::run()
{
    begin();
    if (game_mode == ONEPLAYER)
        OP_Game(screen).launch();
    end();
}

void Game::pause()
{
    SDL_Event event;
    while (1)
    {
        SDL_WaitEvent(&event);
        if (event.type == SDL_KEYDOWN)
            return;
    }
}

void Game::begin()
{
    SDL_Surface *start,*tank;
    start = IMG_Load("./data/images/start.png");
    tank = IMG_Load("./data/images/1P_tank.png");
    SDL_Rect pos_start,pos_blit,pos_tank;
    pos_start.x = 0;
    pos_start.y = HEIGHT;
    SDL_Event event;
    do
    {
        SDL_PollEvent(&event);
        if (event.type == SDL_KEYDOWN)
        {
            pos_start.y = 0;
            SDL_BlitSurface(start,NULL,screen,&pos_start);
            SDL_Flip(screen);
            break;
        }
        pos_start.y--;
        SDL_BlitSurface(start,NULL,screen,&pos_start);
        SDL_Flip(screen);
    }
    while(pos_start.y > 0);
    pos_blit.h = 32;
    pos_blit.w = 32;
    pos_blit.y = 32;
    pos_tank.x = 125;
    int anim_state = 0;
    while (1)
    {
        SDL_BlitSurface(start,NULL,screen,NULL);
        SDL_Event event_game;
        SDL_PollEvent(&event_game);
        if (event_game.type == SDL_KEYDOWN)
        {
            if (event_game.key.keysym.sym == SDLK_DOWN)
                game_mode = TWOPLAYER;
            if (event_game.key.keysym.sym == SDLK_UP)
                game_mode = ONEPLAYER;
            if (event_game.key.keysym.sym == SDLK_SPACE && game_mode == ONEPLAYER)
                break;
            if (event_game.key.keysym.sym == SDLK_SPACE && game_mode == TWOPLAYER)
                break;
        }
        if (game_mode == ONEPLAYER)
        {
            pos_tank.y = 285;
            if (!anim_state)
            {
                pos_blit.x = 0;
                SDL_BlitSurface(tank,&pos_blit,screen,&pos_tank);
                anim_state = 1;
            }
            else if (anim_state)
            {
                pos_blit.x = 32;
                SDL_BlitSurface(tank,&pos_blit,screen,&pos_tank);
                anim_state = 0;
            }
            SDL_Flip(screen);
            SDL_Delay(60);
        }
        else if (game_mode == TWOPLAYER)
        {
            pos_tank.y = 317;
            if (!anim_state)
            {
                pos_blit.x = 0;
                SDL_BlitSurface(tank,&pos_blit,screen,&pos_tank);
                anim_state = 1;
            }
            else if (anim_state)
            {
                pos_blit.x = 32;
                SDL_BlitSurface(tank,&pos_blit,screen,&pos_tank);
                anim_state = 0;
            }
            SDL_Flip(screen);
            SDL_Delay(60);
        }
    }
}

void Game::end()
{
    SDL_Surface *end_screen;
    end_screen = IMG_Load("./data/images/end.png");
    SDL_BlitSurface(end_screen,NULL,screen,NULL);
    SDL_Flip(screen);
    SDL_Delay(5000);
}
