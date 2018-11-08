#include "../includes/keyboardComponent.h"
#include "renderer.h"

static int lastPosX;
static int lastPosY;

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

    if(tmpX != 0 || tmpY != 0){
        lastPosX = tmpX;
        lastPosY = tmpY;
    }

    if (k->keyboard_state_array[SDL_SCANCODE_SPACE]){
        assetmanager->create_obstacle(k->t->x, k->t->y, lastPosX, lastPosY, "Assets/magic.png");
    }

    k->t->set_trans(k->t, tmpX, tmpY);
    return;
}

void keyboard_draw(void *c){
    return;
}




keyboardComponent_t *keyboard_create(){
    static int i;
    keyboardComponent_t *k = malloc(sizeof(keyboardComponent_t));
    k->init = keyboard_init;
    k->update = keyboard_update;
    k->draw = keyboard_draw;
    if(i == 0){
        idxgiver++;
        i = idxgiver;
    }
    k->idx = i;
    return k;
}

