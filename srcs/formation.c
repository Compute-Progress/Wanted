#include "wanted.h"


//Wraps sprite to toher side of the screen
void correct_position(entity *entity)
{

	if (entity->sprite.dst->x >= WINDOW_W - entity->sprite.dst->w / 5)
		entity->sprite.dst->x = 0;
	if (entity->sprite.dst->y >= WINDOW_H - entity->sprite.dst->h / 5)
		entity->sprite.dst->y = 0;
	if (entity->sprite.dst->x + entity->sprite.dst->w - entity->sprite.dst->w / 4 < 0)
		entity->sprite.dst->x = WINDOW_W - entity->sprite.dst->w;
	if (entity->sprite.dst->y + entity->sprite.dst->h - entity->sprite.dst->h / 4 < 0)
		entity->sprite.dst->y = WINDOW_H - entity->sprite.dst->h;
}

void move_circle(entity *self, SDLX_Time time)
{
	self->sprite.dst->x = round(SDL_sin(self->angle * M_PI / 180) * self->r) + self->dx;
	self->sprite.dst->y = round(SDL_cos(self->angle * M_PI / 180) * self->r) + self->dy;

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
	correct_position(self);
	self->angle += 1 * time.delta_time;
	++i;
}

void move_rand(entity *self, SDLX_Time time)
{
	self->sprite.dst->x += self->dx;
	self->sprite.dst->y += self->dy;

	// Not using correct_position,instead, bounces sprite off the edge of the screen
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
	correct_position(self);
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
	// vice versa for gap y
	if (!count)
		return;

	orientation = rand() % 2;
	move_index = rand() % 3;

	gap_x = (WINDOW_W / count);
	gap_y = (WINDOW_H / count);
	// Gap should be at least the width and a half of a sprite
	if (gap_x <= SPRITE_W + SPRITE_W / 2)
		gap_x = SPRITE_W + SPRITE_W / 2;
	if (gap_y <= SPRITE_H + SPRITE_H / 2)
		gap_y = SPRITE_H + SPRITE_H / 2;
	
	gap_x *= orientation;
	gap_y *= (orientation ^ 1);
	i = 0;
	x = rand() % (WINDOW_W - 50) + 50;
	y = rand() % (WINDOW_H - 50) + 50;

	// Dx inverse of dy (if dx = 0, dy = 1 etc)
	dx = rand() % 2;
	dy = dx ^ 1;
	while (i < count)
	{
		entities[i].sprite._dst.x = x;
		entities[i].sprite._dst.y = y;
		entities[i].move = moves[move_index];
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
		entities[i].angle = i;
		// 				 	Direction 	  * 	Speed
		entities[i].dx = SIGN[rand() % 2] * ((rand() % 2) + 1);
		entities[i].dy = SIGN[rand() % 2] * ((rand() % 2) + 1);
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
	long random_num;

	SDLX_Time time;
	init_pos inits[3] = {
		make_circle,
		make_line,
		make_rand
	};
	
	i = 0;
	time = SDLX_Time_Get();

	srand(SDL_GetTicks());
	game_master->level++;
	game_master->sprite_count = MIN(MIN_SPRITE * game_master->level, MAX_SPRITE - 1);

	while(i < game_master->sprite_count)
	{
		random_num = rand() % (MIN(MIN_SPRITE * game_master->level,(MAX_SPRITE - 1) / MIN_SPRITE)) + 1;
		inits[rand() % 3](&game_master->entities[i], random_num);
		i += random_num;
	}
	random_num = rand() % game_master->sprite_count;
	game_master->wanted.sprite._dst = game_master->entities[random_num].sprite._dst;
	game_master->wanted.move = game_master->entities[random_num].move;
	game_master->wanted.angle = game_master->entities[random_num].angle;
	game_master->wanted.dx = game_master->entities[random_num].dx;
	game_master->wanted.dy = game_master->entities[random_num].dy;
	// SDL_Log("HERE IS WANTED BEFORE %d %d", game_master->wanted.sprite.dst->x, game_master->wanted.sprite.dst->y);
	// SDL_Log("OFFSET %d %d %d %d", game_master->wanted.dy, game_master->wanted.dx,   game_master->wanted.sprite.dst->w,   game_master->wanted.sprite.dst->w);
	
	//										Direction       *	    offset size 	*		axis
	game_master->wanted.sprite.dst->x += (SIGN[rand() % 2]) * (((rand() % 100) + 50) * game_master->wanted.dy);
	game_master->wanted.sprite.dst->y += (SIGN[rand() % 2]) * (((rand() % 100) + 50) * game_master->wanted.dx);
	correct_position(&game_master->wanted);
	// SDL_Log("HERE IS WANTED AFTER %d %d", game_master->wanted.sprite.dst->x, game_master->wanted.sprite.dst->y);
	// SDL_Log("HERE IS WANTED COPY %d %d",  game_master->entities[random_num].sprite.dst->x,
	game_master->entities[random_num].sprite.dst->y);
	game_master->wanted.r = game_master->entities[random_num].r;
	game_master->wanted.r += (SIGN[rand() % 2])  * 20;


}

// 1 : 4 dir
// 2 : 8 dir

// 1 : 4 dir
// 2 : 8 dir