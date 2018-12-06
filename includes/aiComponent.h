#ifndef AI_COMPONENT_H
#define AI_COMPONENT_H
#include "vector2D.h"
#include "headers.h"

typedef enum states{
    PATROL,
    ATTACK,
    HOME,
    MOVING
}states_t;

typedef struct aiComponent aiComponent_t;

typedef void (*change_state_t)(aiComponent_t *, states_t );
typedef void (*ai_state_t)(aiComponent_t *);




struct aiComponent{
    entities_t *focus;
    transformComponent_t *t;
    statComponent_t *s;
    ai_state_t ai_state;
    change_state_t change_state;
    char pathn;
    Vector2D_t homePoint;
    Vector2D_t path[2];
};


aiComponent_t *ai_create();

void ai_init(void *e, void *c);
void ai_update(void *c);
void ai_draw(void *c);
void ai_destroy(void *c);




#endif