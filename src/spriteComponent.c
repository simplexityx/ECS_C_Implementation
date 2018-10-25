#include "../includes/spriteComponent.h"


void sprite_draw(void *c){
    spriteComponent_t *s = (spriteComponent_t*)c;
    printf("drawing spriteComponent, got the sprite from filepath: %s",s->filepath);
    return;
}

void sprite_update(void *c){
    printf("updating spritecomponent, this does nothing %d\n", *(int*)c);
    return;
}


spriteComponent_t *sprite_create(){

    spriteComponent_t *s = malloc(sizeof(spriteComponent_t));
    s->draw = sprite_draw;
    s->update = sprite_update;
    s->filepath = "teststring";

    return s;
}
