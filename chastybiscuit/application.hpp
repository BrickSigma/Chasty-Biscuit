#ifndef APPLICATION_HPP
#define APPLICATION_HPP

#ifdef _MSC_VER
#include <SDL.h>
#else
#include <SDL2/SDL.h>
#endif

#include <scene_manager/scene_manager.hpp>

constexpr unsigned int WINDOW_WIDTH = 768;
constexpr unsigned int WINDOW_HEIGHT = 576;

namespace application {
	/**
	 * Application context class.
	 *
	 * Used to share the application context between scenes.
	 */
	class Application {
	public:
		SDL_Window* window = nullptr;

		// Scene manager for the game
		scene_manager::SceneManager scene_manager;

		// Used in the main game loop
		bool is_running = false;

		/**
		 * Create a new SDL window and sets up the scenes and scene manager
		 */
		bool CreateWindow(const char* title, int width, int height);

		/**
		 * Closes the SDL window
		 */
		void Close();
	};
} // namespace application

#endif // APPLICATION_HPP
