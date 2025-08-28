#ifndef MENU_HPP
#define MENU_HPP

#include <scene_manager/scene.hpp>

using namespace scene_manager;

class Menu : public Scene {
private:
	SDL_Rect rect = { 0, 0, 50, 50 };
public:
	Menu(const char* id, SDL_Renderer* renderer);

	void Reload() override;

	NextScene EventLoop() override;

	void RenderLoop() override;
};

#endif  // MENU_HPP