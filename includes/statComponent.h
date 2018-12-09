#ifndef STATCOMPONENT_H
#define STATCOMPONENT_H
#include <stdio.h>
#include <stdlib.h>
#include "observable.h"

typedef void (*set_hp_t) (void *, int);
typedef void (*set_invis_t)(void *, char);
typedef struct statComponent statComponent_t;
struct statComponent{
    char invincible;
    int hp, strength, mana, visionRange, timerId, level, fireRes, temperature;
    observable_t *observable;
    set_hp_t set_hp;
};




statComponent_t *stat_create(short hp, short strength, short mana);



void stat_init(void *e, void *c);

void stat_update(void *c);

void stat_draw(void *c);

void stat_destroy(void *c);



#endif
