#ifndef OBSERVABLE_H
#define OBSERVABLE_H

typedef void (*subscribe_t)(void *, void *);
typedef void (*on_next_t)(void *, int);
typedef void (*on_complete_t)(void *, void *);
typedef void (*unsubscribe_t)(void *, void *);
#include "headers.h"
/*
    observer: on_next and on_complete is passed into a observable the observable calls these functions
    to change the state for the object tied to the observable which is given with the "type field"
*/
typedef struct observer observer_t;
struct observer{
    on_next_t on_next;
    on_complete_t on_complete;
    void *type;
};



/*
    Observable: subscribe, adds an observable to the list of observers.
    the observers is an array which saves all observers observing the current observable.
    unsubscribe removes a specific observer from the observable.
*/
typedef struct observable observable_t;
struct observable{
    subscribe_t subscribe;
    unsubscribe_t unsubscribe;
    observer_t *observer;
};

observer_t *observer_create(on_next_t on_next, on_complete_t on_complete, void *type);
observable_t *observable_create(subscribe_t subscribe, unsubscribe_t unsubscribe);

void observable_destroy(observable_t *observable);



#endif



