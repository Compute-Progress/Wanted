#ifndef WANTED_H
# define WANTED_H

# include "SDLX/SDLX.h"

# define WINDOW_NAME "Wanted !"
# define WINDOW_X SDL_WINDOWPOS_CENTERED
# define WINDOW_Y SDL_WINDOWPOS_CENTERED
# define WINDOW_H 500
# define WINDOW_W 500
# define MAX_SPRITE 100

typedef struct t_maser
{
	SDLX_Sprite 	*sprites;
	SDLX_Sprite 	wanted;
	int 			sprite_count;
	int				level;
	double			timer;

	SDLX_Display	*display;
}	master;

master *game_init(void);
int 	game_loop(void *data);

#endif