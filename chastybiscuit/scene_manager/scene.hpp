#ifndef SCENE_HPP
#define SCENE_HPP

#ifdef _MSC_VER
#include <SDL.h>
#else
#include <SDL2/SDL.h>
#endif

#include <stdio.h>

constexpr int MAX_SCENES = 5;  // Maximum number of scens that can run in parallel.

namespace scene_manager {
	/*
	Structure containing info about the next scene to transition to if needed
	*/
	typedef struct NextScene {
		int no_scenes_changed;  // Number of scenes to be pushed onto the running scenes array.
		const char* scenes[MAX_SCENES];  // Array of scene IDs to replace the stack with.
		bool reload_scenes[MAX_SCENES];  // Array used to indicate whether a scene should be reloaded or not.
		bool exit;  // Used to indicate whether or not to exit the app if the user quits mid-scene.
		bool window_resized;  // Indicates if the window resized.
	} NextScene;

	class Scene {
	protected:
		// Rendering context
		SDL_Renderer* renderer = nullptr;
	public:
		// Scene ID: used for locating scenes in the scene manager
		const char* id = nullptr;

		Scene(const char* id, SDL_Renderer* renderer) : renderer(renderer), id(id) {}

		virtual ~Scene() = default;

		// Used to update the renderer on windows resize events
		void UpdateRenderer(SDL_Renderer* renderer) {
			this->renderer = renderer;
		}

		// Used to restart a scene with it's initial values
		virtual void Reload() = 0;

		// Event loop function: used to handle events and game logic
		// 
		// Returns the next scene(s) to render. 
		virtual NextScene EventLoop() = 0;

		// Render loop function: used to handle rendering and animations
		virtual void RenderLoop() = 0;
	};
}

#endif // SCENE_HPP
