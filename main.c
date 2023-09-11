#include <stdbool.h>
#include <stdio.h>
#include <stdint.h>
#include "libs/raylib/include/raylib.h"
#include "libs/raylib/include/raymath.h"
#include "libs/gamelib/gameobject.h"

/* Grid size */
#define CellSize 30
#define CellCount 25

#define ScreenWidth CellSize * CellCount
#define ScreenHeight CellSize * CellCount
#define GameSpeed 60

Color Green = {173, 204, 96, 255};
Color DarkGreen = {43, 52, 24, 255};

st_gameobject_food_t myFood;
st_gameobject_snake_t mySnake;
Vector2 pos = {.x = 5, .y = 9};
Vector2 pos2 = {.x = 6, .y = 9};
Vector2 pos3 = {.x = 7, .y = 9};

int main(void) {
    puts("Initiating game...");

    /* Create the game window. */
    InitWindow(ScreenWidth, ScreenHeight, "Retro-Snake");

    /* Setting up the game speed, so as to run the same on all platforms. */
    SetTargetFPS(GameSpeed);
    GameObject_Food_Init(&myFood);
    GameObject_Snake_Init(&mySnake);

    mySnake.AppendToTail(&(mySnake), &pos);
    mySnake.AppendToTail(&(mySnake), &pos2);
    mySnake.AppendToTail(&(mySnake), &pos3);

    /* Game loop */
    while (WindowShouldClose() == false) {
        /* Draw the canvas. */
        BeginDrawing();

        /* Set the background to the color Green. */
        ClearBackground(Green);

        myFood.Draw(myFood.texture, myFood.position.x * CellSize, myFood.position.y * CellSize, myFood.color);

        //mySnake.Draw(((Vector2*)(mySnake.snake.first->content))->x * CellSize, ((Vector2*)(mySnake.snake.first->content))->y * CellSize, CellSize, CellSize, DarkGreen);
        mySnake.Draw(&mySnake, CellSize, DarkGreen);
        /* End the canvas. */
        EndDrawing();
    }

    /* Destroy the window after the game exits. */
    CloseWindow();

    GambeObject_Food_Deinit(&myFood);

    /* Exit status. */
    return 0;
}
