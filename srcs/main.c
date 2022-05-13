#include "../includes/wanted.h"

int simple_loop(void *data)
{
    SDLX_Sprite *sprite;
    static int go = 1;

    sprite = data;
    if (sprite->dst->x < 0 )
        go = 1;
    if (sprite->dst->x > WINDOW_W)
        go = -1;
    (void)go;
    sprite->dst->x += go * SDLX_Time_Get().delta_time;
    // SDL_Log("DEltae time %d", SDLX_Time_Get().delta_time);
    return 1;
}

int main()
{
    SDLX_Display *display;
    SDLX_Sprite sprite;
    SDL_Texture *tex;
    SDL_Rect dst;

    SDLX_Start(
        WINDOW_NAME,
        WINDOW_X,
        WINDOW_Y,
        WINDOW_H,
        WINDOW_W,
        0
    );
    dst.h = WINDOW_H / 10;
    dst.w = WINDOW_W / 10;
    dst.y = WINDOW_H / 2;
    display = SDLX_Display_Get();
    tex = SDLX_Texture_Load("assets/circle.png", display);
    SDLX_Sprite_Create(&sprite, 0, tex);
    sprite.src = NULL;
    sprite._dst = dst;

    while(1)
    {
        SDLX_Render_Reset(display);
        SDLX_RenderQueue_FlushAll();
        SDLX_InputLoop();
        SDLX_Input_Update();
        SDLX_TimedLoop(simple_loop, &sprite);
        SDLX_RenderQueue_Push(&sprite);
        SDLX_RenderAll(display);
        SDL_RenderPresent(display->renderer);
        SDLX_CapFPS();
    }
}