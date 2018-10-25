#include "../includes/entities.h"

compTypes_t get_type(Components_t *c){
    return c->type;
}




void entity_update(void* e){
    entities_t *cur = (entities_t*)e;
    for(int i = 0; i < cur->compCount; i++){
        compTypes_t type = get_type(cur->components[i]);
        switch(type){

            case Transform:
                printf("\n");
                transformComponent_t *t = (transformComponent_t *)cur->components[i]->component;
                t->update((void*)t);
                break;

            case Sprite:
                printf("\n");
                spriteComponent_t *s = (spriteComponent_t *)cur->components[i]->component;
                s->update((void*)s);
                break;

            default:
                printf("no known component\n");
                break;
        }
    }
}



entities_t *entities_create(){

    entities_t *e = malloc(sizeof(entities_t));
    e->active = 0;
    e->next = e->prev = NULL;
    e->compCount = 0;
    e->components = calloc(32, sizeof(Components_t *));
    e->update = entity_update;
    return e;
}

Components_t *create_component(void *c, compTypes_t type){
    Components_t *component = malloc(sizeof(Components_t));

    component->type = type;
    component->component = c;
    return component;
}




void add_component(entities_t *e, void *c, compTypes_t type){

    Components_t *component = create_component(c, type);
    e->components[e->compCount] = component;
    e->compCount++;
    return;
}







