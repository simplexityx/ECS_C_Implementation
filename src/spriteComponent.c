#include "../includes/spriteComponent.h"
#include "entities.h"
void sprite_init(void *e, void *c){
    spriteComponent_t *s = (spriteComponent_t*)c;
    s->entity = e;
    return;
}

void sprite_draw(void *c){
    spriteComponent_t *s = (spriteComponent_t*)c;
    entities_t *e = (entities_t*)s->entity;
    printf("drawing spriteComponent, got the sprite from filepath: %s and this component belongs to entity: %d\n",s->filepath, e->id);
    return;
}

void sprite_update(void *c){
    spriteComponent_t *s = (spriteComponent_t*)c;

    transformComponent_t *t = (transformComponent_t*)get_component(s->entity, Transform);

    printf("coordinates: %d, %d\n", t->x, t->y);
    t->x *= 10;
    return;
}


spriteComponent_t *sprite_create(){

    spriteComponent_t *s = malloc(sizeof(spriteComponent_t));
    s->init = sprite_init;
    s->draw = sprite_draw;
    s->update = sprite_update;
    s->filepath = "teststring";

    return s;
}
