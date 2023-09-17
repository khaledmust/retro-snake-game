#ifndef SNAKE_H_
#define SNAKE_H_

#include "raylib.h"
#include "raymath.h"
#include "deque.h"

typedef enum { NORTH, SOUTH, EAST, WEST } Directions;

extern Vector2 SnakeDirection[4];

typedef struct object_snake{
    t_deque *snake;
    Vector2 direction;
    double speed;
    double last_update_time;
    void (*AppendToTail) (struct object_snake *self, void *VectorCordinates);
    void (*Draw) (struct object_snake *self, int CellSize, Color color);
    void (*Update) (struct object_snake *self);
    bool (*SetSpeed) (struct object_snake *self);
}Snake;

void Snake_Init(Snake *self);
void Snake_AppendTail(Snake *self, void *VectorCordinates);


#endif // SNAKE_H_
