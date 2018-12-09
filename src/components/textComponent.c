#include "../../includes/textComponent.h"
#include "../../includes/textureManager.h"
#include "../../includes/statComponent.h"
#include "../../includes/entities.h"
#include "../../includes/renderer.h"
#include <assert.h>
#include <string.h>
static void change_texture(void *c, char *text);

void on_next_text(void *component, int data){
    

    char tmp[20];
    sprintf(tmp, "%d", data);
    change_texture(component,tmp);
}

void on_complete_text(void *component, void *data){
    change_texture(component, "");
    return;
}





textComponent_t *text_create(char *text){

    textComponent_t *t = malloc(sizeof(textComponent_t));
    assert(t != NULL);
    t->observer = observer_create(on_next_text, on_complete_text, t);
    t->texture = NULL;
    
    return t;
}

void text_init(void *e, void *c){

    textComponent_t *t = (textComponent_t *)c;
    
    t->t = (transformComponent_t *)get_component(e, Transform);
    change_texture(t, "");
    return;
}

void text_update(void *c){
    return;
}

void text_draw(void *c){
    textComponent_t *t = (textComponent_t *)c;
    SDL_RenderCopy(renderer, t->texture, NULL, &t->textureRec);
}

void text_destroy(void *c){

    textComponent_t *t = (textComponent_t *)c;
    if(t->texture != NULL)
        SDL_DestroyTexture(t->texture);
    free((t->observer));
    free(t);    
    return;
}


static void change_texture(void *c, char *text){
    textComponent_t *t = (textComponent_t *)c;
    SDL_Color color = {0, 0 ,0 ,0};
    if(t->texture != NULL)
        SDL_DestroyTexture(t->texture);
    t->texture = load_UI_text(text, color);
    t->textureRec.x = t->t->pos.x;
    t->textureRec.y = t->t->pos.y;
    SDL_QueryTexture(t->texture, NULL, NULL, &t->textureRec.w, &t->textureRec.h);
    return;
}