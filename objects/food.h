#ifndef FOOD_H_
#define FOOD_H_

#include "raylib.h"  /**< Include the Raylib library for graphics. */
#include "raymath.h" /**< Include the Raymath library for math functions. */
#include "snake.h"   /**< Include the Snake module header file. */

/**
 * @struct Food
 * @brief Represnts the food object in the game.
 * The Food structure defines the properties of a food object in the game,
 * including its position, generation function, texture, color, image path, and
 * drawing function.
 *  */
typedef struct object_food {
  Vector2 position; /**< The position of the food object. */
  void (*GenerateRandomPosition)(
      Snake *, struct object_food
                   *); /**< Function pointer for generating random positions. */
  Texture2D texture;   /**< The texture representing the food. */
  Color color;         /**< The color of the food object. */
  char *ImagePath;     /**< The file path to the food image. */
  void (*Draw)(Texture2D texture, int posX, int posY,
               Color tint); /**< Function pointer for drawing the food. */
} Food;

void Food_Init(Food *self);
void Food_Deinit(Food *self);
void Food_GenerateRandomPoisition(Snake *snake, Food *self);

#endif // FOOD_H_
