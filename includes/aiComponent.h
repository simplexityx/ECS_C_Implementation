#ifndef AI_COMPONENT_H
#define AI_COMPONENT_H
#include "vector2D.h"
#include "headers.h"

typedef enum states{
    PATROL,
    ATTACK,
    HOME,
    GOING_FOR_GOAL
}states_t;



typedef struct aiComponent aiComponent_t;

typedef void (*change_state_t)(aiComponent_t *, states_t );
typedef void (*ai_state_t)(aiComponent_t *);




struct aiComponent{
    entities_t *focus, *goal;
    transformComponent_t *t;
    statComponent_t *s;
    ai_state_t ai_state;
    change_state_t change_state;
    char pathn;
    Vector2D_t homePoint;
    Vector2D_t path[2];
};


aiComponent_t *ai_create(entities_t *goalEntity);

void ai_init(void *e, void *c);
void ai_update(void *c);
void ai_draw(void *c);
void ai_destroy(void *c);




#endif