#include <SDL/SDL.h>
#include "utility.h"
#include "defs.h"

bool check_collision(SDL_Rect box1, SDL_Rect box2)
{
	if ((box2.x >= box1.x + box1.w)
		|| (box2.x + box2.w <= box1.x)
		|| (box2.y >= box1.y + box1.h) || (box2.y + box2.h <= box1.y))
		return false;
	else
		return true;
}
