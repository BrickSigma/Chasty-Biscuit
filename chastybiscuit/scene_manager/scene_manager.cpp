#include <scene_manager/scene_manager.hpp>

#include <string.h>

#include <menu/menu.hpp>

namespace scene_manager {
	SceneManager::SceneManager(SDL_Window* window, SDL_Renderer* renderer) : window(window), renderer(renderer) {
		// Get the window width and height
		SDL_GetWindowSize(window, &this->window_width, &this->window_height);

		// Setup the render texture
		this->screen_texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGB888, SDL_TEXTUREACCESS_TARGET, window_width, window_height);
		if (this->screen_texture == nullptr) {
			printf("SceneManager: couldn't create sceen_texture: %s\n", SDL_GetError());
			exit(-1);
		}

		// Setup the scenes for the game...
		Menu* menu = new Menu("menu", this->renderer);

		this->AddScene(menu);
		this->PushRunningScene("menu", true);
	}

	void SceneManager::UpdateRenderer() {
		this->renderer = SDL_GetRenderer(this->window);
		if (this->renderer == nullptr) {
			printf("Could not reload renderer: %s\n", SDL_GetError());
			exit(-1);
		}

		SDL_GetWindowSize(this->window, &this->window_width, &this->window_height);

		// Update all the scene renderers
		for (Scene* scene : this->scenes) {
			scene->UpdateRenderer(this->renderer);
		}
	}

	void SceneManager::AddScene(Scene* scene) {
		this->scenes.push_back(scene);
	}

	void SceneManager::RemoveScene(const char* id) {
		int index = -1;

		for (int i = 0; i < (int)this->scenes.size(); i++) {
			if (strcmp(this->scenes[i]->id, id) == 0) {
				index = i;
				break;
			}
		}

		if (index == -1) {
			printf("SceneManager Error: Invalid ID passed to RemoveScene()!\n");
			return;
		}

		Scene* deleted_scene = this->scenes[index];

		this->scenes.erase(this->scenes.begin() + index);

		index = -1;

		// Remove the scene from the array of running scenes as well
		for (int i = 0; i < (int)this->running_scenes.size(); i++) {
			if (strcmp(this->running_scenes[i]->id, id) == 0) {
				index = i;
				break;
			}
		}

		if (index != -1) {
			this->running_scenes.erase(this->running_scenes.begin() + index);
		}

		// Free the memory of the scene
		delete deleted_scene;
	}

	void SceneManager::ClearRunningScenes() {
		this->running_scenes.clear();
	}

	void SceneManager::PushRunningScene(const char* id, bool reload_scene) {
		int index = -1;

		for (int i = 0; i < (int)this->scenes.size(); i++) {
			if (strcmp(this->scenes[i]->id, id) == 0) {
				index = i;
				break;
			}
		}

		if (index == -1) {
			printf("SceneManager Error: Invalid ID passed to PushRunningScene()!\n");
			return;
		}

		this->running_scenes.push_back(this->scenes[index]);
		// Reload the scene if necessary
		if (reload_scene) {
			this->scenes[index]->Reload();
		}
	}

	void SceneManager::Tick() {
		end_frame = SDL_GetTicks64();
		Uint64 time_passed = end_frame - start_frame;
		if (time_passed < frame_time) {
			SDL_Delay(frame_time - time_passed);
		}
		start_frame = SDL_GetTicks64();
	}

	bool SceneManager::Run() {
		size_t no_scenes = this->running_scenes.size();

		if (no_scenes == 0) {
			NextScene next_scene = this->RunFallBackScene();

			if (next_scene.window_resized) {
				this->UpdateRenderer();
			}

			SDL_RenderPresent(this->renderer);

			return next_scene.exit;
		}

		// Switch to the screen texture for rendering
		SDL_SetRenderTarget(this->renderer, this->screen_texture);

		// Run the render loop for all scenes except the last one
		for (size_t i = 0; i < no_scenes - 1; i++) {
			running_scenes[i]->RenderLoop();
		}

		no_scenes--;

		// Run the event loop only for the last scene in the array
		NextScene next_scene = running_scenes[no_scenes]->EventLoop();
		running_scenes[no_scenes]->RenderLoop();

		// Check if the scene requested the app to exit
		if (next_scene.exit == true) {
			return true;  // Exit the application and cleanup
		}

		// Check if a resize event happened and update all the scene renderers
		if (next_scene.window_resized) {
			this->UpdateRenderer();
		}

		// Switch back to the window for rendering and draw the screen, scaled up/down
		SDL_SetRenderTarget(renderer, NULL);

		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
		SDL_RenderClear(renderer);

		// Scale the screen texture accordingly
		int scaled_width, scaled_height;
		int screen_x, screen_y;
		if ((double)window_width / (double)window_height < 1.5f) {
			scaled_width = window_width;
			scaled_height = (window_width * 2) / 3;
			screen_x = 0;
			screen_y = (window_height / 2) - (scaled_height / 2);
		}
		else {
			scaled_width = (window_height * 3) / 2;
			scaled_height = window_height;
			screen_x = (window_width/2) - (scaled_width/2);
			screen_y = 0;
		}
		SDL_Rect screen_rect = { screen_x, screen_y, scaled_width, scaled_height };

		SDL_RenderCopy(renderer, screen_texture, NULL, &screen_rect);

		// Render to the screen
		SDL_RenderPresent(this->renderer);

		// Run the clock to limit the framerate
		this->Tick();

		// Check if the scene system has been updated or not.
		if (next_scene.no_scenes_changed == 0) {
			return false;  // If no scenes have been changed, simply return and continue
		}

		// If new scenes have been added, we need to handle it.
		this->ClearRunningScenes();  // Clear all the running scenes first

		// Loop through the new scenes and push them onto the running scenes array
		for (int i = 0; i < next_scene.no_scenes_changed; i++) {
			this->PushRunningScene(next_scene.scenes[i], next_scene.reload_scenes[i]);
		}

		return false;
	}

	NextScene SceneManager::RunFallBackScene() const {
		SDL_Event event;
		NextScene next_scene{};
		next_scene.exit = false;
		next_scene.window_resized = false;

		while (SDL_PollEvent(&event)) {
			switch (event.type) {
			case SDL_QUIT:
				next_scene.exit = true;
				break;

				// Needed when resizing the window on Linux + Wayland
			case SDL_WINDOWEVENT:
				if (event.window.event == SDL_WINDOWEVENT_SIZE_CHANGED ||
					event.window.event == SDL_WINDOWEVENT_RESIZED) {
					next_scene.window_resized = true;
				}
				break;

			default:
				break;
			}
		}

		SDL_SetRenderDrawColor(this->renderer, 255, 0, 0, 255);
		SDL_RenderFillRect(this->renderer, NULL);

		return next_scene;
	}

	void SceneManager::CloseSceneManager() {
		// Free the screen texture
		SDL_DestroyTexture(this->screen_texture);

		// Free all the scenes from memory
		for (Scene* scene : this->scenes) {
			delete scene;
		}

		// Clear the arrays
		this->scenes.clear();
		this->running_scenes.clear();
	}
}