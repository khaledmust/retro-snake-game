#include "game.h"
#include "food.h"
#include "snake.h"
#include <stdlib.h>

void Game_Init(Game *self) {
    Food_Init(&(self->food));
    Snake_Init(&(self->snake));
}

void Game_DeInit(Game *self) {
    Food_Deinit(&(self->food));
}
