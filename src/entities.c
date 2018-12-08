#include "../includes/entities.h"
#include <assert.h>
void entity_update(void *e);
void entity_draw(void *e);
void entity_destroy(void *e);
static inline int checkmap(uint32_t map, int idx);
static inline void addmap(uint32_t *map, int idx);
static inline void removemap(uint32_t *map, int idx);

component_t *component_create(void *cData, init_t init, update_t update, draw_t draw, destroy_t destroy, compTypes_t type){

    component_t *c = malloc(sizeof(component_t));

    c->cData = cData;
    c->init = init;
    c->update = update;
    c->draw = draw;
    c->destroy = destroy;
    c->type = type;

    c->owner = NULL;

    return c;
}

entities_t *entities_create(){

    entities_t *e = malloc(sizeof(entities_t));

    e->active = 1;

    e->next = e->prev = NULL;

    e->update = entity_update;
    e->draw = entity_draw;
    e->destroy = entity_destroy;

    e->components = calloc(MAXCOMPONENTS, sizeof(component_t*));

    return e;
}




void add_component(entities_t *entity, component_t *component){
    
    component->init(entity, component->cData);
    component->owner = entity;   
    entity->components[component->type] = component;
    
    return;
}

void *get_component(entities_t *entity, compTypes_t type){
    
    if(!has_component(entity, type)){
        return NULL;
    }
    return entity->components[type]->cData;    
}

int has_component(entities_t *entity, compTypes_t type){
    if(entity->components[type] == NULL)
        return 0;
    else
        return 1;
}

void remove_component(entities_t *entity, compTypes_t type){
    
    assert(has_component(entity, type) == 1);

    removemap(&entity->map, type);
    free(entity->components[type]->cData);
    free(entity->components[type]);
    entity->components[type] = NULL;
    return;
}





void entity_update(void *e){

    entities_t *en = (entities_t *)e; 
    for(int i = 0; i < MAXCOMPONENTS; i++){
        if(en->components[i] != NULL)
            en->components[i]->update(en->components[i]->cData);
    }
}

void entity_draw(void *e){

    entities_t *en = (entities_t *)e;
    for(int i = 0; i < MAXCOMPONENTS; i++){
        if(en->components[i] != NULL)
            en->components[i]->draw(en->components[i]->cData);
    }
}




void entity_destroy(void *e){
    entities_t *en = (entities_t *)e;
    for(int i = 0; i < MAXCOMPONENTS; i++){
        if(en->components[i] != NULL){
            en->components[i]->destroy(en->components[i]->cData);
            free(en->components[i]);
        }  
    }
    free(en->components);
    free(e);
}




static inline int checkmap(uint32_t map, int idx){
    return map & (1 << idx);
}

static inline void addmap(uint32_t *map, int idx){
    *map |= (1 << idx);
    return;
}

static inline void removemap(uint32_t *map, int idx){
    *map ^= (1 << idx);
    return;
}