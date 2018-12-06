#include "../includes/particleComponent.h"
#include "../includes/entities.h"
#include "../includes/renderer.h"
particleComponent_t *particle_create(int maxDuration){

    particleComponent_t *p = malloc(sizeof(particleComponent_t));
    assert(p != NULL);

    p->duration = rand() % maxDuration;
    
    return p;
}


uint32_t particle_kill(uint32_t i, void *e){
    entities_t *en = (entities_t *)e;
    en->active = 0;
    return 0;
}

void particle_init(void *e, void *c){
    particleComponent_t *p = (particleComponent_t *)c;
    p->t = get_component(e, Transform);
    p->timerId = SDL_AddTimer(p->duration, particle_kill, e);
    return;
}

void particle_update(void *c){
    
    return;
}

void particle_draw(void *c){
    particleComponent_t *p = (particleComponent_t *)c;
    SDL_RenderDrawPoint(renderer, p->t->pos.x, p->t->pos.y);
    return;
}

void particle_destroy(void *c){

    particleComponent_t *p = (particleComponent_t *)c;

    SDL_RemoveTimer(p->timerId);
    free(c);
    return;
}