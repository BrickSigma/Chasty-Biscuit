#ifndef APPLICATION_HPP
#define APPLICATION_HPP

#ifdef _MSC_VER
#include <SDL.h>
#else
#include <SDL2/SDL.h>
#endif

namespace application {

/**
 * Application context class.
 *
 * Used to share the application context between scenes.
 */
class Application {
  public:
    SDL_Window *window;
    SDL_Surface *surface;
    SDL_Event event;

    // Used in the main game loop
    bool is_running = false;

    /**
     * Create a new SDL window
     */
    bool CreateWindow(const char *title, int width, int height);

    /**
     * Closes the SDL window
     */
    void CloseWindow();
};
} // namespace application

#endif // APPLICATION_HPP
