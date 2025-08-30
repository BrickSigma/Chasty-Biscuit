#include <controller/controller.hpp>
#include <level/level.hpp>

#ifdef _MSC_VER
#include <SDL_image.h>
#else
#include <SDL2/SDL_image.h>
#endif

// Sets up the collision map
static void SetupCollisionMap(Uint8 collision_map[]) {
	SDL_Surface* map = IMG_Load("resources/collision-map.png");
	if (map == nullptr) {
		printf("Could not load collision map: %s\n", IMG_GetError());
		return;
	}

	SDL_Surface* pixel_map = SDL_ConvertSurfaceFormat(map, SDL_PIXELFORMAT_RGB888, 0);
	SDL_FreeSurface(map);
	if (pixel_map == nullptr) {
		printf("Could not convert surface: %s\n", SDL_GetError());
		return;
	}

	SDL_LockSurface(pixel_map);

	for (int h = 0; h < GRID_HEIGHT; h++) {
		for (int w = 0; w < GRID_WIDTH; w++) {
			Uint32 pixel = ((Uint32*)(pixel_map->pixels))[GRID_WIDTH * h + w];
			Uint8 r, g, b;
			SDL_GetRGB(pixel, pixel_map->format, &r, &g, &b);

			int value = 1;
			if (g == 255) {
				value = 0;
			}
			collision_map[GRID_WIDTH * h + w] = value;
		}
	}

	SDL_UnlockSurface(pixel_map);
	SDL_FreeSurface(pixel_map);

	return;
}

Level::Level(const char* id, SDL_Renderer* renderer) : Scene(id, renderer) {
	player = Player(renderer);
	camera = SDL_Rect{ 0, 0, CAMERA_WIDTH, CAMERA_HEIGHT };

	level_base_texture = IMG_LoadTexture(renderer, "resources/level.png");

	SetupCollisionMap(collision_map);

	/*for (int h = 0; h < GRID_HEIGHT; h++) {
		for (int w = 0; w < GRID_WIDTH; w++) {
			printf("%d", collision_map[GRID_WIDTH * h + w]);
		}
		printf("\n");
	}*/
}

Level::~Level() {
	SDL_DestroyTexture(level_base_texture);
	level_base_texture = nullptr;
}

void Level::Reload(SceneCode code) {
	if (code == SCENE_LEVEL_INIT) {
		// Setup the player's position
		player.rect.x = PLAYER_START_X;
		player.rect.y = PLAYER_START_Y;

		camera.x = PLAYER_START_X - CAMERA_WIDTH / 2;
		camera.y = PLAYER_START_Y - CAMERA_HEIGHT / 2;
	}
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

	player.Move(&camera, collision_map);

	return next_scene;
}

void Level::RenderLoop() {
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
	SDL_RenderClear(renderer);

	SDL_Rect level_rect = camera;

	SDL_RenderCopy(renderer, level_base_texture, &level_rect, NULL);

	player.Draw(&camera);
}

void Level::UpdateRenderer(SDL_Renderer* renderer) {
	Scene::UpdateRenderer(renderer);
	player.renderer = renderer;
}