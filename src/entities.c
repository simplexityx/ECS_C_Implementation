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

            case Collision:
                noop();
                colliderComponent_t *c = (colliderComponent_t *)cur->components[i]->component;
                c->update((void*)c);
                break;

            case KeyBoard:
                noop();
                keyboardComponent_t *k = (keyboardComponent_t *)cur->components[i]->component;
                k->update((void*)k);
                break;

            default:
                printf("no known component\n");
                break;
        }
    }
}

void entity_draw(void *e){

    entities_t *cur = (entities_t *)e;
    for(int i = 0; i < cur->compCount; i++){
        compTypes_t type = get_type(cur->components[i]);
        switch(type){
            case Transform:
                noop();
                transformComponent_t *t = (transformComponent_t *)cur->components[i]->component;
                t->draw((void*)t);
                break;

            case Sprite:
                noop();
                spriteComponent_t *s = (spriteComponent_t *)cur->components[i]->component;
                s->draw((void*)s);
                break;

            case Collision:
                noop();
                colliderComponent_t *c = (colliderComponent_t *)cur->components[i]->component;
                c->draw((void*)c);
                break;

            case KeyBoard:
                noop();
                keyboardComponent_t *k = (keyboardComponent_t *)cur->components[i]->component;
                k->draw((void*)k);
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
    e->active = 1;
    e->next = e->prev = NULL;
    e->compCount = 0;
    e->id = eid;
    eid++;
    e->components = calloc(MAXCOMPONENTS, sizeof(Components_t*));
    e->update = entity_update;
    e->draw = entity_draw;
    return e;
}



Components_t *create_component(void *c, compTypes_t type){
    Components_t *component = malloc(sizeof(Components_t));

    component->type = type;
    component->component = c;
    return component;
}


void add_component(entities_t *e, compTypes_t type, void *c){
 
    //get correct component and tie it the current entity
    switch(type){
        case Transform:
            noop();  
            transformComponent_t *t = (transformComponent_t*)c;
            t->init((void*)e, c);
            break;
        case Sprite:
            noop();
            spriteComponent_t *s = (spriteComponent_t *)c;
            s->init((void*)e, c);
            break;
        case Collision:
            noop();
            colliderComponent_t *co = (colliderComponent_t *)c;
            co->init((void*)e, c);
            break;

        case KeyBoard:
            noop();
            keyboardComponent_t *k = (keyboardComponent_t *)c;
            k->init((void*)e, k);
            break;
        default:
            break;
    }

    //add component to the entity
    e->components[e->compCount] = create_component(c, type);
    e->compCount++;  
   
    return;
}

void *get_component(void* e, compTypes_t type){
    entities_t *en = (entities_t *)e;
    void *component;
    for(int i = 0; i < en->compCount || en->components[i] == NULL; i++){
        if(en->components[i]->type == type){
            component = en->components[i]->component;
            return component;
        }
    }
    return NULL;
}


void destroy_entity(entities_t *e){
    for(int i = 0; i < e->compCount; i++){

        free(e->components[i]->component);
        free(e->components[i]);
    }
    free(e);
}


