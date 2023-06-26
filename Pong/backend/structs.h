#ifndef STRUCTS_H
#define STRUCTS_H

#include <stdint.h>
#include <stdbool.h>

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

typedef enum {
	GAMESTATE_NOCOIN,
	GAMESTATE_COIN_INSERTED,
} gamestate;

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

typedef struct {
	board_t board;
	gamestate state;
} gamestate_t;

gamestate_t pong_initialize_game(void);
bool pong_check_collision(const player_t* player, const ball_t* ball);
void pong_move_player(player_t* player, float move); // move should be in the range of -1.0 - 1.0
void pong_insert_coin(gamestate_t* game);
void pong_gamestate_step(gamestate_t* game);

#endif