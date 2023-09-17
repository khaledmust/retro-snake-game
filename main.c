#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include "objects/food.h"
#include "objects/snake.h"
#include "game/game.h"

/* Grid size */
#define CellSize 30
#define CellCount 25

#define ScreenWidth CellSize * CellCount
#define ScreenHeight CellSize * CellCount
#define GameSpeed 60

Color Green = {173, 204, 96, 255};
Color DarkGreen = {43, 52, 24, 255};

Game game;


Vector2 pos = {.x = 5, .y = 9};
Vector2 pos2 = {.x = 6, .y = 9};
Vector2 pos3 = {.x = 7, .y = 9};

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

    /* Draw the canvas. */
    BeginDrawing();

    /* Set the background to the color Green. */
    ClearBackground(Green);

    game.food.Draw(game.food.texture, game.food.position.x * CellSize,
                game.food.position.y * CellSize, game.food.color);

    if (game.snake.SetSpeed(&game.snake)) {
      game.snake.Update(&game.snake);
    }

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
    /* int x = 0; */
    /* printf("Continue?\n"); */
    /* scanf("%d", &x); */
    /* while (x != 1) {} */
    /* x = 0; */

    game.snake.Draw(&game.snake, CellSize, DarkGreen);

    printf("The direction after is %f, %f\n", game.snake.direction.x,
           game.snake.direction.y);

    /* End the canvas. */
    EndDrawing();
  }

  /* Destroy the window after the game exits. */
  CloseWindow();

  Game_DeInit(&game);

  /* Exit status. */
  return 0;
}
