#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include "deque.h"
#include "game.h"
#include "food.h"
#include "raylib.h"
#include "raymath.h"
#include "snake.h"

void Game_Init(Game *self) {
    printf("I am in the Game Init loop.\n");
  Snake_Init(&(self->snake));
  Food_Init(&(self->food));
  self->CheckCollisionFood = Game_CheckCollisionWithFood;
  self->UpdateGame = Game_Update;
}

void Game_DeInit(Game *self) {
  Food_Deinit(&(self->food));
  /* self->snake.SnakeDeInit(&self->snake); */
}

void Game_CheckCollisionWithFood(Game *self) {
  if (Vector2Equals(*(Vector2 *)(self->snake.snake->first->content),
                    self->food.position)) {
      puts("EATING FOOD!!!");
      self->snake.add_segment = true;
      self->food.GenerateRandomPosition(&(self->snake), &(self->food));
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
      pushFront(self->snake.snake, (void*)(new_coordinates));
      printf("This the game update function.\n");
      /* Update the snake's position. */
      self->snake.Update(&self->snake);
      /* Reset the addition of new segment. */
      self->snake.add_segment = false;
      /* Check if the snake collided with the food object. */
      self->CheckCollisionFood(self);
    } else {
      self->snake.Update(&self->snake);
      self->CheckCollisionFood(self);
    }
  }
}
