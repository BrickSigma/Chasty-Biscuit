#ifndef SETUP_HPP
#define SETUP_HPP

/**
 * Namespace used for starting up and closing SDL
 */
namespace setup {
/**
 * Sets up SDL
 */
bool SDL_Startup();

/**
 * Quits SDL
 */
void SDL_QuitGame();
} // namespace setup

#endif // SETUP_HPP
