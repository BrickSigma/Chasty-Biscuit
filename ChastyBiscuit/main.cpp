#ifdef _MSC_VER
#include <SDL.h>
#include <SDL_ttf.h>
#else
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#endif

#include <stdbool.h>

#include <Application.h>
#include <Clock.h>
#include <Text.h>
#include <Window.h>

#ifdef __EMSCRIPTEN__
#include <emscripten.h>
#endif

typedef struct AppCtx
{
	SDL_Event event;
	SDL_Renderer* r;

	TTF_Font* font;
	Text* text;
	SDL_Rect text_pos;
	char fps_buf[32];
} AppCtx;

/* ================================================================ */

/**
 * Main game loop code
 */
void game_loop(void* app_ctx)
{
	AppCtx* ctx = (AppCtx*)app_ctx;

	while (SDL_PollEvent(&(ctx->event)))
	{

		switch (ctx->event.type)
		{

		case SDL_QUIT:
			App_stop();
			break;
		}
	}

	/* ================ */

	SDL_SetRenderDrawColor(ctx->r, 255, 0, 0, 255);
	SDL_RenderClear(ctx->r);

	Text_draw(ctx->text, &ctx->text_pos);

	sprintf(ctx->fps_buf, "FPS: %d", get_fps());
	Text_update(ctx->text, ctx->fps_buf);

	App_render();

	// printf("Delta time: %f\n", get_delta());
}

int main(int argc, char* argv[])
{
	(void)argc;
	(void)argv;
	/* ================================ */

	AppCtx ctx{};

	const char* title = "Chasty Biscuit";
	char buff[20];
	strncpy(buff, title, 20);
	ApplicationConfig app_config = { buff,640,480,SDL_WINDOW_SHOWN, SDL_RENDERER_ACCELERATED };

	Start();
	App_init(&app_config);

	ctx.r = get_context();

	ctx.font = TTF_OpenFont("./resources/8bitOperatorPlus8-Regular.ttf", 24);
	SDL_Color text_color = { 0, 0, 0, 255 };
	ctx.text = Text_new(ctx.r, ctx.font, &text_color, "FPS: 60");
	ctx.text_pos = SDL_Rect{ 32, 32, ctx.text->width, ctx.text->height };

	App_setFPS(45);

#ifdef __EMSCRIPTEN__
	emscripten_set_main_loop_arg(game_loop, &ctx, 0, true);
#else
	while (App_isRunning())
		game_loop(&ctx);
#endif

	/* ================================ */

	TTF_CloseFont(ctx.font);
	Text_destroy(&(ctx.text));

	App_quit();
	Stop();

	/* ======== */
	return 0;
}