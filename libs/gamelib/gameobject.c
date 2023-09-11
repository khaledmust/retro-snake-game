#include <stdlib.h>
#include <stdio.h>
#include "gameobject.h"
#include "deque.h"


void GameObject_Food_Init(st_gameobject_food_t *self) {
    self->position.x = (float)GetRandomValue(0, 24);
    self->position.y = (float)GetRandomValue(0, 24);
    self->color = WHITE;
    self->ImagePath = "Graphics/food.png";
    Image tmp_image = LoadImage(self->ImagePath);
    self->texture = LoadTextureFromImage(tmp_image);
    UnloadImage(tmp_image);
    self->Draw = DrawTexture;
}

void GambeObject_Food_Deinit(st_gameobject_food_t *self) {
    UnloadTexture(self->texture);
}


void GameObject_Snake_AppendTail(st_gameobject_snake_t *self, void *VectorCordinates) {
    if (self->snake.first == NULL) {
        pushFront(&(self->snake), VectorCordinates);
    } else {
        pushBack(&(self->snake), VectorCordinates);
    }
}

void GameObject_Draw_Snake(st_gameobject_snake_t *self, int CellSize, Color color) {
    t_deque_node *current_node = self->snake.last;

    while (current_node->next != NULL) {
        current_node = current_node->next;
        DrawRectangle(((Vector2*)(current_node->content))->x * CellSize, ((Vector2*)(current_node->content))->y * CellSize, CellSize, CellSize, color);
        printf("I am here");
    }
}

void GameObject_Snake_Init(st_gameobject_snake_t *self) {
    self->snake.first = NULL;
    self->snake.last = NULL;
    self->AppendToTail = GameObject_Snake_AppendTail;
    self->Draw = GameObject_Draw_Snake;
}
