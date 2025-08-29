#ifndef SCENE_MANAGER_HPP
#define SCENE_MANAGER_HPP

#include <scene_manager/scene.hpp>

#ifdef _MSC_VER
#include <SDL.h>
#else
#include <SDL2/SDL.h>
#endif

#include <vector>

constexpr int SCREEN_WIDTH = 256;
constexpr int SCREEN_HEIGHT = 192;

namespace scene_manager {
	/**
	Main scene manager: handles different scenes and their event and rendering loops.

	Also allows scenes to run in parallel.
	*/
	class SceneManager {
	private:
		// Array of all the scenes loaded into the game
		std::vector<Scene*> scenes;

		/*
		Array of scenes currently running in the game loop

		The very last scene in the array uses the event loop while the others run only the rendering loop.
		This allows a sort of "async" affect where dialogs can run but animations in the background can continue running.
		*/
		std::vector<Scene*> running_scenes;

		// A fall-back scene rendering loop in case no scenes are running
		NextScene RunFallBackScene() const;

		// Hold the current window width and height sizes to scale the output
		int window_width = 0, window_height = 0;

		/*
		Render texture setup:

		We need to be able to scale the canvas when the window resizes
		so that the aspect ratio of the game remains constant for a good look and feel
		*/
		SDL_Texture* screen_texture = nullptr;

		/*
		Timing control and frame limitting
		*/
		Uint64 start_frame = 0;
		Uint64 end_frame = 0;

		// Frame rate of the game 
		Uint64 fps = 30;
		Uint64 frame_time = 1000 / 30;

		// Used to limit the framerate
		void Tick();
	public:
		// Window
		SDL_Window* window = nullptr;
		// Window rendering context
		SDL_Renderer* renderer = nullptr;

		SceneManager() {}

		// Used to setup the scene manager and the scenes to be loaded
		SceneManager(SDL_Window* window, SDL_Renderer* renderer);

		// Used for updating the renderer on window resize events
		void UpdateRenderer();

		/*
		Add a new scene to the list of available scenes.

		NOTE: once a scene is added, it's memory is also managed and de-allocated as needed.
		It is necessary to create a new scene using `malloc` or `new` rather than pass using `&scene`.

		@param scene - The scene to add to the scene manager
		*/
		void AddScene(Scene* scene);

		/*
		Remove a scene from the scene manager

		@param id - ID of the scene to remove
		*/
		void RemoveScene(const char* id);

		// Clear all running scenes
		void ClearRunningScenes();

		/*
		Push a scene to start running it

		@param id - ID of the scene to start running
		@param reload_scene - if `true`, the scene will be reloaded
		@param scene_code - a code passed to the scene to instruct how it should be reloaded
		*/
		void PushRunningScene(const char* id, bool reload_scene, SceneCode scene_code);

		/*
		Runs the scene manager in the main game loop

		@returns `true` when the app needs to quit/exit. Used for memory management
		*/
		bool Run();

		// Closes the scene manager and frees all the allocated scenes
		void CloseSceneManager();
	};
}

#endif  // SCENE_MANAGER_HPP