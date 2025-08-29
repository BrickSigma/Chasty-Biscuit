#include <setup.hpp>

#ifdef _MSC_VER
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#else
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#endif

#include <font/font.hpp>

#include <stdio.h>

namespace setup {
	bool Startup() {
		if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_GAMECONTROLLER | SDL_INIT_JOYSTICK) != 0) {
			return false;
		}

		if (IMG_Init(IMG_INIT_PNG) != IMG_INIT_PNG) {
			printf("Could not initialize IMG: %s\n", IMG_GetError());
			return false;
		}

		if (TTF_Init() != 0) {
			printf("Could not initialize TTF: %s\n", TTF_GetError());
			return false;
		}

		// Setup the font system
		Font::LoadFonts();

		return true;
	}

	void QuitGame() {
		Font::CloseFonts();

		TTF_Quit();
		IMG_Quit();
		SDL_Quit();
	}
} // namespace setup
