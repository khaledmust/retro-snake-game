#include "food.h"

void Food_Init(Food *self) {
  self->position.x = (float)GetRandomValue(0, 24);
  self->position.y = (float)GetRandomValue(0, 24);
  self->color = WHITE;
  self->ImagePath = "Graphics/food.png";
  Image tmp_image = LoadImage(self->ImagePath);
  self->texture = LoadTextureFromImage(tmp_image);
  UnloadImage(tmp_image);
  self->Draw = DrawTexture;
}

void Food_Deinit(Food *self) {
  UnloadTexture(self->texture);
}
