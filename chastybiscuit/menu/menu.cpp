#include <menu/menu.hpp>

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

	if (keys[SDL_SCANCODE_SPACE]) {
		next_scene.no_scenes_changed = 1;
		next_scene.scenes[0] = "";
		next_scene.reload_scenes[0] = false;
	}

	if (keys[SDL_SCANCODE_LEFT]) {
		rect.x -= 7;
	}
	else if (keys[SDL_SCANCODE_RIGHT]) {
		rect.x += 7;
	}
	else if (keys[SDL_SCANCODE_UP]) {
		rect.y -= 7;
	}
	else if (keys[SDL_SCANCODE_DOWN]) {
		rect.y += 7;
	}

	return next_scene;
}

void Menu::RenderLoop() {
	SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
	SDL_RenderClear(renderer);

	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
	SDL_RenderFillRect(renderer, &rect);
}