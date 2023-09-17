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

Food myFood;
Snake mySnake;

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
  Food_Init(&myFood);
  Snake_Init(&mySnake);

  mySnake.AppendToTail(&(mySnake), &pos);
  mySnake.AppendToTail(&(mySnake), &pos2);
  mySnake.AppendToTail(&(mySnake), &pos3);

  mySnake.direction.x = -1;
  mySnake.direction.y = 0;

  /* Game loop */
  while (WindowShouldClose() == false) {

    /* Draw the canvas. */
    BeginDrawing();

    /* Set the background to the color Green. */
    ClearBackground(Green);

    myFood.Draw(myFood.texture, myFood.position.x * CellSize,
                myFood.position.y * CellSize, myFood.color);

    if (mySnake.SetSpeed(&mySnake)) {
      mySnake.Update(&mySnake);
    }

    if (IsKeyPressed(KEY_UP) && mySnake.direction.y != 1) {
      mySnake.direction = SnakeDirection[NORTH];
    }

    if (IsKeyPressed(KEY_DOWN) && mySnake.direction.y != -1) {
      mySnake.direction = SnakeDirection[SOUTH];
    }

    if (IsKeyPressed(KEY_RIGHT) && mySnake.direction.x != -1) {
      mySnake.direction = SnakeDirection[EAST];
    }

    if (IsKeyPressed(KEY_LEFT) && mySnake.direction.x != 1) {
      mySnake.direction = SnakeDirection[WEST];
    }
    /* int x = 0; */
    /* printf("Continue?\n"); */
    /* scanf("%d", &x); */
    /* while (x != 1) {} */
    /* x = 0; */

    mySnake.Draw(&mySnake, CellSize, DarkGreen);

    printf("The direction after is %f, %f\n", mySnake.direction.x,
           mySnake.direction.y);

    /* End the canvas. */
    EndDrawing();
  }

  /* Destroy the window after the game exits. */
  CloseWindow();

  Food_Deinit(&myFood);

  /* Exit status. */
  return 0;
}
