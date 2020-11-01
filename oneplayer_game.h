#ifndef ONE_PLAYER_H
#define ONE_PLAYER_H

#include <SDL/SDL.h>
#include <cstdlib>
#include <vector>
#include <ctime>
#include <fstream>
#include "defs.h"

using namespace std;

class OP_Game
{
    private:
        SDL_Surface *screen , *game_over, *stage, *p_brick;
        Timer fps_timer,spawn_timer, game_over_timer;
        int level_layout[26][26];
        bool keys[10];
        Mix_Music *intro;
        SDL_Rect pos_game_over;
        vector <Brick> brick;
        vector <Metal> metal;
        Trophy trophy;
        Tank player_one;
    public:
        OP_Game(SDL_Surface *p_screen);
        ~OP_Game();
        void launch();
        void read_level();
        void load_level();
        void show_level();
        void get_input();
};

#endif // JEU_H

