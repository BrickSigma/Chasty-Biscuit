#include <setup.hpp>

#ifdef _MSC_VER
#include <SDL.h>
#else
#include <SDL2/SDL.h>
#endif

namespace setup {
bool SDL_Startup() {
    int value = SDL_Init(SDL_INIT_VIDEO);
    return value == 0;
}

void SDL_QuitGame() { SDL_Quit(); }
} // namespace setup
