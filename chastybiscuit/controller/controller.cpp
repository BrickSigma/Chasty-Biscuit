#include <controller/controller.hpp>

#include<stdio.h>

bool Controller::controller_connected = false;
SDL_GameController* Controller::controller = nullptr;

bool Controller::is_a_pressed = false;
bool Controller::is_start_pressed = false;
bool Controller::is_left_joystick_pressed_up = false;
bool Controller::is_left_joystick_pressed_down = false;

void Controller::Connect() {
	if (Controller::controller_connected) {
		return;
	}

	int no_joysticks = SDL_NumJoysticks();

	if (no_joysticks == 0) {
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
	if (!controller_connected) {
		return ControllerAxis{ 0, 0 };
	}

	Sint16 x = SDL_GameControllerGetAxis(Controller::controller, SDL_CONTROLLER_AXIS_LEFTX);
	Sint16 y = SDL_GameControllerGetAxis(Controller::controller, SDL_CONTROLLER_AXIS_LEFTY);
	return ControllerAxis{x, y};
}

bool Controller::GetButton(SDL_GameControllerButton button) {
	if (!controller_connected) {
		return false;
	}

	return SDL_GameControllerGetButton(Controller::controller, button);
}

bool Controller::IsAPressed() {
	if (!controller_connected) {
		return false;
	}

	if (SDL_GameControllerGetButton(Controller::controller, SDL_CONTROLLER_BUTTON_A) && !Controller::is_a_pressed) {
		Controller::is_a_pressed = true;
		return true;
	} else if (!SDL_GameControllerGetButton(Controller::controller, SDL_CONTROLLER_BUTTON_A)) {
		Controller::is_a_pressed = false;
	}
	return false;
}

bool Controller::IsStartPressed() {
	if (!controller_connected) {
		return false;
	}

	if (SDL_GameControllerGetButton(Controller::controller, SDL_CONTROLLER_BUTTON_START) && !Controller::is_start_pressed) {
		Controller::is_start_pressed = true;
		return true;
	}
	else if (!SDL_GameControllerGetButton(Controller::controller, SDL_CONTROLLER_BUTTON_START)) {
		Controller::is_start_pressed = false;
	}
	return false;
}

bool Controller::IsLeftJoystickPressedUp() {
	if (!controller_connected) {
		return false;
	}

	Sint16 axis = SDL_GameControllerGetAxis(Controller::controller, SDL_CONTROLLER_AXIS_LEFTY);
	if (axis <= -CONTROLLER_PUSH && !Controller::is_left_joystick_pressed_up) {
		Controller::is_left_joystick_pressed_up = true;
		return true;
	}
	else if (axis > -CONTROLLER_PUSH ) {
		Controller::is_left_joystick_pressed_up = false;
	}
	return false;
}

bool Controller::IsLeftJoystickPressedDown() {
	if (!controller_connected) {
		return false;
	}

	Sint16 axis = SDL_GameControllerGetAxis(Controller::controller, SDL_CONTROLLER_AXIS_LEFTY);
	if (axis >= CONTROLLER_PUSH && !Controller::is_left_joystick_pressed_down) {
		Controller::is_left_joystick_pressed_down = true;
		return true;
	}
	else if (axis < CONTROLLER_PUSH) {
		Controller::is_left_joystick_pressed_down = false;
	}
	return false;
}