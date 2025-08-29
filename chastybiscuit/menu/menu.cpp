#include <controller/controller.hpp>
#include <font/font.hpp>
#include <menu/menu.hpp>
#include <scene_manager/scene_manager.hpp>

Menu::Menu(const char* id, SDL_Renderer* renderer) : Scene(id, renderer) {
	SDL_Color font_color = { 167, 102, 66, 255 };
	title = Font::CreateTextureFromText(renderer, Font::title, "Chasty-Biscuit", font_color);
	start_msg = Font::CreateTextureFromText(renderer, Font::menu, "Start", font_color);
	controls_msg = Font::CreateTextureFromText(renderer, Font::menu, "Controls", font_color);

	SDL_QueryTexture(title, NULL, NULL, &(title_pos.w), &(title_pos.h));
	SDL_QueryTexture(start_msg, NULL, NULL, &(start_msg_pos.w), &(start_msg_pos.h));
	SDL_QueryTexture(controls_msg, NULL, NULL, &(controls_msg_pos.w), &(controls_msg_pos.h));

	title_pos.x = (SCREEN_WIDTH / 2) - (title_pos.w / 2);
	title_pos.y = 12;

	start_msg_pos.x = (SCREEN_WIDTH / 2) - (start_msg_pos.w / 2);
	start_msg_pos.y = 78;

	controls_msg_pos.x = (SCREEN_WIDTH / 2) - (controls_msg_pos.w / 2);
	controls_msg_pos.y = start_msg_pos.y + start_msg_pos.h + 8;
}

Menu::~Menu() {
	SDL_DestroyTexture(title);
	SDL_DestroyTexture(start_msg);
	SDL_DestroyTexture(controls_msg);
}

void Menu::Reload() {

}

NextScene Menu::EventLoop() {
	NextScene next_scene{};

	while (SDL_PollEvent(&event)) {
		switch (event.type) {
		case SDL_QUIT:
			next_scene.exit = true;
			break;
		case SDL_WINDOWEVENT:
			if (event.window.event == SDL_WINDOWEVENT_RESIZED ||
				event.window.event == SDL_WINDOWEVENT_SIZE_CHANGED) {
				next_scene.window_resized = true;
			}
			break;
		}
	}

	return next_scene;
}

void Menu::RenderLoop() {
	SDL_SetRenderDrawColor(renderer, 167, 124, 100, 255);
	SDL_RenderClear(renderer);

	SDL_RenderCopy(renderer, title, NULL, &title_pos);
	SDL_RenderCopy(renderer, start_msg, NULL, &start_msg_pos);
	SDL_RenderCopy(renderer, controls_msg, NULL, &controls_msg_pos);
}