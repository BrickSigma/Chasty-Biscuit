#ifndef PLAYER_HPP
#define PLAYER_HPP

#ifdef _MSC_VER
#include <SDL.h>
#else
#include <SDL2/SDL.h>
#endif

constexpr int PLAYER_VEL = 2;

typedef enum PlayerDirection {
	PLAYER_UP,
	PLAYER_DOWN,
	PLAYER_LEFT,
	PLAYER_RIGHT
} PlayerDirection;

class Player {
public:
	SDL_Renderer* renderer = nullptr;
	SDL_Rect rect{};

	PlayerDirection direction = PLAYER_UP;

	Player() = default;
	Player(SDL_Renderer* renderer);

	void Move(SDL_Rect *camera, Uint8 collision_map[]);

	void Draw(const SDL_Rect *camera);
};

#endif // !PLAYER_HPP
