#ifndef GAME_H_
#define GAME_H_

#include "food.h"
#include "snake.h"

typedef struct object_game {
    Snake snake;
    Food food;
}Game;

void Game_Init(Game *self);
void Game_DeInit(Game *self);

#endif // GAME_H_
