#include "game/game.h"
#include "objects/food.h"
#include "objects/snake.h"
#include "raylib.h"
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>


#define ScreenWidth (CellSize * CellCount) + (2 * OFFSET)
#define ScreenHeight (CellSize * CellCount) + (2 * OFFSET)
#define GameSpeed 60

Game game;

Vector2 pos = {.x = 6, .y = 9};
Vector2 pos2 = {.x = 5, .y = 9};
Vector2 pos3 = {.x = 4, .y = 9};

int main(void) {
  puts("Initiating game...");

  /* Create the game window. */
  InitWindow(ScreenWidth, ScreenHeight, "Retro-Snake");

  /* Setting up the game speed, so as to run the same on all platforms. */
  SetTargetFPS(GameSpeed);

  /* Creating instances of the game objects. */
  Game_Init(&game);

  game.snake.AppendToTail(&(game.snake), &pos);
  game.snake.AppendToTail(&(game.snake), &pos2);
  game.snake.AppendToTail(&(game.snake), &pos3);

  game.snake.direction.x = -1;
  game.snake.direction.y = 0;

  /* Game loop */
  while (WindowShouldClose() == false) {

    game.Draw(&game);


    if (IsKeyPressed(KEY_UP) && game.snake.direction.y != 1) {
      game.snake.direction = SnakeDirection[NORTH];
    }

    if (IsKeyPressed(KEY_DOWN) && game.snake.direction.y != -1) {
      game.snake.direction = SnakeDirection[SOUTH];
    }

    if (IsKeyPressed(KEY_RIGHT) && game.snake.direction.x != -1) {
      game.snake.direction = SnakeDirection[EAST];
    }

    if (IsKeyPressed(KEY_LEFT) && game.snake.direction.x != 1) {
      game.snake.direction = SnakeDirection[WEST];
    }

    game.UpdateGame(&game);

    /* End the canvas. */
    EndDrawing();
  }

  /* Destroy the window after the game exits. */
  CloseWindow();

  Game_DeInit(&game);

  /* Exit status. */
  return 0;
}
