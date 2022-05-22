#ifndef WANTED_H
# define WANTED_H

# include "SDLX/SDLX.h"

# define WINDOW_NAME "Wanted !"
# define WINDOW_X SDL_WINDOWPOS_CENTERED
# define WINDOW_Y SDL_WINDOWPOS_CENTERED
# define WINDOW_H 500
# define WINDOW_W 500
# define MAX_SPRITE 35
# define MIN_SPRITE 5

# define SPRITE_W 32
# define SPRITE_H 32

# define MOVEMENT_TOTAL 4
# define SIGN (int [2]){1, -1}

typedef struct t_entity entity;

typedef void(*movement_fn)(entity *, SDLX_Time);

typedef struct	t_entity
{
	SDLX_Sprite		sprite;
	movement_fn		move;
	int				r;
	double			angle;
	int				dx;
	int				dy;
}	entity;


typedef struct t_maser
{
	entity 			*entities;
	entity 			wanted;

	int 			sprite_count;
	int				level;
	int				state;
	double			timer;

	SDLX_Display	*display;
}	master;


master *game_init(void);
int 	game_loop(void *data);
void 	reset_formations(master *game_master);
void 	game_next_level(master *game_master);


void wrap_position(entity *entity);
void move_circle(entity *self, SDLX_Time time);
void move_none(entity *self, SDLX_Time time);
void move_rand(entity *self, SDLX_Time time);
void move_sine(entity *self, SDLX_Time time);
void move_step(entity *self, SDLX_Time time);

#endif