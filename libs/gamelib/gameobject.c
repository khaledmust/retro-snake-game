#include "gameobject.h"
#include "deque.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

Vector2 SnakeDirection[4] = {
    {.x = 0, .y = -1}, {.x = 0, .y = 1}, {.x = 1, .y = 0}, {.x = -1, .y = 0}};

void Food_Init(Food *self) {
  self->position.x = (float)GetRandomValue(0, 24);
  self->position.y = (float)GetRandomValue(0, 24);
  self->color = WHITE;
  self->ImagePath = "Graphics/food.png";
  Image tmp_image = LoadImage(self->ImagePath);
  self->texture = LoadTextureFromImage(tmp_image);
  UnloadImage(tmp_image);
  self->Draw = DrawTexture;
}

void Food_Deinit(Food *self) {
  UnloadTexture(self->texture);
}

void GameObject_Snake_AppendTail(Snake *self, void *VectorCordinates){
  pushBack(self->snake, VectorCordinates);
}

void GameObject_Draw_Snake(Snake *self, int CellSize,
                           Color color) {
  t_deque_node *current_node = self->snake->first;
  printf("The coordinates of the current node are x: %f, y: %f.\n",
         ((Vector2 *)current_node->content)->x,
         ((Vector2 *)current_node->content)->y);
  while (current_node != NULL) {
    Rectangle snakeSegment = {
        .x = ((Vector2 *)(current_node->content))->x * CellSize,
        .y = ((Vector2 *)(current_node->content))->y * CellSize,
        CellSize,
        CellSize};
    DrawRectangleRounded(snakeSegment, 0.5, 6, color);
    current_node = current_node->next;
  }
}

void GameObject_Snake_Update(struct object_snake *self) {
  Vector2 *HeadCoordinate = peekFront(self->snake);
  Vector2 *NewCoordinates = malloc(sizeof(Vector2));
  *NewCoordinates = Vector2Add(*HeadCoordinate, self->direction);
  printf("The new coordinates are x: %f, y: %f.\n", NewCoordinates->x,
         NewCoordinates->y);
  popBack(self->snake);
  pushFront(self->snake,(void *)NewCoordinates);
}

bool GameObject_Snake_SetSpeed(struct object_snake *self) {
  double current_time = GetTime();
  /* Calculate the Delta Time and compare it to the speicfied interval (speed). */
  if (current_time - self->last_update_time >= self->speed) {
    self->last_update_time = current_time;
    return true;
  } else {
    return false;
  }
}

void GameObject_Snake_Init(Snake *self) {
  self->snake = dequeInit();
  self->AppendToTail = GameObject_Snake_AppendTail;
  self->Draw = GameObject_Draw_Snake;
  self->Update = GameObject_Snake_Update;
  self->last_update_time = 0;
  self->speed = 0.2;
  self->SetSpeed = GameObject_Snake_SetSpeed;
}
