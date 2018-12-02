#include "../includes/observable.h"


observer_t *observer_create(on_next_t on_next, on_complete_t on_complete, void *type){
    observer_t *o = malloc(sizeof(observer_t));
    o->on_complete = on_complete;
    o->on_next = on_next;
    o->type = type;
    
    return o;
}



observable_t *observable_create(subscribe_t subscribe, unsubscribe_t unsubscribe){
    observable_t *o = malloc(sizeof(observable_t));
    o->subscribe = subscribe;
    o->unsubscribe = unsubscribe;
    o->observer = NULL;
    return o;
}

void observable_destroy(observable_t *observable){
    free(observable);
}
