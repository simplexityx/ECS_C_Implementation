#include "../includes/spriteComponent.h"
#include "entities.h"
void sprite_init(void *e, void *c){
    spriteComponent_t *s = (spriteComponent_t*)c;
    s->entity = e;
    transformComponent_t *t = (transformComponent_t*)get_component(s->entity, Transform);
    s->t = t;
    s->dst.x = t->x;
    s->dst.y = t->y;
    return;
}

void sprite_draw(void *c){
    spriteComponent_t *s = (spriteComponent_t*)c;
    
    draw_texture(s->tex, s->src, s->dst);

    return;
}

void sprite_update(void *c){
    spriteComponent_t *s = (spriteComponent_t*)c;
    
    s->dst.x = s->t->x;
    s->dst.y = s->t->y;
    return;
}


spriteComponent_t *sprite_create(const char *filepath){

    spriteComponent_t *s = malloc(sizeof(spriteComponent_t));
    s->init = sprite_init;
    s->draw = sprite_draw;
    s->update = sprite_update;
    s->src.x = s->src.y = 0;
    s->src.w = s->src.h = s->dst.w = s->dst.h = 32;
    
    s->tex = load_texture(filepath);

    return s;
}
