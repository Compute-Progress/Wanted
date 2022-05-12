#include "SDLX/SDLX.h"

typedef struct _internal_Queues
{
	uint32_t count;
	SDLX_RenderQueue *queues;
}	_intern_Queues;

static _intern_Queues queues;

void SDLX_RenderQueues_Init()
{
	uint32_t i;

	i = 0;
	queues.queues = SDL_calloc(DEFAULT_QUEUES_COUNT, sizeof(SDLX_RenderQueue));
	while (i < DEFAULT_QUEUES_COUNT)
	{
		queues.queues[i].sprites = SDL_calloc(DEFAULT_QUEUE_SIZE, sizeof(SDLX_Sprite *));
		queues.queues[i].capacity = DEFAULT_QUEUE_SIZE;
		queues.queues[i].size = 0;
		++i;
	}
	queues.count = DEFAULT_QUEUES_COUNT;
} 


void 		SDLX_RenderAll(SDLX_Display *display)
{
	uint32_t i;
	uint32_t n;
	SDLX_RenderQueue *current;

	i = 0;
	while (i < queues.count)
	{
		current = &(queues.queues[i]);
		n = 0;
		while (n < current->size)
		{
			SDL_RenderCopyEx(
				display->renderer,
				current->sprites[n]->texture,
				current->sprites[n]->src,
				current->sprites[n]->dst,
				current->sprites[n]->angle,
				current->sprites[n]->center,
				current->sprites[n]->flip
			);
			++n;
		} 
		++i;
	}
}

void 		SDLX_RenderOne(uint32_t id);

void        SDLX_Render_Reset(SDLX_Display *display)
{
	SDL_RenderClear(display->renderer);
	SDL_SetRenderDrawColor(display->renderer, 0, 0, 0, 0);
}

void		SDLX_RenderQueue_Push(SDLX_Sprite *sprite)
{
	SDLX_RenderQueue *current;

	if (sprite->primary_Layer < queues.count)
	{
		current = &(queues.queues[sprite->primary_Layer]);
		if (current->size >= current->capacity)
		{
			current->capacity *= 2;
			current->sprites = realloc(current->sprites, current->capacity * sizeof(SDLX_Sprite *));
		}
		current->sprites[current->size] = sprite;
		current->size++;
	}
}

void		SDLX_RenderQueue_FlushAll()
{
	uint32_t i;

	i = 0;
	while (i < queues.count)
	{
		queues.queues[i].size = 0;
		++i;
	}
}

void        SDLX_RenderQueue_Flush(uint32_t id)
{
	if (queues.count < id)
		queues.queues[id].size = 0;
}

uint32_t    SDLX_RenderQueue_Create(SDL_bool isSorted);

SDLX_RenderQueue *SDLX_RenderQueue_Get(uint32_t id)
{
	if (id < queues.count)
		return &queues.queues[id];

	return NULL;
}