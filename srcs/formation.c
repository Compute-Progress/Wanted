#include "wanted.h"

void move_circle(entity *self, SDLX_Time time)
{
	self->sprite.dst->x = round(SDL_sin(self->angle * M_PI / 180) * self->r) + self->dx;
	self->sprite.dst->y = round(SDL_cos(self->angle * M_PI / 180) * self->r) + self->dy;

	// if (self->sprite.dst->x > WINDOW_W)
	// 	self->sprite.dst->x = 0;
	// else if (self->sprite.dst->x < 0)
	// if (self->sprite.dst->y > WINDOW_H)
	// 	self->sprite.dst->y = 0;
	// else if (self->sprite.dst->y < 0)
	// 	self->sprite.dst->y = WINDOW_H;
	self->angle += 1 * time.delta_time;
}

void move_none(entity *self, SDLX_Time time)
{
	return ;
}

void move_sine(entity *self, SDLX_Time time)
{
	int i;

	i = 0;
	if (self->dx)
	{
		self->sprite.dst->y += round((SDL_sin(self->angle * 0.1) * 5));
		self->sprite.dst->x += 1;
	}
	else
	{
		self->sprite.dst->x += round((SDL_sin(self->angle * 0.1) * 5));
		self->sprite.dst->y += 1;
	}
	if (self->sprite.dst->x > WINDOW_W)
		self->sprite.dst->x -= WINDOW_W;
	else if (self->sprite.dst->x + self->sprite.dst->w < 0)
		self->sprite.dst->x = WINDOW_W + self->sprite.dst->x;
	if (self->sprite.dst->y > WINDOW_H)
		self->sprite.dst->y -= WINDOW_H;
	else if (self->sprite.dst->y + self->sprite.dst->y < 0)
		self->sprite.dst->y = WINDOW_H + self->sprite.dst->y;
	self->angle += 1 * time.delta_time;
	++i;
}

void move_rand(entity *self, SDLX_Time time)
{
	self->sprite.dst->x += self->dx;
	self->sprite.dst->y += self->dy;

	if (self->sprite.dst->x + self->sprite.dst->w > WINDOW_W || 
		self->sprite.dst->x < 0)
		self->dx *= -1;
	if (self->sprite.dst->y + self->sprite.dst->h > WINDOW_H || 
		self->sprite.dst->y < 0)
		self->dy *= -1;
}

void move_step(entity *self, SDLX_Time time)
{
	self->sprite.dst->x += self->dx;
	self->sprite.dst->y += self->dy;
	if (self->sprite.dst->x > WINDOW_W)
		self->sprite.dst->x = 0;
	if (self->sprite.dst->y > WINDOW_H)
		self->sprite.dst->y = 0;
	if (self->sprite.dst->x + self->sprite.dst->w - self->sprite.dst->w / 4 < 0)
		self->sprite.dst->x = WINDOW_W;
	if (self->sprite.dst->y + self->sprite.dst->h - self->sprite.dst->h / 4 < 0)
		self->sprite.dst->y = WINDOW_H;
}

void make_circle(entity *entities, int count)
{
	int orientation;
	int move_index;
	int gap;
	int i;
	int dx;
	int dy;
	int radius;

	movement_fn moves[2] =
	{
		move_circle,
		move_none,
	};

	if (!count)
		return;
	
	orientation = rand() % 2;
	move_index = rand() % 2;
	gap = 360 / 4;
	i = 0;
	dx = WINDOW_W / ((rand() % 3) + 1);
	dy = WINDOW_H / ((rand() % 3) + 1);
	radius = (rand() % 100) + 50;
	while (i < count)
	{
		entities[i].move = moves[move_index];
		entities[i].angle = i * gap;
		entities[i].dx = rand() % (WINDOW_W / 2) + 100;
		entities[i].dy = rand() % (WINDOW_W / 2) + 100;
		entities[i].r = radius;
		entities[i].sprite._dst.x = SDL_sin((i * gap * M_PI) / 180) * radius + entities[i].dx;
		entities[i].sprite._dst.y = SDL_cos((i * gap * M_PI) / 180) * radius + entities[i].dy;
		++i;
	}
}

void make_line(entity *entities, int count)
{
	int orientation;
	int move_index;
	int gap_x;
	int gap_y;
	int i;
	int x;
	int y;
	int dx;
	int dy;
	int gap;

	movement_fn moves[3] =
	{
		move_rand,
		move_sine,
		move_step
	};
	// Sets gap x to window / count if oritention = 1 else 0
	// vice versa for gapy
	if (!count)
		return;

	orientation = rand() % 2;
	move_index = rand() % 3;
	gap_x = (WINDOW_W / count);
	gap_x = (WINDOW_H / count);
	if (gap_x < SPRITE_W  + SPRITE_W / 2)
		gap_x = SPRITE_W  + SPRITE_W;
	if (gap_y < SPRITE_H  + SPRITE_H / 2)
		gap_y = SPRITE_H  + SPRITE_H;
	
	gap_x *= orientation;
	gap_y *= (orientation ^ 1);
	i = 0;
	x = rand() % (WINDOW_W - 50) + 50;
	y = rand() % (WINDOW_H - 50) + 50;
	SDL_Log("INIT pos %d %d", x, y);
	dx = rand() % 2;
	dy = dx ^ 1;
	while (i < count)
	{
		if (x > WINDOW_W - 20)
			x -= WINDOW_W;
		if (x < 0)
			x *= -1;
		if (y > WINDOW_W - 20)
			y -= WINDOW_W;
		if (y < 0)
			y *= -1;
		entities[i].sprite._dst.x = x;
		entities[i].sprite._dst.y = y;
		// entities[i].move = moves[move_index];
		entities[i].move = move_sine;
		entities[i].angle = i;
		entities[i].dx = dx;
		entities[i].dy = dy;
		x += gap_x;
		y += gap_y;
		++i;
	}
}

void make_rand(entity *entities, int count)
{
	int i;
	int move_index;

	movement_fn moves[2] =
	{
		move_rand,
		move_none
	};

	if (!count)
		return;
	move_index = rand() % 2;
	i = 0;
	while (i < count)
	{
		entities[i].sprite._dst.x = (rand() % (WINDOW_W - 30)) + 30;
		entities[i].sprite._dst.y = (rand() % (WINDOW_H - 30)) + 30;
		if (entities[i].sprite._dst.x > WINDOW_W - 20)
			entities[i].sprite._dst.x -= WINDOW_W;
		if (entities[i].sprite._dst.x < 0)
			entities[i].sprite._dst.x *= -1;
		if (entities[i].sprite._dst.y > WINDOW_W - 20)
			entities[i].sprite._dst.y -= WINDOW_W;
		if (entities[i].sprite._dst.y < 0)
			entities[i].sprite._dst.y *= -1;
		entities[i].move = moves[move_index];
		// entities[i].move = move_rand;
		entities[i].angle = i;
		entities[i].dx = (rand() % 3) + 1;
		entities[i].dy = (rand() % 3) + 1;
		++i;
	}
}

typedef void(*init_pos)(entity *entities, int);

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
	game_master->level = 0;
	game_master->sprite_count = 0;
	game_master->timer = 0;
}


void game_next_level(master *game_master)
{
	int i;
	int start;
	int objCount;
	int remainder;
	long random_num;
	SDLX_Time time;
	init_pos inits[3] = {
		make_circle,
		make_line,
		make_rand
	};
	
	i = 0;
	start = 0;
	time = SDLX_Time_Get();

	srand(SDL_GetTicks());
	game_master->level++;
	objCount = MIN(MIN_SPRITE * game_master->level, MAX_SPRITE - 1);
	game_master->sprite_count = objCount;
	remainder = objCount;
	SDL_Log("HEre %d %d", objCount, game_master->level);
	while(i < remainder)
	{
	// 	SDL_Log("HEre %d", (MIN(MIN_SPRITE * game_master->level, MAX_SPRITE - 1)/ 4));
		random_num = rand() % (MIN(MIN_SPRITE * game_master->level,(MAX_SPRITE - 1) / MIN_SPRITE)) + 1;
		// make_line(&game_master->entities[start], 4);
		SDL_Log("Random is %ld", random_num);
		inits[rand() % 3](&game_master->entities[start], random_num);
		start += random_num;
		i += random_num;
	}
	// random_num = rand() % 4;
	game_master->sprite_count = objCount;
	random_num = rand() % objCount;
	game_master->wanted.sprite._dst = game_master->entities[random_num].sprite._dst;
	game_master->wanted.move = game_master->entities[random_num].move;
	game_master->wanted.angle = game_master->entities[random_num].angle;
	game_master->wanted.dx = game_master->entities[random_num].dx;
	game_master->wanted.dy = game_master->entities[random_num].dy;
	SDL_Log("HERE IS WANTED BEFORE %d %d", game_master->wanted.sprite.dst->x, game_master->wanted.sprite.dst->y);
	game_master->wanted.sprite.dst->x +=   game_master->wanted.sprite.dst->w * game_master->wanted.dy;
	game_master->wanted.sprite.dst->y +=   game_master->wanted.sprite.dst->h * game_master->wanted.dx;
	SDL_Log("OFFSET %d %d", game_master->wanted.dy, game_master->wanted.dx);
	// game_master->wanted.sprite.dst->x += (SIGN[rand() % 2]) * ((rand() % 50) + 50 * game_master->wanted.dy);
	// game_master->wanted.sprite.dst->y += (SIGN[rand() % 2]) * ((rand() % 50) + 50 * game_master->wanted.dx);
	SDL_Log("HERE IS WANTED AFTER %d %d", game_master->wanted.sprite.dst->x, game_master->wanted.sprite.dst->y);
	SDL_Log("HERE IS WANTED COPY %d %d",  game_master->entities[random_num].sprite.dst->x,
	game_master->entities[random_num].sprite.dst->y);
	game_master->wanted.r = game_master->entities[random_num].r;

	if (game_master->wanted.sprite.dst->x < 0)
		game_master->wanted.sprite.dst->x = 0;
	else if (game_master->wanted.sprite.dst->x >= WINDOW_W - SPRITE_W / 3)
		game_master->wanted.sprite.dst->x = WINDOW_W - game_master->wanted.sprite.dst->w;
	if (game_master->wanted.sprite.dst->y < 0)
		game_master->wanted.sprite.dst->y = 0;
	else if (game_master->wanted.sprite.dst->y >= WINDOW_H - SPRITE_H / 3)
		game_master->wanted.sprite.dst->y = WINDOW_H - game_master->wanted.sprite.dst->h;

	if (game_master->wanted.move == move_circle)
	{
		game_master->wanted.r += (SIGN[rand() % 2])  * 20;
	}
	SDL_Log("HERE IS WANTED AFTER %d %d", game_master->wanted.sprite.dst->x, game_master->wanted.sprite.dst->y);
	// //TODO Cap this so it doesnt go off screen
	// game_master->wanted.sprite.dst->x += 10;
	// game_master->wanted.sprite.dst->y += 10;
}

// 1 : 4 dir
// 2 : 8 dir

// 1 : 4 dir
// 2 : 8 dir