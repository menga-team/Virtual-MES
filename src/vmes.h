#define SURFACE_WIDTH 160
#define SURFACE_HEIGHT 120
#define WINDOW_SCALE 3

#define WIDTH 160
#define HEIGHT 120
#define BPP 32
#define BUFFERSIZE WIDTH*HEIGHT*(BPP/8)

#define RMASK 0xff000000
#define GMASK 0x00ff0000
#define BMASK 0x0000ff00
#define AMASK 0x000000ff
#define RBIT 3
#define GBIT 2
#define BBIT 1
#define ABIT 0

#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>

#include <SDL.h>
//#include <SDL_image.h>
#include <SDL_timer.h>

#include "gpu.h"
#include "controller.h"
#include "timer.h"

void init();

void update();

void end();

int main() {
    // init SDL
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0) printf("error initializing SDL: %s\n", SDL_GetError());
    SDL_SetHint(SDL_HINT_RENDER_VSYNC, "0");
    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "0");

    // SDL window and renderer
    SDL_Window* window = SDL_CreateWindow("Virtual-MES",SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SURFACE_WIDTH*WINDOW_SCALE, SURFACE_HEIGHT*WINDOW_SCALE, 0);
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    // buffers
    uint8_t* buffer1 = (uint8_t*) malloc(BUFFERSIZE);
    for (int i = 0; i < HEIGHT*WIDTH*(BPP/8); i++) { // fill every pixel with 0xFFFFFFFF
        buffer1[i] = (uint8_t) 255;
    }
    //    for (int i = 0; i < HEIGHT/2; i++) { // color first half yellow
    //        for (int j = 0; j < WIDTH*(BPP/8); j = j+(BPP/8)) {
    //            buffer1[i*WIDTH*(BPP/8)+j+RBIT] = (char) 255;
    //            buffer1[i*WIDTH*(BPP/8)+j+GBIT] = (char) 255;
    //            buffer1[i*WIDTH*(BPP/8)+j+BBIT] = (char) 0;
    //            buffer1[i*WIDTH*(BPP/8)+j+ABIT] = (char) 255;
    //        }
    //    }
    uint8_t* buffer2 = (uint8_t*) malloc(BUFFERSIZE);
    memcpy(buffer2, buffer1, BUFFERSIZE);

    // surfaces and texture
    SDL_Surface* surface1 = SDL_CreateRGBSurfaceFrom(buffer1, WIDTH, HEIGHT, BPP, (BPP / 8) * WIDTH, RMASK, GMASK, BMASK, AMASK);
    SDL_Surface* surface2 = SDL_CreateRGBSurfaceFrom(buffer2, WIDTH, HEIGHT, BPP, (BPP / 8) * WIDTH, RMASK, GMASK, BMASK, AMASK);
    SDL_Texture* texture;

    // gpu header init
    bool buffer_switch = true;
    _vmes_gpu_init(buffer1, buffer2, &buffer_switch);

    // event handling
    bool quit = false;
    SDL_Event event;

    // initialize game
    init();

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

        // update game
        update();

        // render current front_buffer
        if (buffer_switch) texture = SDL_CreateTextureFromSurface(renderer, surface1);
        else texture = SDL_CreateTextureFromSurface(renderer, surface2);
        SDL_RenderCopy(renderer, texture, NULL, NULL);
        SDL_RenderPresent(renderer);
    }

    // cleanup
    end();
    SDL_FreeSurface(surface1);
    SDL_FreeSurface(surface2);
    free(buffer1);
    free(buffer2);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}