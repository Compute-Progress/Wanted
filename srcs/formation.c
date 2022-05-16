#include "wanted.h"


void move_circle(entity **entities, int count, SDLX_Time time)
{
	// if (sprite->dst->x + sprite->dst->w <= 0)
	// 	sprite->dst->x = WINDOW_W;
	// sprite->dst->x -= 1 * time.delta_time;
}

void move_none(entity **entities, int count, SDLX_Time time)
{
	int i;

	i = 0;
	while (i < count)
	{
		SDLX_RenderQueue_Push(&entities[i]->sprite);
		++i;
	}
}

void move_sine(entity **entities, int count, SDLX_Time time)
{

}

void move_rand(entity **entities, int count, SDLX_Time time)
{

}

void move_step(entity **entities, int count, SDLX_Time time)
{

}

void make_circle(entity **entities, int count)
{

}

void make_line(entity **entities, int count)
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
		entities[i]->sprite._dst.x = x;
		entities[i]->sprite._dst.y = y;
		x += gap_x;
		y += gap_y;
		++i;
	}
}

void make_rectangle(entity **entities, int count)
{

}

void make_rand(entity **entities, int count)
{

}


typedef void(*init_pos)(entity **, int);

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
	inits[1](&game->formations[index].contents, member_count);
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