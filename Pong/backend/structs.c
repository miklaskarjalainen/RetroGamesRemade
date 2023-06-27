#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <time.h>
#include "structs.h"

const float BallStartSpeed = 0.5f;
const float GapSize = (BALL_SIZE * 4);

vec2f vec2f_generate_velocity(float speed) {
	vec2f out;
	out.x = ((float)rand() / (float)(RAND_MAX / 2.0f)) - 1.0f;
	out.y = ((float)rand() / (float)(RAND_MAX / 2.0f)) - 1.0f; // lower max value because we want the ball to move horizontally, not vertically.

	float length = sqrtf(out.x * out.x + out.y * out.y);
	out.x /= length;
	out.y /= length;

	out.x *= speed;
	out.y *= speed;
	return out;
}

gamestate_t pong_initialize_game(void) {
	srand(time(NULL));

	return (gamestate_t){
		.board = {
			.ball = {
				.position = {.x = SCREEN_WIDTH / 2.0f, .y = SCREEN_HEIGHT / 2.0f},
				.velocity = vec2f_generate_velocity(5.0f)
			},
			.player1 = {
				.mover = PADDLE_P1, .score = 0, .position = {
					.x = GapSize,
					.y = (SCREEN_HEIGHT / 2.0f) - (PADDLE_HEIGHT / 2.0)
				}
			},
			.player2 = {
				.mover = PADDLE_P2, .score = 0, .position = {
					.x = SCREEN_WIDTH - (GapSize + PADDLE_WIDTH),
					.y = (SCREEN_HEIGHT / 2.0f) - (PADDLE_HEIGHT / 2.0)
				}
			},
		},
		.state = GAMESTATE_NOCOIN
	};
}

bool pong_check_collision(const player_t* player, const ball_t* ball) {
	return player->position.x < ball->position.x + BALL_SIZE &&
		player->position.x + PADDLE_WIDTH > ball->position.x &&
		player->position.y < ball->position.y + BALL_SIZE    &&
		player->position.y + PADDLE_HEIGHT > ball->position.y;
}

void pong_move_player(player_t* player, float move) {
	const float MoveSpeed = 6.0f;
	player->position.y += (move * MoveSpeed);

	const float MinY = GapSize;
	const float MaxY = (SCREEN_HEIGHT - (PADDLE_HEIGHT + GapSize));
	if (player->position.y < MinY) {
		player->position.y = MinY;
	} 
	else if (player->position.y > MaxY) {
		player->position.y = MaxY;
	}
}

void pong_insert_coin(gamestate_t* game) {
	if (game->state == GAMESTATE_NOCOIN) {
		game->state = GAMESTATE_COIN_INSERTED;
	}
}

void pong_gamestate_step(gamestate_t* game) {
	switch (game->state) {
	case GAMESTATE_NOCOIN:
		break;
	default:
		game->board.ball.position.x += game->board.ball.velocity.x;
		game->board.ball.position.y += game->board.ball.velocity.y;



		// Collision with paddle
		if (pong_check_collision(&game->board.player1, &game->board.ball) ||
			pong_check_collision(&game->board.player2, &game->board.ball)) {
			game->board.ball.velocity.x *= -1;
		}
		// Top & Bottom Collision
		if (game->board.ball.position.y <= GapSize) {
			//game->board.ball.velocity.y = -game->board.ball.velocity.y;
		}
		/*
		if (game->board.ball.position.y >= (SCREEN_HEIGHT - (GapSize + BALL_SIZE))) {
			game->board.ball.velocity.y = -fabsf(game->board.ball.velocity.y);
		}
		*/

		break;
	}
}
