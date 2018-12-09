#include "../../includes/transformComponent.h"
#include "../../includes/test.h"

int tests_run = 0;

static char* transformComponentTest(){

    //test create function
    transformComponent_t *transform = transform_create(Vector2(500, 500), Vector2(20, 20), 300);
    mu_assert("error transform not allocated!", transform != NULL);
    mu_assert("error wrong intial variables!", transform->pos.x == 500 && transform->pos.y == 500 && transform->speed.x == 20 && transform->speed.y == 20 && transform->moveSpeed == 300);

    //test set speed function
    transform->set_speed(transform, 300, 200);

    mu_assert("error wrong speed set!", transform->speed.x == 300 && transform->speed.y == 200);
    //test set point function


    //test deletion
    transform_destroy(transform);
    
    return 0;
}





static char *all_tests(){

    mu_run_test(transformComponentTest);
    return 0;
}

int main(){

    char *result = all_tests();
    if(result != 0){
        printf("%s\n", result);
    }else{
        printf("tests passed!\n");
    }
    return result != 0;
}

