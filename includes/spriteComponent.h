#ifndef SPRITECOMPONENT_H
#define SPRITECOMPONENT_H
#include "headers.h"

struct spriteComponent{

    void *entity;
    init_t init;
    update_t update;
    draw_t draw;
    SDL_Renderer *rend;
    SDL_Rect src, dst;
    SDL_Texture *tex;
};

spriteComponent_t *sprite_create(const char *filepath, SDL_Renderer *rend);

#endif