#include "structs.h"

const float GapSize = (BALL_SIZE * 4);

board_t pong_initialize_board(void) {
	return (board_t){
		.ball = {
			.position = {.x = SCREEN_WIDTH / 2.0f, .y = SCREEN_HEIGHT / 2.0f}
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
	};
}

void pong_move_player(player_t* player, float move) {
	const float MoveSpeed = 4.0f;
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
