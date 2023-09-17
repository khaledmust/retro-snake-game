#ifndef FOOD_H_
#define FOOD_H_

#include "raylib.h"
#include "raymath.h"

typedef struct object_food{
    Vector2 position;
    Texture2D texture;
    Color color;
    char *ImagePath;
    void (*Draw) (Texture2D texture, int posX, int posY, Color tint);
}Food;

void Food_Init(Food *self);
void Food_Deinit(Food *self);

#endif // FOOD_H_
