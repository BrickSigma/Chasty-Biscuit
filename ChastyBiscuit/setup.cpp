#include <setup.hpp>

#ifdef _MSC_VER
#include <SDL.h>
#else
#include <SDL3/SDL.h>
#endif

namespace setup {
bool SDL_Startup() {
    return SDL_Init(SDL_INIT_VIDEO);
}

void SDL_QuitGame() { SDL_Quit(); }
} // namespace setup
