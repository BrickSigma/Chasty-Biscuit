#include <application.hpp>
#include <stdio.h>

namespace application {
bool Application::CreateWindow(const char *title, int width, int height) {
    this->window = SDL_CreateWindow(title, width, height, SDL_WINDOW_RESIZABLE);
    if (this->window == nullptr) {
        printf("Could not create window: %s\n", SDL_GetError());
        return false;
    }

    this->surface = SDL_GetWindowSurface(this->window);
    if (this->surface == nullptr) {
        printf("Could not get window surface: %s\n", SDL_GetError());
        return false;
    }

    this->is_running = true;

    return true;
}

void Application::CloseWindow() {
    if (this->window != nullptr)
        SDL_DestroyWindow(this->window);
}
} // namespace application
