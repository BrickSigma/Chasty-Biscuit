#ifndef FONT_HPP
#define FONT_HPP

#ifdef _MSC_VER
#include <SDL.h>
#include <SDL_ttf.h>
#else
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#endif

class Font {
public:
	static TTF_Font* title;
	static TTF_Font* menu;

	// Load all the fonts needed
	static void LoadFonts();

	// Close the fonts
	static void CloseFonts();

	// Create a texture from text
	static SDL_Texture* CreateTextureFromText(SDL_Renderer* renderer, TTF_Font* font, const char* text, SDL_Color color);
};


#endif // !FONT_HPP
