#include <stdio.h>
#include "../includes/entities.h"
#include <stdarg.h>



int main(){

    
    entities_t *entity = entities_create();
    
    add_component(entity, (void*)transform_create(), Transform);
    add_component(entity, (void*)sprite_create(), Sprite);
    
    entity->update(entity);

    
    return 0;
}









/*
int func(int num,...){

    va_list valist;

    int sum = 0;
    int i;
    
    va_start(valist, num);
    for(i = 0; i < num; i++){
        sum += va_arg(valist, int);
    }

    va_end(valist);

    return sum;
}
*/