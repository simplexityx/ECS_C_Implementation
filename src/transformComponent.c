#include "../includes/transformComponent.h"
#include "../includes/entities.h"

void transform_init(void *e, void *c){
    return;
}

void transform_update(void *c){
    transformComponent_t *t = (transformComponent_t *)c;
    t->oldPos = t->pos;
    unsigned long currentTime = SDL_GetTicks();
    unsigned long deltaTime = currentTime - t->lastUpdate;
    t->pos.x += t->speed.x *(deltaTime / 1000.0f);
    t->pos.y += t->speed.y *(deltaTime / 1000.0f);
    
    t->lastUpdate = currentTime;

    return;
}


void transform_draw(void *c){
    return;
}

void set_transform_speed(void *c, int x, int y){
    transformComponent_t *t = (transformComponent_t *)c;
    t->speed.x = x;
    t->speed.y = y;
    return;
}


uint32_t reachedPointT(uint32_t i, void *data){

    transformComponent_t *t = data;
    t->set_speed(t, 0, 0);
    t->moving = 0;
    //ai->status = -1;
    return 0;
}


void set_transform_point(transformComponent_t *t, Vector2D_t v){
    if(t->moving == 0){
        printVector(&v);
        t->moving = 1;
        //distance between the two points
        double distance = calculate_distance(t->pos, v);
        //time needed to reach point
        double timeRequired = distance/t->moveSpeed;

        //set timer
        t->timerId = SDL_AddTimer(timeRequired * 1000, reachedPointT, t);
        Vector2D_t tmp = Vector2( t->speed.x = t->pos.x - v.x, t->speed.y = t->pos.y - v.y);
        tmp = normalizeVector(tmp);
        printf("tmp vec: \n");
        printVector(&tmp);
        t->set_speed(t, tmp.x * t->moveSpeed, tmp.y * t->moveSpeed);

    }  
}


transformComponent_t *transform_create(Vector2D_t pos, Vector2D_t speed, int moveSpeed){
    transformComponent_t *t = malloc(sizeof(transformComponent_t));
    t->pos = pos;
    t->speed = speed;
    t->set_speed = set_transform_speed;
    t->lastUpdate = SDL_GetTicks();
    t->moveSpeed = moveSpeed;
    t->set_point = set_transform_point;
    t->moving = 0;
    return t;
}
