#ifdef _MSC_VER
#include <SDL.h>
#else
#include <SDL3/SDL.h>
#endif

#include <stdbool.h>
#include <stdio.h>

#ifdef __EMSCRIPTEN__
#include <emscripten.h>
#endif

#include <setup.hpp>
#include <application.hpp>

using namespace application;

/* ================================================================ */

/**
 * Main game loop code
 */
void game_loop(void *app_ctx) {
    Application *app = (Application *)app_ctx;
    
    while (SDL_PollEvent(&(app->event))) {
        if (app->event.type == SDL_EVENT_QUIT) {
            app->is_running = false;
            return;
        }
    }
}

int main(int argc, char *argv[]) {
    (void)argc;
    (void)argv;

    Application app;

    // Initialize SDL
    if (!setup::SDL_Startup()) {
        printf("Couldn't initialize SDL: %s\n", SDL_GetError());
        goto EXIT_SDL;
    }

    if (!app.CreateWindow("Chasty Biscuits", 640, 480)) {
        goto END_APP;
    }

#ifdef __EMSCRIPTEN__
    emscripten_set_main_loop_arg(game_loop, &app, 0, true);
#else
    while (app.is_running)
        game_loop(&app);
#endif

END_APP:
    app.CloseWindow();

EXIT_SDL:
    setup::SDL_QuitGame();

    return 0;
}
