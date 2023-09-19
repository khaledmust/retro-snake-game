#include "game.h"
#include "deque.h"
#include "food.h"
#include "raylib.h"
#include "raymath.h"
#include "snake.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

/**
 * @brief An array of Vector2 structures representing reset positions.
 *
 * The `reset_positions` array contains three Vector2 structures, each representing
 * a set of coordinates. These coordinates are predefined for use in resetting
 * game elements or objects to specific positions in the game.
 */
Vector2 reset_positions[3] = {
    {.x = 6, .y = 9}, {.x = 5, .y = 9}, {.x = 4, .y = 9}};


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

/**
 * @brief Resets the game to its initial state.
 *
 * This function resets the game by performing the following actions:
 * - Deinitializes the Snake game object.
 * - Appends three predefined reset positions to the Snake's body.
 * - Sets the Snake's direction to a default direction (right).
 * - Generates a new random position for the Food object.
 *
 * @param self A pointer to the Game object to be reset.
 */
static void Game_Reset(Game *self) {
  /* Deinitialize the Snake game object. */
  self->snake.SnakeDeInit(&self->snake);

  /* Append three predefined reset positions to the Snake's body. */
  self->snake.AppendToTail(&self->snake, &reset_positions[0]);
  self->snake.AppendToTail(&self->snake, &reset_positions[1]);
  self->snake.AppendToTail(&self->snake, &reset_positions[2]);

  /* Set the Snake's direction to a default direction (right).
   * TODO Remove magic numbers.
   */
  self->snake.direction.x = 1;
  self->snake.direction.y = 0;

  /* Generate a new random position for the Food object. */
  self->food.GenerateRandomPosition(&self->snake, &self->food);
}

/**
 * @brief Checks for collision between the snake and the game grid boundaries.
 *
 * This function checks whether the snake has collided with the boundaries of the game grid.
 * If a collision is detected with either the horizontal (x) or vertical (y) boundaries,
 * it performs the following actions:
 * - Prints a "GAME OVER" message indicating the end of the game.
 * - Resets the game to its initial state using the `Game_Reset` function.
 *
 * @param self A pointer to the Game object to be checked for grid collision.
 */
void Game_CheckCollisionWithGrid(Game *self) {
  /* Check collision with the horizontal boundaries of the game grid. */
  if (((Vector2 *)(self->snake.snake->first->content))->x == 25 ||
      ((Vector2 *)(self->snake.snake->first->content))->x <= -1) {
    printf("GAME OVER !!!");

    /* Reset the game to its initial state. */
    Game_Reset(self);
  }
  /* Check collision with the vertical boundaries of the game grid. */
  if (((Vector2 *)(self->snake.snake->first->content))->y == 25 ||
      ((Vector2 *)(self->snake.snake->first->content))->y <= -1) {
    printf("GAME OVER !!!");

    /* Reset the game to its initial state. */
    Game_Reset(self);
  }
}

/**
 * @brief Updates the game state and handles the snake's movement.
 *
 * This function is responsible for updating the game state and managing the snake's movement.
 * It performs the following actions:
 * - Checks if it's time to update the snake's movement based on its speed.
 * - If an update is due, it checks whether a new segment needs to be added to the snake.
 *   - If yes, it adds a new node to the head of the snake's body.
 *   - Updates the snake's position.
 *   - Resets the flag for adding a new segment.
 *   - Checks for collisions with food and the game grid.
 * - If no new segment is added, it updates the snake's position and checks for collisions.
 *
 * @param self A pointer to the Game object representing the current game state.
 */
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

      /* Reset the addition of a new segment flag. */
      self->snake.add_segment = false;

      /* Check if the snake collided with the food object. */
      self->CheckCollisionFood(self);
      self->CheckCollisionGrid(self);
    } else {
      /* Update the snake's position without adding a new segment. */
      self->snake.Update(&self->snake);

      /* Check for collisions with food and the game grid. */
      self->CheckCollisionFood(self);
      self->CheckCollisionGrid(self);
    }
  }
}
