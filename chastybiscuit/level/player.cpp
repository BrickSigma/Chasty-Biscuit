#include <level/player.hpp>
#include <controller/controller.hpp>

Player::Player(SDL_Renderer *renderer) {
	this->renderer = renderer;
	rect = SDL_Rect{ 0, 0, 16, 16 };
}

void Player::Move() {
	SDL_PumpEvents();
	const Uint8 *keys = SDL_GetKeyboardState(NULL);

	if (keys[SDL_SCANCODE_UP] || Controller::GetAxis().y < -CONTROLLER_DRIFT) {
		rect.y -= 2;
	}
	else if (keys[SDL_SCANCODE_DOWN] || Controller::GetAxis().y > CONTROLLER_DRIFT) {
		rect.y += 2;
	} else if (keys[SDL_SCANCODE_LEFT] || Controller::GetAxis().x < -CONTROLLER_DRIFT) {
		rect.x -= 2;
	}
	else if (keys[SDL_SCANCODE_RIGHT] || Controller::GetAxis().x > CONTROLLER_DRIFT) {
		rect.x += 2;
	}
}

void Player::Draw() {
	SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
	SDL_RenderFillRect(renderer, &rect);
}