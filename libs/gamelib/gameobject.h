#ifndef GAMEOBJECT_H_
#define GAMEOBJECT_H_
#include "..//raylib/include/raylib.h"
#include "..//raylib/include/raymath.h"
#include "deque.h"
#include <stdint.h>

typedef enum { NORTH, SOUTH, EAST, WEST } Directions;

extern Vector2 SnakeDirection[4];


/* Game objects */
typedef struct {
    Vector2 position;
    Texture2D texture;
    Color color;
    char *ImagePath;
    void (*Draw) (Texture2D texture, int posX, int posY, Color tint);
}st_gameobject_food_t;

typedef struct gameobject_snake{
    t_deque *snake;
    Vector2 direction;
    double speed;
    double last_update_time;
    void (*AppendToTail) (struct gameobject_snake *self, void *VectorCordinates);
    void (*Draw) (struct gameobject_snake *self, int CellSize, Color color);
    void (*Update) (struct gameobject_snake *self);
    bool (*SetSpeed) (struct gameobject_snake *self);
}st_gameobject_snake_t;

void GameObject_Food_Init(st_gameobject_food_t *self);
void GambeObject_Food_Deinit(st_gameobject_food_t *self);
void GameObject_Snake_Init(st_gameobject_snake_t *self);
void GameObject_Snake_AppendTail(st_gameobject_snake_t *self, void *VectorCordinates);
#endif // GAMEOBJECT_H_
