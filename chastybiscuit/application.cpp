#include <application.hpp>
#include <stdio.h>

#include <menu/menu.hpp>

namespace application {
	bool Application::CreateWindow(const char* title, int width, int height) {
		this->window =
			SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
				width, height, SDL_WINDOW_RESIZABLE);
		if (this->window == nullptr) {
			printf("Could not create window: %s\n", SDL_GetError());
			return false;
		}

		SDL_Renderer *renderer = SDL_CreateRenderer(this->window, -1, SDL_RENDERER_ACCELERATED);
		if (renderer == nullptr) {
			printf("Could not get window renderer: %s\n", SDL_GetError());
			return false;
		}

		this->scene_manager = scene_manager::SceneManager(this->window, renderer);

		this->is_running = true;

		return true;
	}

	void Application::Close() {
		this->scene_manager.CloseSceneManager();

		if (this->window != nullptr) {
			SDL_DestroyWindow(this->window);
			this->window = nullptr;
		}
	}
} // namespace application
