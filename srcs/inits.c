# include "wanted.h"

void reset_formations(master *game_master)
{
	int i;

	i = 0;
	while (i < game_master->sprite_count)
	{
		game_master->entities[i].angle = 0;
		game_master->entities[i].move = NULL;
		game_master->entities[i].dx = 0;
		game_master->entities[i].dy = 0;
		++i;
	}
	game_master->sprite_count = 0;
}


master *game_init(void)
{
	master *game_master;
	
	SDL_Rect dst;
	SDL_Texture *tex;
	SDL_Texture *tex2;

	int 	i;

	
	game_master = SDL_calloc(1, sizeof(master));
	game_master->display = SDLX_Display_Get();
	game_master->entities = SDL_calloc(MAX_SPRITE + 1, sizeof(entity));
	game_master->timer = 15.0;
	game_master->level = 0;
	game_master->state = 0;
	
	tex = SDLX_Texture_Load("assets/circle.png", game_master->display);
	tex2 = SDLX_Texture_Load("assets/red_circle.png", game_master->display);
	i = 0;
	
	while (i < MAX_SPRITE)
	{
		SDLX_Sprite_Create(&(game_master->entities[i].sprite), 1, tex);
		dst.h = WINDOW_H / 9;
		dst.w = WINDOW_W / 9;
		dst.y = WINDOW_H / 2;
		dst.x = 0;
		game_master->entities[i].sprite.src = NULL;
		game_master->entities[i].sprite._dst = dst;
		++i;
	}
	SDLX_Sprite_Create(&(game_master->wanted.sprite), 0, tex2);
	game_master->wanted.sprite._dst = dst;
	game_master->wanted.sprite.src = NULL;

	reset_formations(game_master);
	game_next_level(game_master);
	SDL_Log("Init game");
	return game_master;
}

void reset_game(master *game_master)
{
	game_master->timer = 15.0;
	game_master->level = 0;
	game_master->state = 0;
	reset_formations(game_master);
}
