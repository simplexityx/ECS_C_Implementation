#ifndef TEXT_COMPONENT_H
#define TEXT_COMPONENT_H
#include "headers.h"
#include "statComponent.h"
#include "observable.h"
typedef struct textComponent textComponent_t;

struct textComponent{
    SDL_Texture *texture;
    SDL_Rect textureRec;
    transformComponent_t *t;
    observer_t *observer;
};

textComponent_t *text_create(char *text);

void text_init(void *e, void *c);

void text_update(void *c);

void text_draw(void *c);

void text_destroy(void *c);


#endif