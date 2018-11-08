#ifndef SPRITECOMPONENT_H
#define SPRITECOMPONENT_H
#include "headers.h"
#include "textureManager.h"
struct spriteComponent{
    char idx;
    void *entity;
    init_t init;
    update_t update;
    draw_t draw;
    transformComponent_t *t;
    SDL_Rect src, dst;
    SDL_Texture *tex;
};

spriteComponent_t *sprite_create(const char *filepath);

#endif