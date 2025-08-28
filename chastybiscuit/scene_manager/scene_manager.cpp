#include <scene_manager/scene_manager.hpp>

#include <string.h>

#include <menu/menu.hpp>

namespace scene_manager {
	SceneManager::SceneManager(SDL_Window* window, SDL_Renderer* renderer) : window(window), renderer(renderer) {
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

		for (size_t i = 0; i < this->scenes.size(); i++) {
			int x = strcmp(this->scenes[i]->id, id);
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

		// Render to the screen
		SDL_RenderPresent(this->renderer);

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
		// Free all the scenes from memory
		for (Scene* scene : this->scenes) {
			delete scene;
		}

		// Clear the arrays
		this->scenes.clear();
		this->running_scenes.clear();
	}
}