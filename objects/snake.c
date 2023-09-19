#include "snake.h"
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

/**
 * @var SnakeDirection[]
 * @brief An array of Vector2 structures representing snake movement directions.
 *
 * The SnakeDirection array contains four Vector2 structures, each representing
 * one of the possible directions in which a snake can move: up, down, right,
 * and left. */
Vector2 SnakeDirection[4] = {
    {.x = 0, .y = -1}, /**< Represents the up direction (0, -1). */
    {.x = 0, .y = 1},  /**< Represents the down direction (0, 1). */
    {.x = 1, .y = 0},  /**< Represents the right direction (1, 0). */
    {.x = -1, .y = 0}  /**< Represents the left direction (-1, 0). */
};

/**
 * @brief The function appends a new node to the tail of the snake.
 *
 * The function appends a new node to the snake's body, which includes the
 * coordinates of it. This opertaion is accomplished using the pushBack() from
 * the deque.h library.
 *
 * @param self A pointer to the Snake object to which the tail will be appended.
 * @param VectorCoordinates A pointer to the Vector coordinates of the new tail
 * element. */
void Snake_AppendTail(Snake *self, void *VectorCoordinates) {
  pushBack(self->snake, VectorCoordinates);
}

/**
 * @brief The function appends a new node to the head of the snake.
 *
 * The function appends a new node to the snak's body, which includes the
 * coordinates of it. This operation is accomplished using the pushFront() from
 * the deque.h library.
 *
 * @param self A pointer to the Snake object to which the head will be appended.
 * @param VectorCoordinates A pointer to the Vector coordinates of the new head.
 */
void Snake_AppendHead(Snake *self, void *VectorCoordinates) {
  pushFront(self->snake, VectorCoordinates);
}

/**
 * @brief Draws the snake object based on the coordinates of each node.
 *
 * This function iterates through every node in the snake's body and draws it
 * according to its coordinates. The drawing operation utilizes the
 * `DrawRectangleRounded()` function.
 *
 * @param self A pointer to the Snake object to be iterated over and drawn.
 * @param CellSize The size of the cell occupied by each snake node.
 * @param color The color used for rendering the snake. */
void GameObject_Draw_Snake(Snake *self, int CellSize, Color color) {
  t_deque_node *current_node = self->snake->first;
  printf("The coordinates of the current node are x: %f, y: %f.\n",
         ((Vector2 *)current_node->content)->x,
         ((Vector2 *)current_node->content)->y);
  while (current_node != NULL) {
    Rectangle snakeSegment = {
        .x = ((Vector2 *)(current_node->content))->x * CellSize,
        .y = ((Vector2 *)(current_node->content))->y * CellSize,
        CellSize,
        CellSize};
    DrawRectangleRounded(snakeSegment, 0.5, 6, color);
    current_node = current_node->next;
  }
}

/** @brief Updates the Snake game object to move according to its current
 * direction.
 *
 * This function is responsible for controlling the motion of the Snake game
 * object. It updates the coordinates of every node in the snake's body based on
 * the current direction of motion, effectively moving the snake in its intended
 * direction.
 *
 * @param self A pointer to the Snake game object to be updated.
 */
void GameObject_Snake_Update(struct object_snake *self) {
  printf("This is the update function\n");
  Vector2 *HeadCoordinate = (Vector2 *)peekFront(self->snake);
  printf("The content of the head is %f %f\n", HeadCoordinate->x,
         HeadCoordinate->y);
  Vector2 *NewCoordinates = malloc(sizeof(Vector2));
  *NewCoordinates = Vector2Add(*HeadCoordinate, self->direction);
  printf("The new coordinates are x: %f, y: %f.\n", NewCoordinates->x,
         NewCoordinates->y);
  popBack(self->snake);
  pushFront(self->snake, (void *)NewCoordinates);
  printf("Exit snake update.\n");
}

/**
 * @brief Deinitializes and cleans up the Snake game object.
 *
 * This function is responsible for the deinitialization and cleanup of the
 * Snake game object. It frees all memory associated with the snake's body
 * nodes, using the popBack().
 * This is done by iterating over the snake's body starting from its tail and
 * freeing up its contents.
 *
 * \TODO We still need to free up the node itself rather than only its content.
 *
 * @param self A pointer to the Snake game object to be deinitialized. */
void Snake_DeInit(Snake *self) {
  t_deque_node *current_node = self->snake->last;
  while (current_node != NULL) {
    free(popBack(self->snake));
    current_node = self->snake->last;
  }
}

/**
 * @brief Initializes a Snake game object.
 *
 * @param self A pointer to the Snake game object to be initialized. */
void Snake_Init(Snake *self) {
  printf("Enter snake Init.\n");
  /* Initialize the deque for the snake's body. */
  self->snake = dequeInit();

  /* Assign function pointers for appending to the tail and head. */
  self->AppendToTail = Snake_AppendTail;
  self->AppendToHead = Snake_AppendHead;

  /* Set the initial state for adding a new segment. */
  self->add_segment = false;

  /* Assign the drawing and updating functions. */
  self->Draw = GameObject_Draw_Snake;
  self->Update = GameObject_Snake_Update;

  /* Assign a function for deinitializing the snake object. */
  self->SnakeDeInit = Snake_DeInit;
  printf("Exit snake init.\n");
}
