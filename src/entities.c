#include "../includes/entities.h"

compTypes_t get_type(Components_t *c){
    return c->type;
}


void noop(){
    return;
}



void entity_update(void* e){
    entities_t *cur = (entities_t*)e;
    for(int i = 0; i < cur->compCount; i++){
        compTypes_t type = get_type(cur->components[i]);
        switch(type){

            case Transform:
                noop();
                transformComponent_t *t = (transformComponent_t *)cur->components[i]->component;
                t->update((void*)t);
                break;

            case Sprite:
                noop();
                spriteComponent_t *s = (spriteComponent_t *)cur->components[i]->component;
                s->update((void*)s);
                break;

            default:
                printf("no known component\n");
                break;
        }
    }
}

static int eid;

entities_t *entities_create(){

    entities_t *e = malloc(sizeof(entities_t));
    e->active = 0;
    e->next = e->prev = NULL;
    e->compCount = 0;
    e->id = eid;
    eid++;
    e->components = calloc(MAXCOMPONENTS, sizeof(Components_t*));
    e->update = entity_update;
    return e;
}



Components_t *create_component(void *c, compTypes_t type){
    Components_t *component = malloc(sizeof(Components_t));

    component->type = type;
    component->component = c;
    return component;
}


void add_component(entities_t *e, compTypes_t type){

    void *component;

    //get correct component and tie it the current entity
    switch(type){
        case Transform:
            noop();
            transformComponent_t *t = transform_create();
            t->init((void*)e, (void*)t);
            component = (void*)t;
            break;
        case Sprite:
            noop();
            spriteComponent_t *s = sprite_create();
            s->init(e, s);
            component = (void*)s;
            break;
        default:
            break;
    }

    //add component to the entity
    e->components[e->compCount] = create_component(component, type);
    e->compCount++;  
    return;
}

