#include "game.h"
#include "deque.h"
#include "food.h"
#include "raylib.h"
#include "raymath.h"
#include "snake.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

void Game_Init(Game *self) {
  printf("I am in the Game Init loop.\n");
  Snake_Init(&(self->snake));
  Food_Init(&(self->food));
  self->CheckCollisionFood = Game_CheckCollisionWithFood;
  self->CheckCollisionGrid = Game_CheckCollisionWithGrid;
  self->UpdateGame = Game_Update;
}

void Game_DeInit(Game *self) {
  Food_Deinit(&(self->food));
  self->snake.SnakeDeInit(&self->snake);
}

void Game_CheckCollisionWithFood(Game *self) {
  if (Vector2Equals(*(Vector2 *)(self->snake.snake->first->content),
                    self->food.position)) {
    puts("EATING FOOD!!!");
    self->snake.add_segment = true;
    self->food.GenerateRandomPosition(&(self->snake), &(self->food));
  }
}

Vector2 reset_positions[3] = {
    {.x = 6, .y = 9}, {.x = 5, .y = 9}, {.x = 4, .y = 9}};

static void Game_Reset(Game *self) {
  self->snake.SnakeDeInit(&self->snake);
  self->snake.AppendToTail(&self->snake, &reset_positions[0]);
  self->snake.AppendToTail(&self->snake, &reset_positions[1]);
  self->snake.AppendToTail(&self->snake, &reset_positions[2]);

  self->snake.direction.x = 1;
  self->snake.direction.y = 0;

  self->food.GenerateRandomPosition(&self->snake, &self->food);
}

void Game_CheckCollisionWithGrid(Game *self) {
  if (((Vector2 *)(self->snake.snake->first->content))->x == 25 ||
      ((Vector2 *)(self->snake.snake->first->content))->x <= -1) {
    printf("GAME OVER !!!");
    Game_Reset(self);
  }
  if (((Vector2 *)(self->snake.snake->first->content))->y == 25 ||
      ((Vector2 *)(self->snake.snake->first->content))->y <= -1) {
    printf("GAME OVER !!!");
    Game_Reset(self);
  }
}

void Game_Update(Game *self) {
  /* Update the snake's movement every "speed" unit. */
  if (self->snake.SetSpeed(&self->snake)) {
    if (self->snake.add_segment) {
      /* Add node to the head of the snake. */
      Vector2 *old_coordinates = (Vector2 *)peekFront(self->snake.snake);
      Vector2 *new_coordinates = malloc(sizeof(Vector2));
      *new_coordinates = Vector2Add(*old_coordinates, self->snake.direction);
      pushFront(self->snake.snake, (void *)(new_coordinates));
      printf("This the game update function.\n");
      /* Update the snake's position. */
      self->snake.Update(&self->snake);
      /* Reset the addition of new segment. */
      self->snake.add_segment = false;
      /* Check if the snake collided with the food object. */
      self->CheckCollisionFood(self);
      self->CheckCollisionGrid(self);
    } else {
      self->snake.Update(&self->snake);
      self->CheckCollisionFood(self);
      self->CheckCollisionGrid(self);
    }
  }
}
