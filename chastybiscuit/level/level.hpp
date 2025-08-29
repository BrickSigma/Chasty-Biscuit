#ifndef LEVEL_HPP
#define LEVEL_HPP

#include <scene_manager/scene.hpp>
#include <level/player.hpp>

#ifdef _MSC_VER
#include <SDL.h>
#else
#include <SDL2/SDL.h>
#endif

using namespace scene_manager;

class Level : public Scene {
private:
	Player player;
public:
	Level(const char* id, SDL_Renderer* renderer);

	~Level();

	void Reload(SceneCode code) override;
	NextScene EventLoop() override;
	void RenderLoop() override;
	void UpdateRenderer(SDL_Renderer* renderer) override;
};

#endif // !LEVEL_HPP
