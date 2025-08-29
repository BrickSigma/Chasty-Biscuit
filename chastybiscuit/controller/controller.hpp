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

/*
Class used to handle game controllers.
*/
class Controller {
  private:
    // Pointer to the controller
    static SDL_GameController *controller;

	// Button states: used to check if a button has been pressed once
	static bool is_a_pressed;

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
};

#endif // CONTROLLER_HPP
