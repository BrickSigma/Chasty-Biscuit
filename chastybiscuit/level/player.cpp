#include <level/player.hpp>
#include <level/level.hpp>
#include <controller/controller.hpp>
#include <utils/utils.hpp>

Player::Player(SDL_Renderer* renderer) {
	this->renderer = renderer;
	rect = SDL_Rect{ 0, 0, 16, 16 };
}

void Player::Move(SDL_Rect* camera, Uint8 collision_map[]) {
	SDL_PumpEvents();
	const Uint8* keys = SDL_GetKeyboardState(NULL);

	// Player movement code
	if (keys[SDL_SCANCODE_UP] || Controller::GetAxis().y < -CONTROLLER_DRIFT) {
		rect.y -= PLAYER_VEL;
		direction = PLAYER_UP;
	}
	else if (keys[SDL_SCANCODE_DOWN] || Controller::GetAxis().y > CONTROLLER_DRIFT) {
		rect.y += PLAYER_VEL;
		direction = PLAYER_DOWN;
	}
	else if (keys[SDL_SCANCODE_LEFT] || Controller::GetAxis().x < -CONTROLLER_DRIFT) {
		rect.x -= PLAYER_VEL;
		direction = PLAYER_LEFT;
	}
	else if (keys[SDL_SCANCODE_RIGHT] || Controller::GetAxis().x > CONTROLLER_DRIFT) {
		rect.x += PLAYER_VEL;
		direction = PLAYER_RIGHT;
	}

	// Player collision code
	for (int h = 0; h < GRID_HEIGHT; h++) {
		for (int w = 0; w < GRID_WIDTH; w++) {
			Uint8 tile = collision_map[GRID_WIDTH * h + w];
			if (!tile) {
				continue;
			}

			if (CheckCollisionRect(rect, SDL_Rect{ w * TILE_SIZE, h * TILE_SIZE, TILE_SIZE, TILE_SIZE })) {
				switch (direction) {
				case PLAYER_UP:
					rect.y = h * TILE_SIZE + TILE_SIZE;
					break;
				case PLAYER_DOWN:
					rect.y = h * TILE_SIZE - rect.h;
					break;
				case PLAYER_LEFT:
					rect.x = w * TILE_SIZE + TILE_SIZE;
					break;
				case PLAYER_RIGHT:
					rect.x = w * TILE_SIZE - rect.w;
					break;
				default:
					break;
				}
			}
		}
	}

	// Camera movement logic handled here
	if ((rect.x - camera->x) < CAMERA_BOUNDS) {
		camera->x -= CAMERA_BOUNDS - (rect.x - camera->x);
	}
	if ((rect.x - camera->x + rect.w) > camera->w - CAMERA_BOUNDS) {
		camera->x += (rect.x - camera->x + rect.w) - (camera->w - CAMERA_BOUNDS);
	}

	if ((rect.y - camera->y) < CAMERA_BOUNDS) {
		camera->y -= CAMERA_BOUNDS - (rect.y - camera->y);
	}
	if ((rect.y - camera->y + rect.h) > camera->h - CAMERA_BOUNDS) {
		camera->y += (rect.y - camera->y + rect.h) - (camera->h - CAMERA_BOUNDS);
	}
}

void Player::Draw(const SDL_Rect* camera) {
	SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
	SDL_Rect draw_rect = rect;
	draw_rect.x -= camera->x;
	draw_rect.y -= camera->y;
	SDL_RenderFillRect(renderer, &draw_rect);
}