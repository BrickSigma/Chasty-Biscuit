#include <menu/menu.hpp>
#include <controller/controller.hpp>

Menu::Menu(const char* id, SDL_Renderer* renderer) : Scene(id, renderer) {}

void Menu::Reload() {

}

NextScene Menu::EventLoop() {
	NextScene next_scene{};

	while (SDL_PollEvent(&event)) {
		switch (event.type) {
		case SDL_QUIT:
			next_scene.exit = true;
			break;
		case SDL_WINDOWEVENT:
			if (event.window.event == SDL_WINDOWEVENT_RESIZED ||
				event.window.event == SDL_WINDOWEVENT_SIZE_CHANGED) {
				next_scene.window_resized = true;
			}
			break;
		}
	}

	SDL_PumpEvents();
	const Uint8* keys = SDL_GetKeyboardState(NULL);

	return next_scene;
}

void Menu::RenderLoop() {
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
	SDL_RenderClear(renderer);
}