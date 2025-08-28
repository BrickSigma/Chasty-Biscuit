#ifndef MENU_HPP
#define MENU_HPP

#include <scene_manager/scene.hpp>

using namespace scene_manager;

class Menu : public Scene {
public:
	void Reload() override {}

	NextScene EventLoop() override {
		return NextScene{};
	}

	void RenderLoop() override {}
};

#endif  // MENU_HPP