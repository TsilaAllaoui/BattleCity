#include "oneplayer_game.h"

OP_Game::OP_Game(SDL_Surface *p_screen)
{
    srand(time(0));
    SDL_EnableKeyRepeat(10, 10);
    Mix_OpenAudio(22050,MIX_DEFAULT_FORMAT,2,4096);
    intro = Mix_LoadMUS("./data/sounds/intro.mp3");
    stage = IMG_Load("./data/images/stage.png");
    game_over = IMG_Load("./data/images/game_over.png");
    screen = p_screen;
    for (int i = 0; i < 10; i++)
        keys[i] = false;
    pos_game_over.x = WIDTH/2 - 15;
    pos_game_over.y = HEIGHT;
    trophy = Trophy(WIDTH/2-16,HEIGHT-32,screen);
}

OP_Game::~OP_Game()
{

}

void OP_Game::launch()
{
    read_level();
    load_level();
    show_level();
    player_one = Tank(screen,&brick,&metal,keys, &trophy);
    Mix_PlayMusic(intro,0);
    while (1)
    {
        fps_timer.start();
        get_input();
        SDL_FillRect(screen,NULL,SDL_MapRGB(screen->format, 0,0,0));
        for(int i=0; i < brick.size(); i++)
            if (!brick[i].get_state())
                brick[i].draw();
        for (int i=0; i < metal.size(); i++)
            if (!metal[i].get_state())
                metal[i].draw();
        trophy.draw();
        player_one.move();
        player_one.draw();
        if (!trophy.get_status())
        {
            SDL_BlitSurface(game_over,NULL,screen,&pos_game_over);
            if (pos_game_over.y > HEIGHT/2)
                pos_game_over.y -= 2;
            if (pos_game_over.y <= HEIGHT/2)
            {
                if (game_over_timer.get_time() > 20000)
                    break;
            }
        }
        SDL_Flip(screen);
        if (1000/60 > fps_timer.get_time())
            SDL_Delay(1000/60 - fps_timer.get_time());
    }
}

void OP_Game::read_level()
{
    ifstream level("./data/levels/level.txt");
    char c;
    for (int i=0; i<26; i++)
    {
        for (int j=0; j<26; j++)
        {
            level.get(c);
            if (c == '0')
                level_layout[i][j] = VOID;
            else if (c == '1')
                level_layout[i][j] = BRICK;
            else if (c == '2')
                level_layout[i][j] = METAL;
        }
    }
}

void OP_Game::load_level()
{
    for (int i=0; i<26; i++)
        for (int j=0; j<26; j++)
        {
            if (level_layout[i][j] == BRICK)
                brick.push_back(Brick(j*20,i*20,screen));
            else if (level_layout[i][j] == METAL)
                metal.push_back(Metal(j*20,i*20,screen));
        }
}

void OP_Game::show_level()
{
    SDL_BlitSurface(stage,NULL,screen,NULL);
    SDL_Flip(screen);
    SDL_Delay(250);
}

void OP_Game::get_input()
{
    SDL_Event event;
    SDL_PollEvent(&event);
    switch(event.type)
    {
        case SDL_QUIT:
            return;
        case SDL_KEYDOWN:
            {
                if (event.key.keysym.sym == SDLK_w)
                    keys[0] = true;
                if (event.key.keysym.sym == SDLK_s)
                    keys[1] = true;
                if (event.key.keysym.sym == SDLK_a)
                    keys[2] = true;
                if (event.key.keysym.sym == SDLK_d)
                    keys[3] = true;
                if (event.key.keysym.sym == SDLK_SPACE)
                    keys[4] = true;
                if (event.key.keysym.sym == SDLK_UP)
                    keys[5] = true;
                if (event.key.keysym.sym == SDLK_DOWN)
                    keys[6] = true;
                if (event.key.keysym.sym == SDLK_LEFT)
                    keys[7] = true;
                if (event.key.keysym.sym == SDLK_RIGHT)
                    keys[8] = true;
                if (event.key.keysym.sym == SDLK_RETURN)
                    keys[9] = true;
                if (event.key.keysym.sym == SDLK_l)
                    trophy.destroy();
                break;
            }
        case SDL_KEYUP:
            {
                if (event.key.keysym.sym == SDLK_w)
                    keys[0] = false;
                if (event.key.keysym.sym == SDLK_s)
                    keys[1] = false;
                if (event.key.keysym.sym == SDLK_a)
                    keys[2] = false;
                if (event.key.keysym.sym == SDLK_d)
                    keys[3] = false;
                if (event.key.keysym.sym == SDLK_SPACE)
                    keys[4] = false;
                if (event.key.keysym.sym == SDLK_UP)
                    keys[5] = false;
                if (event.key.keysym.sym == SDLK_DOWN)
                    keys[6] = false;
                if (event.key.keysym.sym == SDLK_LEFT)
                    keys[7] = false;
                if (event.key.keysym.sym == SDLK_RIGHT)
                    keys[8] = false;
                if (event.key.keysym.sym == SDLK_RETURN)
                    keys[9] = false;
                    break;
            }
    }
}
