#ifndef MENU_HPP
#define MENU_HPP

#include <scene_manager/scene.hpp>

#ifdef _MSC_VER
#include <SDL.h>
#include <SDL_ttf.h>
#else
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#endif

using namespace scene_manager;

class Menu : public Scene {
private:
	SDL_Texture* title = nullptr;
	SDL_Texture* start_msg = nullptr;
	SDL_Texture* controls_msg = nullptr;

	// Position of the title on screen
	SDL_Rect title_pos{};

	SDL_Rect start_msg_pos{};
	SDL_Rect controls_msg_pos{};

public:
	Menu(const char* id, SDL_Renderer* renderer);

	~Menu();

	void Reload() override;

	NextScene EventLoop() override;

	void RenderLoop() override;
};

#endif  // MENU_HPP