#include "game/game.h"
#include "objects/food.h"
#include "objects/snake.h"
#include "raylib.h"
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>

/* Grid size */
#define CellSize 20
#define CellCount 25
#define OFFSET 75
#define BORDER_THICKNESS 5

#define ScreenWidth (CellSize * CellCount) + (2 * OFFSET)
#define ScreenHeight (CellSize * CellCount) + (2 * OFFSET)
#define GameSpeed 60

Color Green = {173, 204, 96, 255};
Color DarkGreen = {43, 52, 24, 255};

Rectangle Borders = {.x = (OFFSET - BORDER_THICKNESS),
                     .y = (OFFSET - BORDER_THICKNESS),
                     .height = (CellSize * CellCount) + (2 * BORDER_THICKNESS),
                     .width = (CellSize * CellCount) + (2 * BORDER_THICKNESS)};

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

    DrawRectangleLinesEx(Borders, BORDER_THICKNESS, DarkGreen);

    /* Draw the canvas. */
    BeginDrawing();
    printf("Beginning to draw.\n");
    /* Set the background to the color Green. */
    ClearBackground(Green);
    printf("Lay green canvas.\n");

    game.food.Draw(game.food.texture, game.food.position.x * CellSize + 75,
                   game.food.position.y * CellSize + 75, game.food.color);

    game.snake.Draw(&game.snake, CellSize, DarkGreen);

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

    game.UpdateGame(&game);
    printf("The direction after the press is %f, %f\n", game.snake.direction.x,
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
