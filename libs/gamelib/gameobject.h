#ifndef GAMEOBJECT_H_
#define GAMEOBJECT_H_
#include "..//raylib/include/raylib.h"
#include "..//raylib/include/raymath.h"
#include "deque.h"
#include <stdint.h>

typedef enum { NORTH, SOUTH, EAST, WEST } Directions;

extern Vector2 SnakeDirection[4];


/* Game objects */
typedef struct object_food{
    Vector2 position;
    Texture2D texture;
    Color color;
    char *ImagePath;
    void (*Draw) (Texture2D texture, int posX, int posY, Color tint);
}Food;

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

void Food_Init(Food *self);
void Food_Deinit(Food *self);
void GameObject_Snake_Init(Snake *self);
void GameObject_Snake_AppendTail(Snake *self, void *VectorCordinates);
#endif // GAMEOBJECT_H_
