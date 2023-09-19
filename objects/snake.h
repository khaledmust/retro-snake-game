#ifndef SNAKE_H_
#define SNAKE_H_

#include "deque.h"
#include "raylib.h"
#include "raymath.h"

/**
 * @enum Directions
 * @brief Represents the possible directions a snake can move. */
typedef enum { NORTH, SOUTH, EAST, WEST } Directions;

extern Vector2 SnakeDirection[4];

/**
 * @struct Snake
 * @brief Represents a Snake game object.
 *
 * The Snake structure defines the properties and functions associated with a
 * Snake game object. It includes the snake's body represented as a deque, the
 * current direction of motion, a flag to indicate whether to add a new segment,
 * the snake's speed, the last update time, and function pointers for various
 * snake-related operations like appending to the tail or head, drawing,
 * updating, setting speed, and deinitialization.
 */
typedef struct object_snake {
  t_deque *snake;          /**< The deque representing the snake's body. */
  Vector2 direction;       /**< The current direction of motion. */
  bool add_segment;        /**< Flag indicating whether to add a new segment. */
  double speed;            /**< The snake's speed. */
  double last_update_time; /**< The timestamp of the last update. */
  void (*AppendToTail)(struct object_snake *self,
                       void *VectorCordinates); /**< Function pointer for
                                                   appending to the tail. */
  void (*AppendToHead)(struct object_snake *self,
                       void *VectorCoordinates); /**< Function pointer for
                                                    appending to the head. */
  void (*Draw)(struct object_snake *self, int CellSize,
               Color color); /**< Function pointer for drawing the snake. */
  void (*Update)(struct object_snake
                     *self); /**< Function pointer for updating the snake. */
  bool (*SetSpeed)(struct object_snake *self); /**< Function pointer for setting
                                                  the snake's speed. */
  void (*SnakeDeInit)(
      struct object_snake
          *self); /**< Function pointer for deinitializing the snake. */
} Snake;

void Snake_Init(Snake *self);

#endif // SNAKE_H_
