#include "game.h"
#include "deque.h"
#include "food.h"
#include "raylib.h"
#include "raymath.h"
#include "snake.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

extern Game game;

Color Green = {173, 204, 96, 255};
Color DarkGreen = {43, 52, 24, 255};

/**
 * @brief Defines the rectangular borders of the game grid.
 *
 * The `Borders` variable represents a rectangle that defines the borders of the
 * game grid. It specifies the position, height, and width of the grid
 * boundaries, including any border thickness.
 *
 * @note The position is determined by the `OFFSET` and `BORDER_THICKNESS`
 * values.
 * @note The height and width are based on the cell size and count, including
 * border thickness.
 */
Rectangle Borders = {
    .x = (OFFSET - BORDER_THICKNESS), /**< The x-coordinate of the top-left
                                         corner of the borders. */
    .y = (OFFSET - BORDER_THICKNESS), /**< The y-coordinate of the top-left
                                         corner of the borders. */
    .height = (CellSize * CellCount) +
              (2 * BORDER_THICKNESS), /**< The height of the borders. */
    .width = (CellSize * CellCount) +
             (2 * BORDER_THICKNESS)}; /**< The width of the borders. */

/**
 * @brief An array of Vector2 structures representing reset positions.
 *
 * The `reset_positions` array contains three Vector2 structures, each
 * representing a set of coordinates. These coordinates are predefined for use
 * in resetting game elements or objects to specific positions in the game.
 */
Vector2 reset_positions[3] = {
    {.x = 6, .y = 9}, {.x = 5, .y = 9}, {.x = 4, .y = 9}};


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

  self->score = 0;

  /* Generate a new random position for the Food object. */
  self->food.GenerateRandomPosition(&self->snake, &self->food);
}


void Game_Init(Game *self) {
  Snake_Init(&(self->snake));
  Food_Init(&(self->food));
  self->speed = 0.2;
  self->last_update_time = 0;

  Game_Reset(self);

  self->GameTitleSettings.title = "Retro Snake";
  self->GameTitleSettings.posX = OFFSET - BORDER_THICKNESS;
  self->GameTitleSettings.posY = 20;
  self->GameTitleSettings.size = 35;
  self->GameTitleSettings.color = DarkGreen;

  self->GameScoreTitleSettings.title =(char *)TextFormat("%i", self->score);
  self->GameScoreTitleSettings.posX =
      (CellSize * CellCount) + (OFFSET - BORDER_THICKNESS);
  self->GameScoreTitleSettings.posY = 20;
  self->GameScoreTitleSettings.size = 35;
  self->GameScoreTitleSettings.color = DarkGreen;

  self->GameCreatorTitleSettings.title = "Created by: Khaled Mustafa";
  self->GameCreatorTitleSettings.posX = OFFSET;
  self->GameCreatorTitleSettings.posY =
      (CellSize * CellCount) + (OFFSET + BORDER_THICKNESS);
  self->GameCreatorTitleSettings.size = 30;
  self->GameCreatorTitleSettings.color = DarkGreen;

  self->CheckCollisionFood = Game_CheckCollisionWithFood;
  self->CheckCollisionGrid = Game_CheckCollisionWithGrid;
  self->UpdateGame = Game_Update;
  self->SetSpeed = Game_SetSpeed;
  self->Draw = Game_Draw;
}

void Game_DeInit(Game *self) {
  Food_Deinit(&(self->food));
  self->snake.SnakeDeInit(&self->snake);
}

/**
 * @brief Checks for collision between the snake and the food object.
 *
 * This function checks whether the head of the snake has collided with the food
 * object. If a collision is detected, it performs the following actions:
 * - Sets the flag to add a new segment to the snake.
 * - Generates a new random position for the food object.
 * - Increases the player's score.
 *
 * @param self A pointer to the Game object representing the current game state.
 */
void Game_CheckCollisionWithFood(Game *self) {
  /* Check if the head of the snake collides with the food object's position. */
  if (Vector2Equals(*(Vector2 *)(self->snake.snake->first->content),
                    self->food.position)) {
    /* Set the flag to add a new segment to the snake. */
    self->snake.add_segment = true;

    /* Generate a new random position for the food object. */
    self->food.GenerateRandomPosition(&(self->snake), &(self->food));

    /* Increase the player's score. */
    self->score++;
  }
}

/**
 * @brief Checks for collision between the snake and the game grid boundaries.
 *
 * This function checks whether the snake has collided with the boundaries of
 * the game grid. If a collision is detected with either the horizontal (x) or
 * vertical (y) boundaries, it performs the following actions:
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

    /* Reset the to its initial state. */
    Game_Reset(self);
  }
}

/**
 * @brief Checks if it's time to update the game's speed.
 *
 * This function checks if enough time has elapsed since the last game update to
 * determine whether it's time to  perform the next game update.
 *
 * @param self A pointer to the Game object representing the current game state.
 *
 * @return Returns true if it's time to update the game's speed and perform the
 * next game update; otherwise, returns false.
 */
bool Game_SetSpeed(Game *self) {
  double current_time = GetTime();

  if (current_time - self->last_update_time >= self->speed) {
    /* Update the last update time to the current time. */
    self->last_update_time = current_time;
    return true;
  } else {
    return false;
  }
}

/**
 * @brief Updates the game state and handles the snake's movement.
 *
 * This function is responsible for updating the game state and managing the
 * snake's movement. It performs the following actions:
 * - Checks if it's time to update the snake's movement based on its speed.
 * - If an update is due, it checks whether a new segment needs to be added to
 * the snake.
 *   - If yes, it adds a new node to the head of the snake's body.
 *   - Updates the snake's position.
 *   - Resets the flag for adding a new segment.
 *   - Checks for collisions with food and the game grid.
 * - If no new segment is added, it updates the snake's position and checks for
 * collisions.
 *
 * @param self A pointer to the Game object representing the current game state.
 */
void Game_Update(Game *self) {
  /* Update the snake's movement every "speed" unit. */
  if (self->SetSpeed(self)) {
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

void Game_Draw(Game *self) {

  /* Draw the canvas. */
  BeginDrawing();
  /* Set the background to the color Green. */
  ClearBackground(Green);

  /* Draw borders. */
  DrawRectangleLinesEx(Borders, BORDER_THICKNESS, DarkGreen);

  /* Draw the food object. */
  self->food.Draw(self->food.texture, self->food.position.x * CellSize + OFFSET,
                  self->food.position.y * CellSize + OFFSET, self->food.color);

  /* Draw the snake object. */
  self->snake.Draw(&self->snake, CellSize, DarkGreen);

  /* Draw the name of the game. */
  DrawText(self->GameTitleSettings.title, self->GameTitleSettings.posX,
           self->GameTitleSettings.posY, self->GameTitleSettings.size,
           self->GameTitleSettings.color);

  /* Draw the score. */
  /* DrawText(self->GameScoreTitleSettings.title, */
  /*          self->GameScoreTitleSettings.posX, self->GameScoreTitleSettings.posY, */
  /*          self->GameScoreTitleSettings.size, */
  /*          self->GameScoreTitleSettings.color); */
  DrawText(TextFormat("%i", game.score), self->GameScoreTitleSettings.posX,
           self->GameScoreTitleSettings.posY, self->GameScoreTitleSettings.size,
           self->GameScoreTitleSettings.color);

  printf("The score is %d\n", self->score);

  /* Draw the game creator name. */
  DrawText(
      self->GameCreatorTitleSettings.title, self->GameCreatorTitleSettings.posX,
      self->GameCreatorTitleSettings.posY, self->GameCreatorTitleSettings.size,
      self->GameCreatorTitleSettings.color);
}
