#ifndef AI_COMPONENT_H
#define AI_COMPONENT_H

#include "headers.h"
typedef struct aiComponent aiComponent_t;

typedef void (*ai_state_t)(aiComponent_t *);

struct aiComponent{
    entities_t *player;
    transformComponent_t *t;
    statComponent_t *s;
    ai_state_t ai_state;
    init_t init;
    update_t update;
    draw_t draw;
    destroy_t destroy;
    int moveSpeed;
};


aiComponent_t *ai_create(entities_t *player, int moveSpeed);

void ai_init(void *e, void *c);
void ai_update(void *c);
void ai_draw(void *c);
void ai_destroy(void *c);




#endif