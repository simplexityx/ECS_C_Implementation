#ifndef PARTICLE_COMPONENT_H
#define PARTICLE_COMPONENT_H
#include "headers.h"

typedef struct particleComponent particleComponent_t;
struct particleComponent{
    transformComponent_t *t;
    int duration;
};

particleComponent_t *particle_create(int maxDuration);

void particle_init(void *e, void *c);

void particle_update(void *c);

void particle_draw(void *c);

void particle_destroy(void *c);

#endif