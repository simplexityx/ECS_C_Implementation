#include "../includes/keyboardComponent.h"
#include "renderer.h"

void keyboard_init(void *e, void *c){

    keyboardComponent_t *k = (keyboardComponent_t*)c;

    k->entity = e;
    k->t = get_component(e, Transform);
    return;
}

void keyboard_update(void *c){
    keyboardComponent_t *k = (keyboardComponent_t*)c;
    
    k->keyboard_state_array = SDL_GetKeyboardState(NULL);
    int tmpX = 0, tmpY = 0;
    if (k->keyboard_state_array[SDL_SCANCODE_W]) {
        tmpY -= 5;
    }
    if (k->keyboard_state_array[SDL_SCANCODE_S]) {
        tmpY += 5;
    }
    if (k->keyboard_state_array[SDL_SCANCODE_A]) {
        tmpX -= 5;
    }
    if (k->keyboard_state_array[SDL_SCANCODE_D]) {
        tmpX += 5;
    }
    if (k->keyboard_state_array[SDL_SCANCODE_SPACE]){
        
    }

    k->t->set_trans(k->t, tmpX, tmpY);
    return;
}

void keyboard_draw(void *c){
    return;
}




keyboardComponent_t *keyboard_create(){
    keyboardComponent_t *k = malloc(sizeof(keyboardComponent_t));
    k->init = keyboard_init;
    k->update = keyboard_update;
    k->draw = keyboard_draw;
    return k;
}

