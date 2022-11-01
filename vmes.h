#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 450
#define BACKGROUND_COLOR 255, 255, 0, 255

#include <sstream>
#include <SDL.h>
#include <SDL_image.h>

#include "drivers/gpu.h"
#include "drivers/controller.h"
#include "drivers/timer.h"

void update();

int main(){
    // event handling
    bool quit = false;
    SDL_Event event;

    // init SDL
    SDL_Init(SDL_INIT_VIDEO);
    IMG_Init(IMG_INIT_TIF);

    // SDL hints
    SDL_SetHint(SDL_HINT_RENDER_VSYNC, "0");
    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "2");

    // SDL window and renderer
    SDL_Window* window = SDL_CreateWindow("Virtual-MES",SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WINDOW_WIDTH, WINDOW_HEIGHT, 0);
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    SDL_Surface* gamesurf = IMG_Load("../peppers.tiff");
    SDL_Texture* gametex = SDL_CreateTextureFromSurface(renderer, gamesurf);

    // init timer
    _timer_start();

    // game loop
    while (!quit) {

        // clear buffer
        SDL_SetRenderDrawColor(renderer, BACKGROUND_COLOR);
        SDL_RenderClear(renderer);

        // event handling
        while (SDL_PollEvent(&event)) {
            switch (event.type) {
                case SDL_QUIT:
                    quit = true;
                    break;
                case SDL_KEYDOWN:
                    switch (event.key.keysym.sym) {
                        case SDLK_1: active_controller[0] = !active_controller[0]; break;
                        case SDLK_2: active_controller[1] = !active_controller[1]; break;
                        case SDLK_3: active_controller[2] = !active_controller[2]; break;
                        case SDLK_4: active_controller[3] = !active_controller[3]; break;
                    }
                    break;
            }
        }

        _update_controllers();
        update();

        // rendering
        SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
        SDL_RenderDrawLine(renderer, 20, 20, 40, 40);
        SDL_RenderCopy(renderer, gametex, NULL, NULL);
        SDL_RenderPresent(renderer);

    }

    // cleanup SDL
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
