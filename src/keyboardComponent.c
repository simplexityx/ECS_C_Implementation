#include "../includes/keyboardComponent.h"
#include "../includes/renderer.h"

static int lastPosX;
static int lastPosY;

void keyboard_init(void *e, void *c){

    keyboardComponent_t *k = (keyboardComponent_t*)c;

    k->entity = e;
    k->t = get_component(e, Transform);
    k->s = get_component(e, Sprite);
    return;
}

void keyboard_update(void *c){
    keyboardComponent_t *k = (keyboardComponent_t*)c;
    
    k->keyboard_state_array = SDL_GetKeyboardState(NULL);
  
    Vector2D_t tmp = Vector2(0, 0);
    if (k->keyboard_state_array[SDL_SCANCODE_W]) {
        tmp.y -= 240;
    }
    if (k->keyboard_state_array[SDL_SCANCODE_S]) {
        tmp.y += 240;
    }
    if (k->keyboard_state_array[SDL_SCANCODE_A]) {
        tmp.x -= 240;
        k->s->flip = 1;
    }
    if (k->keyboard_state_array[SDL_SCANCODE_D]) {
        tmp.x += 240;
        k->s->flip = 0;
    }

    if(tmp.x != 0 || tmp.y != 0){
        lastPosX = tmp.x;
        lastPosY = tmp.y;
        k->s->currentState = WALK;
    }else{
        k->s->currentState = IDLE;
    }

    if (k->keyboard_state_array[SDL_SCANCODE_SPACE]){
        
        assetmanager->create_projectile(Vector2(k->t->pos.x, k->t->pos.y), Vector2(lastPosX * 2, lastPosY * 2), "magic");
    }

    k->t->set_trans(k->t, tmp.x, tmp.y);
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

