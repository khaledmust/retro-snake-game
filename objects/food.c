#include "food.h"    /**< Include the Food module header file. */
#include <stdlib.h>  /**< Include the standard library for memory allocation. */

/**
 * @brief Initializes a Food object.
 *
 * This function initializes a Food object by setting its properties, including
 * its position, color, image path, and texture.
 *
 * @param self The memory address pointing to the Food object. */
void Food_Init(Food *self) {
  self->GenerateRandomPosition = Food_GenerateRandomPoisition;
  self->color = WHITE;
  self->ImagePath = "Graphics/food.png";
  Image tmp_image = LoadImage(self->ImagePath);
  self->texture = LoadTextureFromImage(tmp_image);
  UnloadImage(tmp_image);
  self->Draw = DrawTexture;
}

/**
 * Free up the memory from the loaded texture.
 *
 * @param self The memory address pointing to the Food object. */
void Food_Deinit(Food *self) { UnloadTexture(self->texture); }

/**
 * @brief Checks if the food spawned on the same coordinates as that of the
 * snake body.
 *
 * This function iterates through the snake's body, comparing its coordinates
 * with those of the food object using the Vector2Equals() function. It then
 * returns th result of this comparison as its output.
 *
 * @param snake The memory address pointing to the Snake object.
 * @param self The memory address pointing to the Food  object.
 *
 * @return true If the food is spawned on the same coordinates as that of the
 * snake.
 * @return false Otherwise. */
bool Food_PositionInDeque(Snake *snake, Food *self) {
  t_deque_node *current_node = snake->snake->first;
  while (current_node != NULL) {
    if (Vector2Equals(*((Vector2 *)(current_node->content)), self->position)) {
      return true;
    }
    current_node = current_node->next;
  }
  return false;
}

/**
 * @brief Generates a random x and y coordinates of the "Food" class object.
 *
 * The function generates a random number within the range of 0 to 24 using the
 * GetRandomValue() function and then assigns this value to both the x and y
 * coordinates of the food instance.
 *
 * @param self The memory address pointing to the Food object. */
void Food_GetRandomCell(Food *self) {
  self->position.x = (float)GetRandomValue(0, 24);
  self->position.y = (float)GetRandomValue(0, 24);
}

/**
 * @brief  Sets the "Food" class object at a random coordinates.
 *
 * The function initially verifies if the randomly generated coordinates match
 * those of the snake's body. If they match, it proceeds to generate new random
 * coordinates repeatedly until they no longer coincide with the snake's body.
 * It employs the Food_PositionInDeque() function to assess whether there is an
 * overlap between the food object and the snake's body. Furthermore, it relies
 * on the Food_GetRandomCell() function to generate these random coordinates.
 *
 * @param snake The memory address pointing to the Snake object .
 * @param self The memory address pointing to the Food object. */
void Food_GenerateRandomPoisition(Snake *snake, Food *self) {
  while (Food_PositionInDeque(snake, self)) {
    Food_GetRandomCell(self);
  }
  Food_GetRandomCell(self);
}
