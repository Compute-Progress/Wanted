#include "wanted.h"


void move_circle(divide *formation, SDLX_Time time)
{
	// if (sprite->dst->x + sprite->dst->w <= 0)
	// 	sprite->dst->x = WINDOW_W;
	// sprite->dst->x -= 1 * time.delta_time;
}

void move_none(divide *formation, SDLX_Time time)
{
	int i;

	i = 0;
	while (i < formation->amount)
	{
		SDLX_RenderQueue_Push(&formation->contents[i]->sprite);
		++i;
	}
}

void move_sine(divide *formation, SDLX_Time time)
{

}

void move_rand(divide *formation, SDLX_Time time)
{

}

void move_step(divide *formation, SDLX_Time time)
{
	int i;

	i = 0;
	while (i < formation->amount)
	{
		SDL_Log("Here %d", i);
		formation->contents[i]->sprite.dst->x += formation->x;
		formation->contents[i]->sprite.dst->y += formation->y;
		if (formation->contents[i]->sprite.dst->x > WINDOW_W)
			formation->contents[i]->sprite.dst->x = 0;
		if (formation->contents[i]->sprite.dst->y > WINDOW_H)
			formation->contents[i]->sprite.dst->y = 0;
		SDLX_RenderQueue_Push(&formation->contents[i]->sprite);
		++i;
	}
}

void make_circle(divide *formation, int count)
{

}

void make_line(divide *formation, int count)
{
	long gap_x;
	long gap_y;

	int orientation;
	int i;
	int x;
	int y;


	orientation = rand() % 1;

	// Sets gap x to window / count if oritention = 1 else 0
	// vice versa for gapy
	if (! count)
		return;
	// SDL_Log("HERE 1");
	gap_x = (WINDOW_W / count) * orientation;
	gap_y = (WINDOW_H / count) * (orientation ^ 1);
	// SDL_Log("HERE 2");
	i = 0;
	x = rand() % WINDOW_W;
	// SDL_Log("HERE 3");
	y = rand() % WINDOW_H;
	// SDL_Log("HERE 4");
	while (i < count)
	{
		formation->contents[i]->sprite._dst.x = x;
		formation->contents[i]->sprite._dst.y = y;
		x += gap_x;
		y += gap_y;
		++i;
	}
}

void make_rectangle(divide *formation, int count)
{

}

void make_rand(divide *formation, int count)
{

}


typedef void(*init_pos)(divide *, int);

void reset_formations(master *game_master)
{
	int i;
	divide *formation;

	i = 0;
	while (i < game_master->divide_count)
	{
		formation = &game_master->formations[i];
		formation->amount = 0;
		formation->movement_fn = NULL;
		formation->x = 0;
		formation->y = 0;
		++i;
	}
}

void create_formation(master *game, int member_count, int index)
{
	SDLX_Time time;

	time = SDLX_Time_Get();
	movement_fn fns[4] = {
		move_circle,
		move_rand,
		move_step,
		move_sine
	};

	init_pos inits[4] = {
		make_circle,
		make_line,
		make_rectangle,
		make_rand
	};

	// SDL_Log("Here");
	game->formations[index].amount = member_count;

	//Pick inital shape
	// inits[rand() % 4](&game->formations[index], member_count);
	inits[1](&game->formations[index], member_count);
	game->formations[index].x = rand() % 1;
	game->formations[index].y = rand() % 1;
	// choose movement
	// if (rand() % STATIC)// If not static, pick random movement function
	// {
	// 	fns[rand() % 3](&game->formations[index], member_count, time);
	// }
	// else
	// {
		game->formations[index].movement_fn = move_none;
	// }
}
// 1 : 4 dir
// 2 : 8 dir