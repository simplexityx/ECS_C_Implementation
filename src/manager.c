#include "../includes/manager.h"



manager_t *manager_create(){

    manager_t *m = malloc(sizeof(manager_t));
    assert(m != NULL);
    m->currentActiveGroups = 0;
    for(int i = 0; i < MAXCOMPONENTS; i++){
        m->groups[i].head = NULL;
        m->groups[i].tail = NULL;
        m->groups[i].currentSize = 0;
    }
    return m;
}

void manager_insert(manager_t *m, entities_t *e, Groups_t group){

    if(m->groups[group].head == NULL){
        m->currentActiveGroups++;
        m->groups[group].head = m->groups[group].tail = e;
        m->groups[group].currentSize++;
        return;
    }
    entities_t *tmp = m->groups[group].tail;
    e->prev = tmp;
    tmp->next = e;
    m->groups[group].tail = e;
    m->groups[group].currentSize++;

    return;
}


void manager_update(manager_t *m, Groups_t group){

    entities_t *tmp = m->groups[group].head;
    while(tmp != NULL){
        tmp->update(tmp);
        tmp = tmp->next;
    }
    return;
}


void manager_draw(manager_t *m, Groups_t group){

    entities_t *tmp = m->groups[group].head;
    while(tmp != NULL){
        tmp->draw(tmp);
        tmp = tmp->next;
    }
    return;
}


void remove_entity(manager_t *m, entities_t *e, Groups_t group){

    
    if(e->next != NULL && e->prev != NULL){
        e->next->prev = e->prev;
        e->prev->next = e->next;
    }else if(e->next == NULL && e->prev != NULL){
        m->groups[group].tail = m->groups[group].tail->prev;
        e->prev->next = NULL;
    }else if(e->prev == NULL && e->next != NULL){
        
        m->groups[group].head = m->groups[group].head->next;
        e->next->prev = NULL;
    }else{
        m->groups[group].head = m->groups[group].tail = NULL;
    }

    e->destroy(e);
    m->groups[group].currentSize--;
    return;
}


void manager_refresh(manager_t *m){
    for(int i = 0; i < MAXCOMPONENTS; i++){
        entities_t * tmp = m->groups[i].head;
        while(tmp != NULL){
            if(tmp->active == 0){
                remove_entity(m, tmp, i);
            }
            tmp = tmp->next;

        }
        if(tmp != NULL){
            printf("ever in here!?!?\n");
            free(tmp);
        }
        
    }
}

void destroy_manager(manager_t *m){

    for(int i = 0; i < m->currentActiveGroups; i++){

        entities_t *tmp = m->groups[i].head;
        while(tmp != NULL){
            tmp->active = 0;
            tmp = tmp->next;
        }
    }
    manager_refresh(m);
    free(m);
}


void print_manager(manager_t *m){

    for(int i = 0; i < m->currentActiveGroups; i++){
        entities_t *tmp = m->groups[i].head;
        while(tmp != NULL){
            tmp = tmp->next;
        }
    }
}


entities_t *get_group(manager_t *m, Groups_t group){
    return m->groups[group].head;
}
