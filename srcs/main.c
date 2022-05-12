#include "../includes/wanted.h"

int main()
{
    SDLX_Display *display;
    SDLX_Sprite sprite;
    SDL_Texture *tex;
    // SDLX_RenderQueue *queue;

    SDLX_Start(
        WINDOW_NAME,
        WINDOW_X,
        WINDOW_Y,
        WINDOW_H,
        WINDOW_W,
        0
    );
    display = SDLX_Display_Get();
    tex = SDLX_Texture_Load("assets/circle.png", display);
    SDLX_Sprite_Create(&sprite, 0, tex);
    sprite.src = NULL;
    sprite.dst = NULL;
    // SDLX_Background_Set()
    SDLX_RenderQueue_Push(&sprite);
    // // queue = SDLX_RenderQueue_Get(0);
    while(1)
    {
        SDLX_Render_Reset(display->renderer);
        SDLX_InputLoop();
        SDLX_RenderAll(display);
        SDL_RenderPresent(display->renderer);
    }
}