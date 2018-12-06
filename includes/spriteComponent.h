#ifndef SPRITECOMPONENT_H
#define SPRITECOMPONENT_H
#include "headers.h"
#include "textureManager.h"
typedef void (*set_tex_t)(void *,char *);

#define FRAMESX     2
#define FRAMESY     2

typedef enum spriteFlags{
    NOTANIMATED,
    ANIMATED
}spriteFlags_t;


typedef enum animationStates{
    IDLE,
    WALK
}animationStates_t;


struct spriteComponent{
    char flip;
    char flags;
    transformComponent_t *t;
    set_tex_t set_tex;
    char currentFrame;
    char currentState;
    SDL_Rect src, dst;
    SDL_Texture *tex;
};

spriteComponent_t *sprite_create(const char *texName, uint32_t flags);

void sprite_init(void *e, void *c);

void sprite_draw(void *c);

void sprite_update(void *c);

void sprite_destroy(void *c);





#endif