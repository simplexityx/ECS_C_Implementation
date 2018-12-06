#include "../includes/aiComponent.h"
#include "../includes/entities.h"
#include "../includes/statComponent.h"
#include "../includes/transformComponent.h"
#include <math.h>
#include <assert.h>
void ai_update_patrolling_state(aiComponent_t *ai);
void ai_init(void *e, void *c){
    aiComponent_t *ai = (aiComponent_t *)c;


    ai->t = (transformComponent_t *)get_component(e, Transform);
    ai->s = (statComponent_t *)get_component(e, Stat);
    ai->homePoint = ai->t->pos;
    ai->path[0].x = ai->t->pos.x + 150;
    ai->path[0].y = ai->t->pos.y + 150;
    
    ai->path[1].x = ai->t->pos.x - 50;
    ai->path[1].y = ai->t->pos.y - 50;
   

    return;
}

void ai_update_attacking_state(aiComponent_t *ai){

    transformComponent_t *enemyPos = get_component(ai->focus, Transform);
    if(calculate_distance(ai->t->pos, enemyPos->pos) > 200){
        ai->change_state(ai, PATROL);
        return;
    }
    ai->t->moving = 0;
    ai->t->set_point(ai->t, enemyPos->pos, 0);
    return;
}



void ai_update_patrolling_state(aiComponent_t *ai){
    ai->focus = NULL;
    
    ai->t->set_point(ai->t, ai->path[ai->pathn], 1);
    if(ai->t->moving == 0){
        ai->pathn +=1;
        ai->pathn %=2;
    }
    
    
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
    free(c);
    return;
}


void ai_change_state(aiComponent_t *ai, states_t state){

    switch(state){

        case PATROL:
            printf("start patrolling sequence\n");
            ai->ai_state = ai_update_patrolling_state;
            break;

        case ATTACK:
            printf("start attacking sequence\n");
            ai->ai_state = ai_update_attacking_state;
            break;



        default:
            break;
    }

}


aiComponent_t *ai_create(){

    aiComponent_t *ai = malloc(sizeof(aiComponent_t));
    ai->focus = NULL;
    ai->change_state = ai_change_state;
    ai->ai_state = ai_update_patrolling_state;
    ai->pathn = 0;
    return ai;
}
