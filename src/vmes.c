#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>

#include <SDL.h>
#include <SDL_timer.h>
#include <SDL_thread.h>

#include "gpu.h"
#include "controller.h"
#include "timer.h"

// mes main
int mes_main();

// vmes main
int main() {
    // init SDL
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0) printf("error initializing SDL: %s\n", SDL_GetError());
    SDL_SetHint(SDL_HINT_RENDER_VSYNC, "0");
    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "0");

    // SDL window and renderer
    SDL_Window* window = SDL_CreateWindow("Virtual-MES",SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WIDTH*WINDOW_SCALE, HEIGHT*WINDOW_SCALE, 0);
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    // buffers
    uint8_t* buffer1 = (uint8_t*) malloc(_VMES_BUFFERSIZE);
    for (int i = 0; i < _VMES_BUFFERSIZE; i++) { // fill every pixel with 0xFFFFFFFF
        buffer1[i] = (uint8_t) 255;
    }
    uint8_t* buffer2 = (uint8_t*) malloc(_VMES_BUFFERSIZE);
    memcpy(buffer2, buffer1, _VMES_BUFFERSIZE);

    // surfaces and texture
    SDL_Surface* surface1 = SDL_CreateRGBSurfaceFrom(buffer1, WIDTH, HEIGHT, _VMES_BPP, (_VMES_BPP / 8) * WIDTH, RMASK, GMASK, BMASK, AMASK);
    SDL_Surface* surface2 = SDL_CreateRGBSurfaceFrom(buffer2, WIDTH, HEIGHT, _VMES_BPP, (_VMES_BPP / 8) * WIDTH, RMASK, GMASK, BMASK, AMASK);
    SDL_Texture* texture;

    // gpu header init
    bool buffer_switch = true;
    _vmes_gpu_init(buffer1, buffer2, &buffer_switch);

    // event handling
    bool quit = false;
    SDL_Event event;

    // timing
    uint32_t deltatime;
    uint32_t stop;
    uint32_t start;

    // game thread
    int data = 101;
    SDL_Thread* threadID = SDL_CreateThread( mes_main, "MES_main", (void*)data );

    // game loop
    while (!quit) {

        // event handling
        while (SDL_PollEvent(&event)) {
            switch (event.type) {
                case SDL_QUIT:
                    quit = true;
                    break;
                case SDL_KEYDOWN:
                    switch (event.key.keysym.sym) {
                        case SDLK_1: _vmes_controller_active[0] = !_vmes_controller_active[0]; break;
                        case SDLK_2: _vmes_controller_active[1] = !_vmes_controller_active[1]; break;
                        case SDLK_3: _vmes_controller_active[2] = !_vmes_controller_active[2]; break;
                        case SDLK_4: _vmes_controller_active[3] = !_vmes_controller_active[3]; break;
                    }
                    break;
            }
        }

        // update controllers
        _vmes_controller_update();

        // render current front_buffer
        if (buffer_switch) texture = SDL_CreateTextureFromSurface(renderer, surface1);
        else texture = SDL_CreateTextureFromSurface(renderer, surface2);
        SDL_RenderCopy(renderer, texture, NULL, NULL);
        SDL_RenderPresent(renderer);

        // timing
        stop = timer_get_ms();
        deltatime = stop - start;
        if (deltatime < _VMES_FRAMETIME) {
            timer_block_ms(_VMES_FRAMETIME - deltatime);
        }
        start = timer_get_ms();
    }

    // cleanup
    SDL_FreeSurface(surface1);
    SDL_FreeSurface(surface2);
    free(buffer1);
    free(buffer2);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}