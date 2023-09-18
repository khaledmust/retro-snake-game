#include "food.h"
#include "raylib.h"
#include "raymath.h"
#include "snake.h"
#include <stdio.h>
#include <stdlib.h>

void Food_Init(Food *self) {
  printf("Enter food init.\n");
  self->GenerateRandomPosition = Food_GenerateRandomPoisition;
  self->color = WHITE;
  self->ImagePath = "Graphics/food.png";
  Image tmp_image = LoadImage(self->ImagePath);
  self->texture = LoadTextureFromImage(tmp_image);
  UnloadImage(tmp_image);
  self->Draw = DrawTexture;
  printf("Exit food init.\n");
}

void Food_Deinit(Food *self) { UnloadTexture(self->texture); }

bool Food_PositionInDeque(Snake *snake, Food *self) {
  t_deque_node *current_node = snake->snake->first;
  while (current_node != NULL) {
    if (Vector2Equals(*((Vector2 *)(current_node->content)), self->position)) {
      return true;
    }
    current_node = current_node->next;
  }
  return false;
}

void Food_GetRandomCell(Food *self) {
  self->position.x = (float)GetRandomValue(0, 24);
  self->position.y = (float)GetRandomValue(0, 24);
}

void Food_GenerateRandomPoisition(Snake *snake, Food *self) {
  while (Food_PositionInDeque(snake, self)) {
    Food_GetRandomCell(self);
  }
  Food_GetRandomCell(self);
}
