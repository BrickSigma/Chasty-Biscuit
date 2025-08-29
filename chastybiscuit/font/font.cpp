#include <font/font.hpp>

#include <stdio.h>

TTF_Font* Font::title = nullptr;
TTF_Font* Font::menu = nullptr;

void Font::LoadFonts() {
	Font::title = TTF_OpenFont("resources/fonts/Milky Honey.ttf", 34);
	if (Font::title == nullptr) {
		printf("Could not load font: %s\n", TTF_GetError());
	}

	Font::menu = TTF_OpenFont("resources/fonts/Milky Honey.ttf", 20);
	if (Font::menu == nullptr) {
		printf("Could not load font: %s\n", TTF_GetError());
	}
}

void Font::CloseFonts() {
	TTF_CloseFont(Font::title);
	Font::title = nullptr;
	TTF_CloseFont(Font::menu);
	Font::menu = nullptr;
}

SDL_Texture* Font::CreateTextureFromText(SDL_Renderer* renderer, TTF_Font* font, const char* text, SDL_Color color) {
	SDL_Surface* text_surf = TTF_RenderUTF8_Solid(font, text, color);
	if (text_surf == nullptr) {
		printf("Could not create text surface: %s\n", TTF_GetError());
		return nullptr;
	}

	SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, text_surf);
	if (texture == nullptr) {
		printf("Could not convert texture to surface: %s\n", SDL_GetError());
		SDL_FreeSurface(text_surf);
		return nullptr;
	}

	SDL_FreeSurface(text_surf);
	return texture;
}