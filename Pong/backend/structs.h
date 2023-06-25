#ifndef STRUCTS_H
#define STRUCTS_H

#include <stdint.h>

#define SCREEN_WIDTH 858
#define SCREEN_HEIGHT 525

#define PADDLE_HEIGHT (40.0f)
#define PADDLE_WIDTH (5.0f)
#define BALL_SIZE (5.0f)

typedef enum {
	PADDLE_NONE,
	PADDLE_AI,
	PADDLE_P1,
	PADDLE_P2
} paddle_mover;

typedef struct {
	float x, y;
} vec2f;

typedef struct {
	vec2f position;
	paddle_mover mover;
	uint8_t score;
} player_t;

typedef struct {
	vec2f position;
	vec2f velocity;
} ball_t;

typedef struct {
	player_t player1, player2;
	ball_t ball;
} board_t;

board_t pong_initialize_board(void);
void pong_move_player(player_t* player, float move); // move should be in the range of -1.0 - 1.0


#endif