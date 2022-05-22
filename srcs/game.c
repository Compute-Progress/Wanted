# include "wanted.h"

master *game_init(void)
{
	SDL_Rect dst;
	SDL_Texture *tex;
	SDL_Texture *tex2;
	master *game_master;
	int 	i;

	i = 0;
	game_master = SDL_calloc(1, sizeof(master));
	game_master->display = SDLX_Display_Get();
	game_master->entities = SDL_calloc(MAX_SPRITE + 1, sizeof(entity));
	tex = SDLX_Texture_Load("assets/circle.png", game_master->display);
	tex2 = SDLX_Texture_Load("assets/red_circle.png", game_master->display);
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
	game_master->sprite_count = 3; //TODO : Change this to the actual count and init in level selectx
	game_master->divide_count = 4;
	game_master->timer = 0.0;
	game_master->level = 1;
	reset_formations(game_master);
	game_next_level(game_master);
	SDL_Log("Init game");
	return game_master;
}


int collisions_loop(master *game_master)
{
	SDLX_Input input;
	int i;

	input = SDLX_Input_Get();
	i = 0;
	if (input.mouse_state == 2)
	{
		while (i < game_master->sprite_count)
		{
			if (SDL_PointInRect(&input.mouse, game_master->entities[i].sprite.dst))
			{
				return -1;
			}
			++i;
		}
		if (SDL_PointInRect(&input.mouse, game_master->wanted.sprite.dst))
		{
			game_next_level(game_master);
			return 1;
		}
	}
	return 0;
}

int game_loop(void *data)
{
	SDLX_Time	time;
	master		*game_master;

	int i;
	int	collision;

	time = SDLX_Time_Get();
	game_master = data;
	i = 0;

	game_master->timer += time.delta_time / 100.0;
	collision = collisions_loop(game_master);
	if (collision != 0)
	{

		SDL_Log("Something happened %d", collision);
		return 1;
	}

	game_master->timer += collision * 10;
	
	while (i < game_master->sprite_count)
	{
		if (game_master->entities[i].move)
		{
			game_master->entities[i].move(&game_master->entities[i],  time);
			SDLX_RenderQueue_Push(&game_master->entities[i].sprite);
		}
		++i;
	}
	game_master->wanted.move(&game_master->wanted,  time);
	SDLX_RenderQueue_Push(&game_master->wanted.sprite);

	// SDLX_Sprite_Print(&game_master->sprites[0]);
	// SDL_Log("Timer %f", game_master->timer);

	return 1;
}