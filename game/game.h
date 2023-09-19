#ifndef GAME_H_
#define GAME_H_

#include "food.h"
#include "snake.h"

typedef struct object_game {
    Snake snake;
    Food food;
    void (*CheckCollisionFood) (struct object_game *self);
    void (*CheckCollisionGrid) (struct object_game *self);
    void (*UpdateGame) (struct object_game *);
}Game;

void Game_Init(Game *self);
void Game_DeInit(Game *self);
void Game_CheckCollisionWithFood(Game *self);
void Game_CheckCollisionWithGrid(Game *self);
void Game_Update(Game *self);

#endif // GAME_H_
