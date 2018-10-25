#include "../includes/manager.h"


manager_t *manager_create(){

    manager_t *m = malloc(sizeof(manager_t));
    m->head = m->tail = NULL;
    m->size = 0;
    return m;
}

void add_entity(manager_t *m, entities_t *e){

    if(m->head == NULL){
        m->head = m->tail = e;
        m->size++;
        return;
    }

    entities_t *tmp = m->tail;
    e->prev = tmp;
    tmp->next = e;
    m->tail = e;

    return;
}

void remove_entity(manager_t *m, entities_t *e){

    if(e->next != NULL && e->prev != NULL){
        e->next->prev = e->prev;
        e->prev->next = e->next;
    }else if(e->next == NULL && e->prev != NULL){
        m->head = m->tail->prev;
        e->prev->next = NULL;
    }else if(e->prev == NULL && e->next != NULL){
        m->head = m->head->next;
        e->next->prev = NULL;
    }else{
        m->head = m->tail = NULL;
    }

    destroy_entity(e);
    m->size--;
    return;
}

void manager_refresh(manager_t *m){

    entities_t *tmp = m->head;
    while(tmp != NULL){
        if(tmp->active == 0){
            remove_entity(m, tmp);
        }
        tmp = tmp->next;
    }
    return;
}

//destroys everything
void destroy_manager(manager_t *m){
    entities_t *tmp = m->head;
    while(tmp != NULL){
        tmp->active = 0;
        tmp = tmp->next;
    }
    manager_refresh(m);
    free(m);
}


void print_manager(manager_t *m){

    if(m->head == NULL)
        printf("manager is empty\n");
    entities_t *tmp = m->head;
    while(tmp != NULL){
        printf("%d\n", tmp->id);
        tmp = tmp->next;
    }
    return;
}
