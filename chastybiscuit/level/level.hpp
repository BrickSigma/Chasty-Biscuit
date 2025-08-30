#ifndef LEVEL_HPP
#define LEVEL_HPP

#include <scene_manager/scene.hpp>
#include <scene_manager/scene_manager.hpp>
#include <level/player.hpp>

#ifdef _MSC_VER
#include <SDL.h>
#else
#include <SDL2/SDL.h>
#endif

using namespace scene_manager;

constexpr int GRID_WIDTH = 94;
constexpr int GRID_HEIGHT = 60;
constexpr int TILE_SIZE = 16;

constexpr int CAMERA_BOUNDS = 48;
constexpr int CAMERA_WIDTH = SCREEN_WIDTH;
constexpr int CAMERA_HEIGHT = SCREEN_HEIGHT;

constexpr int PLAYER_START_X = 680;
constexpr int PLAYER_START_Y = 560;

class Level : public Scene {
private:
	Player player{};

	SDL_Rect camera{};

	// Collision map for the level
	Uint8 collision_map[GRID_WIDTH * GRID_HEIGHT] = { 0 };

	SDL_Texture* level_base_texture = nullptr;
public:
	Level(const char* id, SDL_Renderer* renderer);

	~Level();

	void Reload(SceneCode code) override;
	NextScene EventLoop() override;
	void RenderLoop() override;
	void UpdateRenderer(SDL_Renderer* renderer) override;
};

#endif // !LEVEL_HPP
