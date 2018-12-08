#include "../../includes/spriteComponent.h"
#include "../../includes/entities.h"
#include "../../includes/renderer.h"
#include <assert.h>



void sprite_init(void *e, void *c){

    spriteComponent_t *s = (spriteComponent_t*)c;
    transformComponent_t *t = (transformComponent_t*)get_component(e, Transform);
    s->t = t;
    s->dst.x = t->pos.x;
    s->dst.y = t->pos.y;
    return;
}

void sprite_draw(void *c){
    spriteComponent_t *s = (spriteComponent_t*)c;
    
    draw_texture(s->tex, s->src, s->dst, s->flip);
    
    return;
}

void sprite_update(void *c){
    spriteComponent_t *s = (spriteComponent_t*)c;
    
    if(s->flags == 1){
        s->src.y = s->currentState * s->src.h;
        s->src.x = (s->currentFrame++%FRAMESX) * s->src.w;
    }
    
    s->dst.x = s->t->pos.x;
    s->dst.y = s->t->pos.y;
    return;
}

void sprite_destroy(void *c){
    free(c);
}


void set_texture(void *c, char *name){
    spriteComponent_t *s = (spriteComponent_t*)c;
    s->tex = assetmanager->get_tex(name);
    return;    
}


spriteComponent_t *sprite_create(const char *texName, uint32_t flags){
    spriteComponent_t *s = malloc(sizeof(spriteComponent_t));
    assert(s != NULL);

    s->src.x = s->src.y = 0;
    s->tex = assetmanager->get_tex(texName);
    
    if(flags == 0){
        SDL_QueryTexture(s->tex, NULL, NULL, &s->src.w, &s->src.h);
        s->dst.w = s->src.w;
        s->dst.h = s->src.h;
        
    }else{
        s->src.w = s->src.h = s->dst.w = s->dst.h = 32;
    }
    
    
    
    s->flip = 0;
    s->currentFrame = 0;
    s->currentState = IDLE;
    s->flags = flags;
    s->set_tex = set_texture;
    return s;
}
