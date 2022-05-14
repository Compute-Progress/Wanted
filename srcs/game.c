# include "wanted.h"

master *game_init(void)
{
	SDL_Rect dst;
	SDL_Texture *tex;
	master *game_master;
	int 	i;

	i = 0;
	game_master = SDL_calloc(1, sizeof(master));
	game_master->display = SDLX_Display_Get();
	game_master->sprites = SDL_calloc(MAX_SPRITE, sizeof(SDLX_Sprite));
	tex = SDLX_Texture_Load("assets/circle.png", game_master->display);
	while (i < MAX_SPRITE)
	{
		SDLX_Sprite_Create(&(game_master->sprites[i]), 1, tex);
		dst.h = WINDOW_H / 10;
		dst.w = WINDOW_W / 10;
		dst.y = WINDOW_H / 2;
		game_master->sprites[i].src = NULL;
		game_master->sprites[i]._dst = dst;
		++i;
	}

	return game_master;
}

// void game_next_level(master *game_master)
// {
// 	// game_master->level += 1;
	
// }

int game_loop(void *data)
{
	SDLX_Time	time;
	master		*game_master;

	static int go = 1;

	time = SDLX_Time_Get();
	game_master = data;
	game_master->timer += time.delta_time;

    if (game_master->sprites[0].dst->x < 0 )
        go = 1;
    if (game_master->sprites[0].dst->x > WINDOW_W)
        go = -1;
    game_master->sprites[0].dst->x += go * time.delta_time;
	SDLX_Sprite_Print(&game_master->sprites[0]);
	SDLX_RenderQueue_Push(&(game_master->sprites[0]));

	return 1;
}