#include <setup.hpp>

#ifdef _MSC_VER
#include <SDL.h>
#include <SDL_image.h>
#else
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#endif

namespace setup {
	bool SDL_Startup() {
		if (SDL_Init(SDL_INIT_VIDEO) != 0) {
			return false;
		}

		if (IMG_Init(IMG_INIT_PNG) != IMG_INIT_PNG) {
			printf("ERROR: %s\n", IMG_GetError());
			return false;
		}

		return true;
	}

	void SDL_QuitGame() {
		SDL_Quit();
		IMG_Quit();
	}
} // namespace setup
