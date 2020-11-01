#ifndef DEFS_H
#define DEFS_H

#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_mixer.h>
#include <vector>

#include "timer.h"
#include "brick.h"
#include "metal.h"
#include "trophy.h"
#include "tank.h"
#include "utility.h"
#include "bullet.h"

#define WIDTH 520
#define HEIGHT 520
#define MAX 50

enum {UP,DOWN,LEFT,RIGHT,KUP,KDOWN,KLEFT,KRIGHT,ONEPLAYER,TWOPLAYER,BRICK,METAL,VOID};

#endif // DEFS_H
