#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 450
#define BACKGROUND_COLOR 255, 255, 255, 255

#include <sstream>
#include <SDL.h>
#include <unistd.h>

int main(){
    // event handling
    bool quit = false;
    SDL_Event event;

    // init SDL
    SDL_Init(SDL_INIT_VIDEO);

    // hints
    SDL_SetHint(SDL_HINT_RENDER_VSYNC, "1");
    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "2");

    // window and renderer
    SDL_Window * window = SDL_CreateWindow("Anima",SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WINDOW_WIDTH, WINDOW_HEIGHT, 0);
    SDL_Renderer * renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    SDL_SetRenderDrawColor(renderer, BACKGROUND_COLOR);

    // fps
    Uint32 fps_last_update = SDL_GetTicks();
    Uint32 fps_current;
    Uint32 fps_frames = 0;

    // game loop
    while (!quit) {

        // fps calculation
        fps_frames++;
        if (fps_last_update < SDL_GetTicks() - 1000) {
            fps_last_update = SDL_GetTicks();
            fps_current = fps_frames;
            fps_frames = 0;
        }

        // fps display
        std::stringstream ss;
        ss <<" FPS: " << fps_current;
        SDL_SetWindowTitle(window, ss.str().c_str());

        // clear buffer
        SDL_RenderClear(renderer);

        // event handling
        SDL_PollEvent(&event);
        switch (event.type) {
            case SDL_QUIT:
                quit = true;
                break;
        }

        // rendering
        SDL_RenderPresent(renderer);

        // hardcoded fps limiter
        usleep(16000);
    }

    // cleanup SDL
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
