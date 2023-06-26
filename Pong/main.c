#include <stdio.h>
#include <stdbool.h>
#include <SDL2/SDL.h>
#include <stdlib.h>

#include "backend/structs.h"

#undef main
int main(int argc, char** argv) {
	if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
		printf("Couldn't initialize SDL2 because %s\n", SDL_GetError());
		return 0;
	}

	SDL_Window* window = SDL_CreateWindow("fk", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, NULL);
	if (window == NULL) {
		printf("Couldn't initialize window because %s\n", SDL_GetError());
		return 0;
	}

	SDL_Renderer* renderer = SDL_CreateRenderer(window, 0, NULL);
	if (renderer == NULL) {
		printf("Couldn't initialize renderer because %s\n", SDL_GetError());
		return 0;
	}
	

	bool done = false;
	
	gamestate_t pong_game = pong_initialize_game();
	uint8_t* keys = SDL_GetKeyboardState(NULL);

	while (!done) {
		SDL_Event ev;
		while (SDL_PollEvent(&ev)) {
			switch (ev.type) {
			case SDL_KEYDOWN:
				if (ev.key.keysym.scancode == SDL_SCANCODE_C) {
					pong_insert_coin(&pong_game);
				}
				break;
			case SDL_QUIT: {
				done = true;
				break;
			}
			default: break;
			}
		}

		// Logic
		float p1 = 0;
		float p2 = 0;
		if (keys[SDL_SCANCODE_W]) { p1 -= 1; }
		if (keys[SDL_SCANCODE_S]) { p1 += 1; }
		if (keys[SDL_SCANCODE_UP])	 { p2 -= 1; }
		if (keys[SDL_SCANCODE_DOWN]) { p2 += 1; }
		pong_move_player(&pong_game.board.player1, p1);
		pong_move_player(&pong_game.board.player2, p2);
		
		pong_gamestate_step(&pong_game);

		// Rendering
		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
		SDL_RenderClear(renderer);
			
		SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);

		SDL_FRect rect = { pong_game.board.ball.position.x, pong_game.board.ball.position.y, BALL_SIZE, BALL_SIZE};
		SDL_RenderFillRectF(renderer, &rect);
			
		rect = (SDL_FRect){ pong_game.board.player1.position.x, pong_game.board.player1.position.y, PADDLE_WIDTH, PADDLE_HEIGHT};
		SDL_RenderFillRectF(renderer, &rect);
		rect = (SDL_FRect){ pong_game.board.player2.position.x, pong_game.board.player2.position.y, PADDLE_WIDTH, PADDLE_HEIGHT};
		SDL_RenderFillRectF(renderer, &rect);


		SDL_RenderPresent(renderer);
		SDL_Delay(16);
	}

	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
	return 0;
}