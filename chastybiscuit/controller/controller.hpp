#ifndef CONTROLLER_HPP
#define CONTROLLER_HPP

#ifdef _MSC_VER
#include <SDL.h>
#else
#include <SDL2/SDL.h>
#endif

typedef struct ControllerAxis {
    Sint16 x, y;
} ControllerAxis;

// Used to ignore joystick drifting
constexpr Sint16 CONTROLLER_DRIFT = 10000;

// Used to check if joystick moved up once
constexpr Sint16 CONTROLLER_PUSH = 20000;

/*
Class used to handle game controllers.
*/
class Controller {
  private:
    // Pointer to the controller
    static SDL_GameController *controller;

	// Button states: used to check if a button has been pressed once
	static bool is_a_pressed;

    static bool is_start_pressed;

    static bool is_left_joystick_pressed_up;

    static bool is_left_joystick_pressed_down;

  public:
    // Indicates if a controller is connected or not
    static bool controller_connected;

    // Attempts to connect to a controller
    static void Connect();

    // Disconnect the controller
    static void Disconnect();

	// Get the values of the controller axis
    static ControllerAxis GetAxis();

	// Get controller button state
	static bool GetButton(SDL_GameControllerButton button);

	// Check if the A button has been pressed once
	static bool IsAPressed();

    static bool IsStartPressed();

    static bool IsLeftJoystickPressedUp();

    static bool IsLeftJoystickPressedDown();
};

#endif // CONTROLLER_HPP
