#include "wanted.h"

void move_left(SDLX_Sprite *sprite, SDLX_Time time)
{
	if (sprite->dst->x + sprite->dst->w <= 0)
		sprite->dst->x = WINDOW_W;
	sprite->dst->x -= 1 * time.delta_time;
}