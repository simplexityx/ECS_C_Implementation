#include "../includes/statComponent.h"
#include <assert.h>
#define INV_TIME    250


uint32_t unset_invincible(uint32_t i, void *component){
    statComponent_t *s = (statComponent_t *)component;
    s->invincible = 0;
    return 0;
}

void set_invincible(void *component){

    statComponent_t *s = (statComponent_t *)component;
    s->invincible = 1;
    s->timerId = SDL_AddTimer(INV_TIME, unset_invincible, s);
    
    return;
}

//needs the component and the observer
void stat_subscribe(void *component, void *observer){
    statComponent_t *stat = (statComponent_t *)component;
    stat->observable->observer = observer;
    return;
}

void stat_unsubscribe(void *observable, void *observer){
    //TODO
    observable_t *obs = (observable_t *)observable;
    if(obs->observer == NULL)
        return;
    obs->observer->on_complete(obs->observer->type, NULL);
    obs->observer = NULL;
    return;
}

void stat_set_hp(void *component, int hp){

    statComponent_t *s = (statComponent_t *)component;
    if(s->invincible == 1){
        return;
    }
    s->hp -= hp;
    printf("hp: %d\n", s->hp);
    if(s->observable->observer != NULL){
        s->observable->observer->on_next(s->observable->observer->type, s->hp);
    }
    set_invincible(s);
}






statComponent_t *stat_create(short hp, short strength, short mana){
    statComponent_t *s = malloc(sizeof(statComponent_t));
    assert(s != NULL);

    s->hp = hp;
    s->strength = strength;
    s->mana = mana;
    s->set_hp = stat_set_hp;
    s->invincible = 0;
    s->timerId = -1;
    s->visionRange = 200;
    s->observable = observable_create(stat_subscribe, stat_unsubscribe);
    return s;
}




void stat_init(void *e, void *c){
    return;
}

void stat_update(void *c){
    return;
}

void stat_draw(void *c){
    return;
}

void stat_destroy(void *c){

    statComponent_t *s = (statComponent_t *)c;
    SDL_RemoveTimer(s->timerId);
    observable_destroy(s->observable);
    free(s);
    return;
}

