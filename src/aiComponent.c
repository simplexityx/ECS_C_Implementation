#include "../includes/aiComponent.h"
#include "../includes/entities.h"
#include "../includes/statComponent.h"
#include "../includes/transformComponent.h"
#include <math.h>
#include <assert.h>
void ai_init(void *e, void *c){
    entities_t *ent = (entities_t *)e;
    aiComponent_t *ai = (aiComponent_t *)c;
    ai->t = (transformComponent_t *)get_component(ent, Transform);
    assert(ai->t != NULL);
    ai->s = (statComponent_t *)get_component(ent, Stat);
    assert(ai->s != NULL);
    return;
}

void ai_update_defensive_state(aiComponent_t *ai){


    transformComponent_t *pT = get_component(ai->player, Transform);
    assert(pT != NULL);

    float tmpX =  pT->pos.x - ai->t->pos.x;
    float tmpY =   pT->pos.y - ai->t->pos.y;
    if(tmpX > 0){
        tmpX = -ai->moveSpeed;
    }else if(tmpX < 0){
        tmpX = ai->moveSpeed;
    }else{
        tmpX = 0;
    }
    if(tmpY > 0){
        tmpY = -ai->moveSpeed;
    }else if(tmpY < 0){
        tmpY = ai->moveSpeed;
    }else{
        tmpY = 0;
    }

    pT->set_trans(ai->t, tmpX, tmpY);
    return;
}


void ai_update_default_state(aiComponent_t *ai){


    if(ai->s->hp < 30){
        ai->ai_state = ai_update_defensive_state;
        return;
    }

    transformComponent_t *pT = get_component(ai->player, Transform);
    assert(pT != NULL);
    float tmpX =  pT->pos.x - ai->t->pos.x;
    float tmpY =   pT->pos.y - ai->t->pos.y;
    if(tmpX > 0){
        tmpX = ai->moveSpeed;
    }else if(tmpX < 0){
        tmpX = -ai->moveSpeed;
    }else{
        tmpX = 0;
    }
    if(tmpY > 0){
        tmpY = ai->moveSpeed;
    }else if(tmpY < 0){
        tmpY = -ai->moveSpeed;
    }else{
        tmpY = 0;
    }

    pT->set_trans(ai->t, tmpX, tmpY);

    return;
}

void ai_update(void *c){
    
    aiComponent_t *ai = (aiComponent_t *)c;
    ai->ai_state(ai);
}



void ai_draw(void *c){
    return;
}
void ai_destroy(void *c){
    return;
}


aiComponent_t *ai_create(entities_t *player,  int moveSpeed){

    aiComponent_t *ai = malloc(sizeof(aiComponent_t));
    ai->player = player;
    ai->init = ai_init;
    ai->update = ai_update;
    ai->draw = ai_draw;
    ai->destroy = ai_destroy;
    ai->ai_state = ai_update_default_state;
    ai->moveSpeed = moveSpeed;
    return ai;
}
