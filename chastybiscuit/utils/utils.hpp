#ifndef UTILS_HPP
#define UTILS_HPP

#ifdef _MSC_VER
#include <SDL.h>
#else
#include <SDL2/SDL.h>
#endif

// Check if two SDL_Rects are colliding
bool CheckCollisionRect(SDL_Rect r1, SDL_Rect r2) {
	return (
		r1.x < r2.x + r2.w &&
		r1.x + r1.w > r2.x &&
		r1.y < r2.y + r2.h &&
		r1.y + r1.h > r2.y
		);
}

#endif // UTILS_HPP
