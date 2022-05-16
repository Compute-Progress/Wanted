#ifndef WANTED_H
# define WANTED_H

# include "SDLX/SDLX.h"

# define WINDOW_NAME "Wanted !"
# define WINDOW_X SDL_WINDOWPOS_CENTERED
# define WINDOW_Y SDL_WINDOWPOS_CENTERED
# define WINDOW_H 500
# define WINDOW_W 500
# define MAX_SPRITE 100
# define FORMATION_CAP 50

# define STATIC 1
# define RANDOM 2
# define SHAPE 3
# define LINE 4
# define MOVEMENT_TOTAL 4


typedef struct	t_entity
{
	SDLX_Sprite		sprite;
	int				faction;
	int				angle;
}	entity;

typedef void(*movement_fn)(entity **, int, SDLX_Time);
typedef struct t_divide
{
	int 			amount;
	entity			*contents[FORMATION_CAP];
	movement_fn 	movement_fn;

	int				x;
	int 			y;
}	divide;

typedef struct t_maser
{
	entity 			*entities;
	entity 			wanted;
	divide			formations[4];

	int				divide_count;
	int 			sprite_count;
	int				level;
	double			timer;

	SDLX_Display	*display;
}	master;


master *game_init(void);
int 	game_loop(void *data);
void 	create_formation(master *game, int member_count, int index);
void 	reset_formations(master *game_master);

#endif