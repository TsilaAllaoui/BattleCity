#ifndef GAME_H
#define GAME_H

#include "defs.h"
#include "oneplayer_game.h"

class Game
{
    private:
        SDL_Surface *screen;
        int game_mode;
    public:
        Game();
        void run();
        void begin();
        void end();
        void pause();
};

#endif // GAME_H
