#include "../../includes/aiComponent.h"
#include "../../includes/entities.h"
#include "../../includes/statComponent.h"
#include "../../includes/transformComponent.h"
#include <math.h>
#include <assert.h>
void ai_update_patrolling_state(aiComponent_t *ai);
void ai_init(void *e, void *c){
    aiComponent_t *ai = (aiComponent_t *)c;


    ai->t = (transformComponent_t *)get_component(e, Transform);
    ai->s = (statComponent_t *)get_component(e, Stat);
    ai->homePoint = ai->t->pos;
    ai->path[0].x = ai->t->pos.x + 50;
    ai->path[0].y = ai->t->pos.y + 50;
    
    ai->path[1].x = ai->t->pos.x - 50;
    ai->path[1].y = ai->t->pos.y - 50;
    

    return;
}

void ai_update_attacking_state(aiComponent_t *ai){

    if(ai->focus == NULL){
        ai->change_state(ai, GOING_FOR_GOAL);
        return;
    }
    transformComponent_t *enemyPos = get_component(ai->focus, Transform);
    if(enemyPos == NULL){
        printf("enemypos is NULL\n");
        ai->change_state(ai, GOING_FOR_GOAL);
        return;
    }

    assert(ai->t != NULL);
    

    if(calculate_distance(ai->t->pos, enemyPos->pos) > 200){
        ai->change_state(ai, GOING_FOR_GOAL);
        return;
    }
    ai->t->set_point(ai->t, enemyPos->pos, ATTACKING, ai->t->moveSpeed);
    return;
}



void ai_update_patrolling_state(aiComponent_t *ai){
    ai->focus = NULL;
    if(ai->t->moving == 0){
        ai->pathn +=1;
        ai->pathn %=2;
    }
    ai->t->set_point(ai->t, ai->path[ai->pathn], MOVING, ai->t->moveSpeed);
   
    
    
    return;
}

void ai_update_walk_towards_goal_state(aiComponent_t *ai){
    ai->focus = ai->goal;
    transformComponent_t *goalPos = get_component(ai->focus, Transform);
    ai->t->set_point(ai->t, goalPos->pos, MOVING, ai->t->moveSpeed);
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
            ai->ai_state = ai_update_patrolling_state;
            break;

        case ATTACK:
            ai->ai_state = ai_update_attacking_state;
            break;

        case GOING_FOR_GOAL:
            ai->ai_state = ai_update_walk_towards_goal_state;
            break;

        default:
            break;
    }

}


aiComponent_t *ai_create(entities_t *goalEntity){

    aiComponent_t *ai = malloc(sizeof(aiComponent_t));
    assert(ai != NULL);
    ai->goal = goalEntity;
    ai->focus = goalEntity;
    ai->change_state = ai_change_state;
    ai->ai_state = ai_update_walk_towards_goal_state;
    ai->pathn = 0;
   
    return ai;
}
