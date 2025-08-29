#ifndef PLAYER_HPP
#define PLAYER_HPP

#ifdef _MSC_VER
#include <SDL.h>
#else
#include <SDL2/SDL.h>
#endif

class Player {
public:
	SDL_Renderer* renderer = nullptr;
	SDL_Rect rect{};

	Player() = default;
	Player(SDL_Renderer* renderer);

	void Move();

	void Draw();
};

#endif // !PLAYER_HPP
