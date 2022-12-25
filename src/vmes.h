#define WINDOW_WIDTH 100
#define WINDOW_HEIGHT 100

#define WIDTH 100
#define HEIGHT 100
#define BPP 32

#define RMASK 0xff000000
#define GMASK 0x00ff0000
#define BMASK 0x0000ff00
#define AMASK 0x000000ff
#define RBIT 3
#define GBIT 2
#define BBIT 1
#define ABIT 0

#include <sstream>
#include <SDL.h>
#include <SDL_image.h>
#include <iostream>

#include "gpu.h"
#include "controller.h"
#include "timer.h"

void update();

int main() {
    // event handling
    bool quit = false;
    SDL_Event event;

    // init SDL
    SDL_Init(SDL_INIT_VIDEO);
    IMG_Init(IMG_INIT_TIF);

    // SDL hints
    SDL_SetHint(SDL_HINT_RENDER_VSYNC, "0");
    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "0");

    // SDL window and renderer
    SDL_Window* window = SDL_CreateWindow("Virtual-MES",SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WINDOW_WIDTH, WINDOW_HEIGHT, 0);
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    // surface data
    char* pixels = (char*) malloc(WIDTH*HEIGHT*(BPP/8));
    for (int i = 0; i < HEIGHT*WIDTH*(BPP/8); i++) { // fill every pixel with 0xFFFFFFFF
        pixels[i] = (char) 255;
    }
    for (int i = 0; i < HEIGHT/2; i++) { // color first half green
        for (int j = 0; j < WIDTH*(BPP/8); j = j+(BPP/8)) {
            pixels[i*WIDTH*(BPP/8)+j+RBIT] = (char) 0;
            pixels[i*WIDTH*(BPP/8)+j+GBIT] = (char) 255;
            pixels[i*WIDTH*(BPP/8)+j+BBIT] = (char) 0;
            pixels[i*WIDTH*(BPP/8)+j+ABIT] = (char) 255;
        }
    }

    // surface an texture
    SDL_Surface* surface = SDL_CreateRGBSurfaceFrom(pixels, WIDTH, HEIGHT, BPP, (BPP/8)*WIDTH, RMASK, GMASK, BMASK, AMASK);
    SDL_Texture* texture;
    if(surface == nullptr) {
        std::cout << "Something went wrong! Here's what:" << std::endl;
        std::cout << SDL_GetError() << std::endl;
    }

    // init timer
    _timer_start();

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

        _vmes_controller_update();
        update();

        // rendering
        texture = SDL_CreateTextureFromSurface(renderer, surface);
        SDL_RenderCopy(renderer, texture, NULL, NULL);
        SDL_RenderPresent(renderer);
    }

    // cleanup
    SDL_FreeSurface(surface);
    free(pixels);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}