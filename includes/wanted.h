#ifndef WANTED_H
# define WANTED_H

# include "SDLX/SDLX.h"

# define WINDOW_NAME "Wanted !"
# define WINDOW_X SDL_WINDOWPOS_CENTERED
# define WINDOW_Y SDL_WINDOWPOS_CENTERED
# define WINDOW_H 500
# define WINDOW_W 500
# define MAX_SPRITE 100

typedef void(*movement)(SDLX_Sprite *, SDLX_Time);

typedef struct	t_entity
{
	SDLX_Sprite		sprite;
	int				faction;
	movement		move_fn;
}	entity; 

typedef struct t_maser
{
	entity 			*entities;
	entity 			wanted;
	int 			sprite_count;
	int				level;
	double			timer;

	SDLX_Display	*display;
}	master;


master *game_init(void);
int 	game_loop(void *data);
void	move_left(SDLX_Sprite *sprite, SDLX_Time time);

#endif