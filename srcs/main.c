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
    return 1;
}

int main()
{
    SDLX_Display    *display;
    master          *game_master;

    SDLX_Start(
        WINDOW_NAME,
        WINDOW_X,
        WINDOW_Y,
        WINDOW_H,
        WINDOW_W,
        0
    );
    display = SDLX_Display_Get();
    game_master = game_init();
    while(1)
    {
        SDLX_Render_Reset(display);
        SDLX_RenderQueue_FlushAll();
        SDLX_InputLoop();
        SDLX_Input_Update();
        SDLX_TimedLoop(game_loop, game_master);
        SDLX_RenderAll(display);
        SDL_RenderPresent(display->renderer);
        SDLX_CapFPS();
    }
}