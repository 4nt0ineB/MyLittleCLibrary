

#include "../../include/Tests/MLCL_LinkedList_test.h"
#include "../../include/Tests/MLCL_exceptions.h"
#include "../../include/MLCL_LinkedList.h"

int run_all_linked_list_tests(){
    printf("### Running all LinkedList tests\n");
    if(!test_new_ll())
        return 0;
    if(!test_ll_prepend())
        return 0;
    if(!test_ll_append())
        return 0;
    if(!test_search())
        return 0;
    if(!test_del())
        return 0;
    if(!test_del())
        return 0;
    if(!test_ll_filter())
        return 0;
    if(!test_ll_map())
        return 0;
    if(!test_ll_shift())
        return 0;
    if(!test_ll_pop())
        return 0;

    return 1;
}

int test_new_ll(){
    LinkedList ll;
    int x;
    printf("- test_new_ll\n");
    x = 5;
    ll = new_ll(&x, new_type_descriptor(int_manifest));
    if(!ll)
        MLCL_ERR(1, MLCL_ERR_ALLOC);
    if((*(int *) ll->data) != 5)
        MLCL_ERR(1, MLCL_ERR_NEQ);
    MLCL_OK();
    return 1;
}

int test_ll_prepend(){
    printf("- test_ll_prepend\n");
    MLCL_OK();
    return 1;
}

int test_ll_append(){
    printf("- test_ll_append\n");
    MLCL_OK();
    return 1;
}

int test_search(){
    printf("- test_search\n");
    MLCL_OK();
    return 1;
}

int test_ll_del(){
    printf("- test_ll_del\n");
    MLCL_OK();
    return 1;
}

int test_del(){
    printf("- test_del\n");
    MLCL_OK();
    return 1;
}

int test_ll_filter(){
    printf("- test_ll_filter\n");
    MLCL_OK();
    return 1;
}

int test_ll_map(){
    printf("- test_ll_map\n");
    MLCL_OK();
    return 1;
}

int test_ll_shift(){
    printf("- test_ll_shift\n");
    MLCL_OK();
    return 1;
}

int test_ll_pop(){
    printf("- test_ll_pop\n");
    MLCL_OK();
    return 1;
}