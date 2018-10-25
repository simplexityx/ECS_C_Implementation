#include "../../includes/transformComponent.h"



void transform_update(void *c){

    transformComponent_t *t = (transformComponent_t *)c;
    printf("current position: %d, %d\n",t->x, t->y);
    t->x++;
    t->y+=25;
    return;
}


void transform_draw(void *c){
    printf("in draw in transform component no need to do anything\n");
    return;
}


transformComponent_t *transform_create(){
    
    transformComponent_t *t = malloc(sizeof(transformComponent_t));
    
    t->x = 25;
    t->y = 250;
    t->update = transform_update((void*)t);

    return t;
}
