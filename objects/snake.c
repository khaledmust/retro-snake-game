#include "snake.h"
#include "deque.h"
#include "raylib.h"
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

Vector2 SnakeDirection[4] = {
    {.x = 0, .y = -1}, {.x = 0, .y = 1}, {.x = 1, .y = 0}, {.x = -1, .y = 0}};

void Snake_AppendTail(Snake *self, void *VectorCordinates) {
  pushBack(self->snake, VectorCordinates);
}

void Snake_AppendHead(Snake *self, void *VectorCoordinates) {
  pushFront(self->snake, VectorCoordinates);
}

void GameObject_Draw_Snake(Snake *self, int CellSize, Color color) {
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
  printf("This is the update function\n");
  Vector2 *HeadCoordinate = (Vector2*)peekFront(self->snake);
  printf("The content of the head is %f %f\n", HeadCoordinate->x, HeadCoordinate->y);
  Vector2 *NewCoordinates = malloc(sizeof(Vector2));
  *NewCoordinates = Vector2Add(*HeadCoordinate, self->direction);
  printf("The new coordinates are x: %f, y: %f.\n", NewCoordinates->x,
         NewCoordinates->y);
  popBack(self->snake);
  pushFront(self->snake, (void *)NewCoordinates);
  printf("Exit snake update.\n");
}

bool GameObject_Snake_SetSpeed(struct object_snake *self) {
  double current_time = GetTime();
  /* Calculate the Delta Time and compare it to the speicfied interval (speed).
   */
  if (current_time - self->last_update_time >= self->speed) {
    self->last_update_time = current_time;
    return true;
  } else {
    return false;
  }
}

void Snake_DeInit(Snake *self) {
  t_deque_node *current_node = self->snake->last;
  while (current_node != NULL) {
    free(popBack(self->snake));
    current_node = self->snake->last;
  }
}

void Snake_Init(Snake *self) {
  printf("Enter snake Init.\n");
  self->snake = dequeInit();
  self->AppendToTail = Snake_AppendTail;
  self->AppendToHead = Snake_AppendHead;
  self->add_segment = false;
  self->Draw = GameObject_Draw_Snake;
  self->Update = GameObject_Snake_Update;
  self->last_update_time = 0;
  self->speed = 0.2;
  self->SetSpeed = GameObject_Snake_SetSpeed;
  self->SnakeDeInit = Snake_DeInit;
  printf("Exit snake init.\n");
}
