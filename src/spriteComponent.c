#include "../includes/spriteComponent.h"
#include "entities.h"
void sprite_init(void *e, void *c){
    spriteComponent_t *s = (spriteComponent_t*)c;
    s->entity = e;
    return;
}

void sprite_draw(void *c){
    spriteComponent_t *s = (spriteComponent_t*)c;
    
    draw_texture(s->tex, s->src, s->dst,  s->rend);

    return;
}

void sprite_update(void *c){
    spriteComponent_t *s = (spriteComponent_t*)c;
    transformComponent_t *t = (transformComponent_t*) get_component(s->entity, Transform);
    if(t == NULL){
        printf("something went terribly wrong\n");
        return;
    }
    s->dst.x = t->x;
    s->dst.y = t->y;
    return;
}


spriteComponent_t *sprite_create(const char *filepath, SDL_Renderer *rend){

    spriteComponent_t *s = malloc(sizeof(spriteComponent_t));
    s->init = sprite_init;
    s->draw = sprite_draw;
    s->update = sprite_update;
    s->src.x = s->src.y = 0;
    s->src.w = s->src.h = s->dst.w = s->dst.h = 32;
    s->rend = rend;
    s->tex = load_texture(filepath, rend);

    return s;
}
