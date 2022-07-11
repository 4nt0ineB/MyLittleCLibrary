

#include "../../include/Tests/MLCL_LinkedList_test.h"
#include "../../include/Tests/MLCL_exceptions.h"
#include "../../include/MLCL_LinkedList.h"
#include "../../include/MLCL_basic_types.h"


int run_all_linked_list_tests(){
    printf("|> Running all LinkedList tests\n");
    if(!test_new_ll())
        return 0;
    if(!test_ll_prepend())
        return 0;
    if(!test_ll_append())
        return 0;
    if(!test_search())
        return 0;
    if(!test_ll_del())
        return 0;
    if(!test_ll_shift())
        return 0;
    if(!test_ll_pop())
        return 0;
    if(!test_ll_filter())
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
        MLCL_ERR(1, MLCL_ERR_ALLOC)
    if((*(int *) ll->data) != 5)
        MLCL_ERR(2, MLCL_ERR_NEQ)
    ll->d->free(&ll);
    MLCL_OK();
    return 1;
}

int test_ll_prepend(){
    LinkedList ll;
    float x;
    printf("- test_ll_prepend\n");
    x = 5.2f;
    ll = new_ll(&x, new_type_descriptor(float_manifest));
    if(!ll)
        MLCL_ERR(1, MLCL_ERR_ALLOC)
    x = 7.9f;
    ll->d->prepend(&ll, &x);
    if(!ll)
        MLCL_ERR(2, MLCL_ERR_ALLOC)
    if(!ll->next)
        MLCL_ERR(3, MLCL_ERR_ALLOC)
    if((* (float *) ll->next->data) !=  5.2f)
        MLCL_ERR(4, MLCL_ERR_EQ)
    if((* (float *) ll->data) != 7.9f)
        MLCL_ERR(5, MLCL_ERR_EQ)
    ll->d->free(&ll);
    MLCL_OK();
    return 1;
}

int test_ll_append(){
    LinkedList ll;
    float x;
    printf("- test_ll_append\n");
    x = 5.2f;
    ll = new_ll(&x, new_type_descriptor(float_manifest));
    if(!ll)
    MLCL_ERR(1, MLCL_ERR_ALLOC)
    x = 7.9f;
    ll->d->append(&ll, &x);
    if(!ll)
        MLCL_ERR(2, MLCL_ERR_ALLOC)
    if(!ll->next)
        MLCL_ERR(3, MLCL_ERR_ALLOC)
    if((* (float *) ll->next->data) != 7.9f)
        MLCL_ERR(4, MLCL_ERR_EQ);
    if((* (float *) ll->data) != 5.2f)
        MLCL_ERR(5, MLCL_ERR_EQ)
    ll->d->free(&ll);
    MLCL_OK();
    return 1;
}

int test_insert(){
    /* @Todo Insert test*/
    return 1;
}

int test_search(){
    LinkedList ll;
    int x;
    printf("- test_search\n");
    x = 5;
    ll = new_ll(&x, new_type_descriptor(int_manifest));
    if(!ll)
        MLCL_ERR(1, MLCL_ERR_ALLOC)
    x = 6;
    ll->d->prepend(&ll, &x);
    x = 7;
    ll->d->prepend(&ll, &x);
    if((* (int *) ll->data) != 7)
        MLCL_ERR(2, MLCL_ERR_EQ)
    if(!ll->d->search(ll, &x))
        MLCL_ERR(3, MLCL_ERR_TRUE)
    ll->d->free(&ll);
    MLCL_OK();
    return 1;
}

int test_ll_del(){
    LinkedList ll;
    int x;
    printf("- test_ll_del\n");
    x = 5;
    ll = new_ll(&x, new_type_descriptor(int_manifest));
    if(!ll)
        MLCL_ERR(1, MLCL_ERR_ALLOC)
    x = 6;
    ll->d->prepend(&ll, &x);
    ll->d->del(&ll, &x);
    if((* (int *) ll->data) != 5)
        MLCL_ERR(2, MLCL_ERR_EQ)
    x = 5;
    ll->d->del(&ll, &x);
    if(ll)
        MLCL_ERR(3, MLCL_ERR_TRUE)
    if(ll)
        ll->d->free(&ll);
    MLCL_OK();
    return 1;
}

int test_ll_shift(){
    LinkedList ll;
    int x;
    void * data;
    printf("- test_ll_shift\n");
    x = 5;
    ll = new_ll(&x, new_type_descriptor(int_manifest));
    if(!ll)
        MLCL_ERR(1, MLCL_ERR_ALLOC);
    x = 6;
    ll->d->prepend(&ll, &x);
    data = ll->d->shift(&ll);
    if((* (int *) data) != 6)
        MLCL_ERR(2, MLCL_ERR_TRUE);
    if(!ll)
        MLCL_ERR(3, MLCL_ERR_FALSE);
    ll->d->free(&ll);
    free(data);
    MLCL_OK();
    return 1;
}

int test_ll_pop(){
    LinkedList ll;
    int x;
    void * data;
    printf("- test_ll_pop\n");
    x = 5;
    ll = new_ll(&x, new_type_descriptor(int_manifest));
    if(!ll)
        MLCL_ERR(1, MLCL_ERR_ALLOC);
    x = 6;
    ll->d->prepend(&ll, &x);
    data = ll->d->pop(&ll);
    if((* (int *) data) != 5)
        MLCL_ERR(2, MLCL_ERR_TRUE);
    if(!ll)
        MLCL_ERR(3, MLCL_ERR_FALSE);
    ll->d->free(&ll);
    free(data);
    MLCL_OK();
    return 1;
}

int test_ll_filter(){
    printf("- test_ll_filter\n");
    /* @Todo filter test */
    MLCL_OK();
    return 1;
}
