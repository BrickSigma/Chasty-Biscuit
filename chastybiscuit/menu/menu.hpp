#ifndef MENU_HPP
#define MENU_HPP

#include <scene_manager/scene.hpp>

using namespace scene_manager;

class Menu : public Scene {
private:
	SDL_Event event{};
public:
	Menu(const char* id, SDL_Renderer* renderer);

	void Reload() override;

	NextScene EventLoop() override;

	void RenderLoop() override;
};

#endif  // MENU_HPP