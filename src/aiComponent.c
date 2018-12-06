#include "../includes/aiComponent.h"
#include "../includes/entities.h"
#include "../includes/statComponent.h"
#include "../includes/transformComponent.h"
#include <math.h>
#include <assert.h>
void ai_update_patrolling_state(aiComponent_t *ai);
void ai_init(void *e, void *c){
    entities_t *ent = (entities_t *)e;
    aiComponent_t *ai = (aiComponent_t *)c;
    ai->t = (transformComponent_t *)get_component(ent, Transform);
    assert(ai->t != NULL);
    ai->s = (statComponent_t *)get_component(ent, Stat);
    assert(ai->s != NULL);

    ai->path[0].x = ai->t->pos.x + 150;
    ai->path[0].y = ai->t->pos.y + 150;
    
    ai->path[1].x = ai->t->pos.x + 200;
    ai->path[1].y = ai->t->pos.y + 200;
   

    return;
}

void ai_update_attacking_state(aiComponent_t *ai){

    transformComponent_t *enemyPos = get_component(ai->focus, Transform);
    if(enemyPos->pos.x - ai->t->pos.x > 200 || enemyPos->pos.x - ai->t->pos.x < -200 || enemyPos->pos.y - ai->t->pos.y > 200 || enemyPos->pos.y - ai->t->pos.y < - 200){
        ai->change_state(ai, PATROL);
        return;
    }

    return;
}

uint32_t reachedPoint(uint32_t i, void *data){

    aiComponent_t *ai = data;
    ai->t->set_speed(ai->t, 0, 0);
    ai->pathn++%2;
    //ai->status = -1;
    return 0;
}

void ai_update_patrolling_state(aiComponent_t *ai){
    ai->focus = NULL;
    
    /*if(ai->status != MOVING){

        
        //distance between the two points
        double distance = calculate_distance(ai->t->pos, ai->path[ai->pathn]);
        //time needed to reach point
        double timeRequired = distance/ai->t->moveSpeed;
        //set timer
        ai->t->timerId = SDL_AddTimer(timeRequired * 1000, reachedPoint, ai);


        Vector2D_t tmp = Vector2(ai->path[ai->pathn].x - ai->t->pos.x, ai->path[ai->pathn].y - ai->t->pos.y );
        printVector(&tmp);
        tmp = normalizeVector(tmp);    
        printVector(&tmp);

        ai->t->set_speed(ai->t, tmp.x * ai->t->moveSpeed, tmp.y * ai->t->moveSpeed);
        ai->status = MOVING;
    }
    */

    return;
}

void ai_update_return_home(aiComponent_t *ai){



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


aiComponent_t *ai_create(int moveSpeed){

    aiComponent_t *ai = malloc(sizeof(aiComponent_t));
    ai->focus = NULL;
    ai->change_state = ai_change_state;
    ai->ai_state = ai_update_patrolling_state;
    ai->moveSpeed = moveSpeed;
    ai->pathn = 0;
    ai->status = -1;
    return ai;
}
