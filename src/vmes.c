#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <signal.h>

#include <SDL.h>
#include <SDL_timer.h>
#include <SDL_thread.h>

#include <mes.h>
#include <gpu.h>
#include <input.h>
#include <timer.h>

#define _VMES_RUNNING 255
uint8_t _vmes_exit_code = _VMES_RUNNING;

// mes main
uint8_t start(void);

// mes main wrapper
void thread(void) {
    _vmes_exit_code = start();
}

// vmes main
int main() {
    // init SDL
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0) printf("error initializing SDL: %s\n", SDL_GetError());
    SDL_SetHint(SDL_HINT_RENDER_VSYNC, "0");
    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "0");

    // SDL window and renderer
    SDL_Window* window = SDL_CreateWindow("Virtual-MES", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WIDTH * _VMES_WINDOW_SCALE, HEIGHT * _VMES_WINDOW_SCALE, 0);
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    // buffers
    uint8_t* buffer1 = (uint8_t*) malloc(_VMES_BUFFERSIZE);
    memset(buffer1, 0xFF, _VMES_BUFFERSIZE);
    uint8_t* buffer2 = (uint8_t*) malloc(_VMES_BUFFERSIZE);
    memset(buffer2, 0xFF, _VMES_BUFFERSIZE);

    // surfaces and texture
    SDL_Surface* surface1 = SDL_CreateRGBSurfaceFrom(buffer1, WIDTH, HEIGHT, _VMES_BPP, (_VMES_BPP / 8) * WIDTH, RMASK, GMASK, BMASK, AMASK);
    SDL_Surface* surface2 = SDL_CreateRGBSurfaceFrom(buffer2, WIDTH, HEIGHT, _VMES_BPP, (_VMES_BPP / 8) * WIDTH, RMASK, GMASK, BMASK, AMASK);
    SDL_Texture* texture;
    SDL_Rect fullscreen;
    fullscreen.h = HEIGHT*_VMES_WINDOW_SCALE;
    fullscreen.w = WIDTH*_VMES_WINDOW_SCALE;
    fullscreen.x = 0;
    fullscreen.y = 0;

    // gpu header init
    bool buffer_switch = true;
    bool reset_switch = false;
    bool dont_render = false;
    uint16_t dont_render_time = 0;
    _vmes_gpu_init(buffer1, buffer2, &buffer_switch, &reset_switch);

    // event handling
    bool quit = false;
    bool freeze = false;
    SDL_Event event;

    // timing
    uint32_t deltatime;
    uint32_t stop_time;
    uint32_t start_time;

    // controllers
    _vmes_controller_active[0] = 1;

    // game thread
    SDL_Thread* sdlthread = SDL_CreateThread((SDL_ThreadFunction) thread, "MES_main", NULL);

    // game loop
    while (!quit) {

        if (_vmes_exit_code == CODE_EXIT) break;
        else if (_vmes_exit_code == CODE_RESTART)  {
            _vmes_exit_code = _VMES_RUNNING;
            pthread_kill((pthread_t) SDL_GetThreadID(sdlthread), 0);
            sdlthread = SDL_CreateThread((SDL_ThreadFunction) thread, "MES_main", NULL);
        }

        // event handling
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {quit = true; continue;}
            else if (event.type == SDL_KEYDOWN) {
                switch (event.key.keysym.sym) {
                    case SDLK_1: _vmes_controller_active[0] = !_vmes_controller_active[0]; break;
                    case SDLK_2: _vmes_controller_active[1] = !_vmes_controller_active[1]; break;
                    case SDLK_3: _vmes_controller_active[2] = !_vmes_controller_active[2]; break;
                    case SDLK_4: _vmes_controller_active[3] = !_vmes_controller_active[3]; break;
                }
            }
        }

        if (!freeze) {
            // update controllers
            _vmes_controller_update();

            // fake reset gpu
            if (reset_switch) {
                dont_render = true;
                dont_render_time = 0;
                reset_switch = false;
                SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
                SDL_RenderFillRect(renderer, &fullscreen);
                SDL_RenderPresent(renderer);
            }
        }

        // render front buffer
        if (!dont_render) {
            if (buffer_switch) texture = SDL_CreateTextureFromSurface(renderer, surface1);
            else texture = SDL_CreateTextureFromSurface(renderer, surface2);
            SDL_RenderCopy(renderer, texture, NULL, NULL);
            SDL_RenderPresent(renderer);
            SDL_DestroyTexture(texture);
        } else {
            dont_render_time += deltatime;
            if (dont_render_time > 500) {
            dont_render = false;
            }
        }

        if (_vmes_exit_code == CODE_FREEZEFRAME) freeze = true;

        // timing
        stop_time = timer_get_ms();
        deltatime = stop_time - start_time;
        if (deltatime < _VMES_FRAMETIME) {
            timer_block_ms(_VMES_FRAMETIME - deltatime);
        }
        start_time = timer_get_ms();
    }

    // cleanup
    // pthread_kill((pthread_t) SDL_GetThreadID(sdlthread), 0);
    SDL_FreeSurface(surface1);
    SDL_FreeSurface(surface2);
    free(buffer1);
    free(buffer2);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
