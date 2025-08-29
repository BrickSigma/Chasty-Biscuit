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
#include<controller/controller.hpp>
#include <setup.hpp>

using namespace application;

/* ================================================================ */

/**
 * Main game loop code
 */
void game_loop(void *app_ctx) {
    Application *app = (Application *)app_ctx;

    if (!app->is_running) {
        // Cleanup...
        Controller::Disconnect();
        app->Close();
        setup::SDL_QuitGame();
#ifdef __EMSCRIPTEN__
        emscripten_cancel_main_loop();
#else
        exit(0);
#endif
    }
       
    app->is_running = !app->scene_manager.Run();
}

int main(int argc, char *argv[]) {
    (void)argc;
    (void)argv;

    Application app = Application();

    // Initialize SDL
    if (!setup::SDL_Startup()) {
        printf("Couldn't initialize SDL: %s\n", SDL_GetError());
        setup::SDL_QuitGame();
        exit(-1);
    }

    if (!app.CreateWindow("Chasty Biscuits", WINDOW_WIDTH, WINDOW_HEIGHT)) {
        app.Close();
        setup::SDL_QuitGame();
        exit(-1);
    }

    // Setup the game controller
    Controller::Connect();

#ifdef __EMSCRIPTEN__
    emscripten_set_main_loop_arg(game_loop, &app, 0, true);
#else
    while (true)
        game_loop(&app);
#endif

    return 0;
}
