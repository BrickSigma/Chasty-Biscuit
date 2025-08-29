#include <controller/controller.hpp>
#include <level/level.hpp>

Level::Level(const char* id, SDL_Renderer* renderer) : Scene(id, renderer) {
	player = Player(renderer);
}

Level::~Level() {

}

void Level::Reload(SceneCode code) {
	(void)code;
}

NextScene Level::EventLoop() {
	NextScene next_scene{};

	while (SDL_PollEvent(&event)) {
		switch (event.type) {
		case SDL_QUIT:
			next_scene.exit = true;
			break;
		case SDL_WINDOWEVENT:
			if (event.window.event == SDL_WINDOWEVENT_RESIZED ||
				event.window.event == SDL_WINDOWEVENT_SIZE_CHANGED) {
				next_scene.window_resized = true;
			}
			break;
		}
	}

	player.Move();

	return next_scene;
}

void Level::RenderLoop() {
	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
	SDL_RenderClear(renderer);

	player.Draw();
}

void Level::UpdateRenderer(SDL_Renderer* renderer) {
	Scene::UpdateRenderer(renderer);
	player.renderer = renderer;
}