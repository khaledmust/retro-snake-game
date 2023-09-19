#ifndef GAME_H_
#define GAME_H_

#include "food.h"
#include "snake.h"

#define OFFSET 75

/**
 * @struct Game
 * @brief Represents the game state and components.
 *
 * The `Game` structure defines the properties and functions associated with the
 * game state. It includes the Snake game object, Food game object, and function
 * pointers for checking collision with food, checking collision with the game
 * grid, and updating the game state.
 */
typedef struct object_game {
  Snake snake; /**< The Snake game object representing the player-controlled
                  snake. */
  Food food;   /**< The Food game object representing the in-game food. */
  double speed;
  double last_update_time;
  void (*CheckCollisionFood)(
      struct object_game
          *self); /**< Function pointer for checking collision with food. */
  void (*CheckCollisionGrid)(
      struct object_game *self); /**< Function pointer for checking collision
                                    with the game grid. */
  void (*UpdateGame)(struct object_game *); /**< Function pointer for updating
                                               the game state. */
  bool (*SetSpeed)(struct object_game *);
} Game;

void Game_Init(Game *self);
void Game_DeInit(Game *self);
void Game_CheckCollisionWithFood(Game *self);
void Game_CheckCollisionWithGrid(Game *self);
void Game_Update(Game *self);
bool Game_SetSpeed(Game *self);
#endif // GAME_H_
