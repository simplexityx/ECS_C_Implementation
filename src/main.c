#include <stdio.h>
#include "../includes/manager.h"
#include <stdarg.h>






int main(){

    manager_t *m = manager_create();

    entities_t *entity = entities_create();
    entities_t *entity1 = entities_create();
    entities_t *entity2 = entities_create();
    entities_t *entity3 = entities_create();
    entities_t *entity4 = entities_create();
    
    add_component(entity, Transform);
    add_component(entity1, Transform);
    add_component(entity2, Transform);
    add_component(entity3, Transform);
    add_component(entity4, Transform);


    manager_insert(m, entity, GROUP1);
    manager_insert(m, entity1, GROUP1);
    manager_insert(m, entity2, GROUP2);
    manager_insert(m, entity3, GROUP2);
    manager_insert(m, entity4, GROUP3);
    
    manager_update(m, GROUP2);
    manager_update(m, GROUP1);
    manager_update(m, GROUP3);
    entity4->active = 0;
    manager_refresh(m);
    manager_update(m, GROUP3);
    print_manager(m);


    return 0;
}


