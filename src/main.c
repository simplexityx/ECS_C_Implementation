#include <stdio.h>
#include "../includes/entities.h"
#include <stdarg.h>



int main(){

    
    entities_t *entity = entities_create();
    
    add_component(entity,  Transform);
    add_component(entity,  Sprite);
    

    entities_t *entity2 = entities_create();
    
    add_component(entity2,  Transform);
    add_component(entity2,  Sprite);
    int i = 0;
    while(i < 10){
        entity->update(entity);
        entity2->update(entity2);
        i++;
    }
    

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