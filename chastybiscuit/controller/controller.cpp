#include <controller/controller.hpp>

#include<stdio.h>

bool Controller::controller_connected = false;
SDL_GameController* Controller::controller = nullptr;

bool Controller::is_a_pressed = false;

void Controller::Connect() {
	if (Controller::controller_connected) {
		return;
	}

	int no_joysticks = SDL_NumJoysticks();

	if (no_joysticks == 0) {
		printf("No controllers found.\n");
		return;
	}
	
	Controller::controller = SDL_GameControllerOpen(0);
	if (Controller::controller == nullptr) {
		printf("Could not connect to controller: %s\n", SDL_GetError());
		return;
	}

	printf("Connected to controller!\n");
	Controller::controller_connected = true;
}

void Controller::Disconnect() {
	SDL_GameControllerClose(Controller::controller);
}

ControllerAxis Controller::GetAxis() {
	Sint16 x = SDL_GameControllerGetAxis(Controller::controller, SDL_CONTROLLER_AXIS_LEFTX);
	Sint16 y = SDL_GameControllerGetAxis(Controller::controller, SDL_CONTROLLER_AXIS_LEFTY);
	return ControllerAxis{x, y};
}

bool Controller::GetButton(SDL_GameControllerButton button) {
	return SDL_GameControllerGetButton(Controller::controller, button);
}

bool Controller::IsAPressed() {
	if (SDL_GameControllerGetButton(Controller::controller, SDL_CONTROLLER_BUTTON_A) && !Controller::is_a_pressed) {
		Controller::is_a_pressed = true;
		return true;
	} else if (!SDL_GameControllerGetButton(Controller::controller, SDL_CONTROLLER_BUTTON_A)) {
		Controller::is_a_pressed = false;
	}
	return false;
}