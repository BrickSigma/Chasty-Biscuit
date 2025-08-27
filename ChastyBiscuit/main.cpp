#ifdef _MSC_VER
#include <SDL.h>
#else
#include <SDL2/SDL.h>
#endif

#include <stdbool.h>
#include <stdio.h>

#ifdef __EMSCRIPTEN__
#include <emscripten.h>
#endif

#include <application.hpp>
#include <setup.hpp>

using namespace application;

/* ================================================================ */

/**
 * Main game loop code
 */
void game_loop(void *app_ctx) {
    Application *app = (Application *)app_ctx;

    if (!app->is_running) {
        app->CloseWindow();
        setup::SDL_QuitGame();
#ifdef __EMSCRIPTEN__
        emscripten_cancel_main_loop();
#else
        exit(0);
#endif
    }

    while (SDL_PollEvent(&(app->event))) {
        switch (app->event.type) {
        case SDL_QUIT:
            app->is_running = false;
            break;

        // Needed when resizing the window on Linux + Wayland
        case SDL_WINDOWEVENT:
            if (app->event.window.event == SDL_WINDOWEVENT_SIZE_CHANGED ||
                app->event.window.event == SDL_WINDOWEVENT_RESIZED) {
                // Refresh the window surface
                app->surface = SDL_GetWindowSurface(app->window);
            }
            break;

        default:
            break;
        }
    }

    SDL_FillRect(app->surface, NULL,
                 SDL_MapRGB(app->surface->format, 200, 200, 200));

    SDL_UpdateWindowSurface(app->window);
}

int main(int argc, char *argv[]) {
    (void)argc;
    (void)argv;

    Application app;

    // Initialize SDL
    if (!setup::SDL_Startup()) {
        printf("Couldn't initialize SDL: %s\n", SDL_GetError());
        setup::SDL_QuitGame();
        exit(-1);
    }

    if (!app.CreateWindow("Chasty Biscuits", 640, 480)) {
        app.CloseWindow();
        setup::SDL_QuitGame();
        exit(-1);
    }

#ifdef __EMSCRIPTEN__
    emscripten_set_main_loop_arg(game_loop, &app, 0, true);
#else
    while (true)
        game_loop(&app);
#endif

    return 0;
}
