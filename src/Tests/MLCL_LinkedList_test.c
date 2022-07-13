

#include "../../include/Tests/MLCL_LinkedList_test.h"
#include "../../include/Tests/MLCL_exceptions.h"
#include "../../include/MLCL_LinkedList.h"
#include "../../include/MLCL_basic_types.h"


int run_all_linked_list_tests(){
    printf("▒▓ Running all LinkedList tests\n");
    MLCL_TEST(test_new_linked_list)
    MLCL_TEST(test_linked_list_prepend)
    MLCL_TEST(test_linked_list_append)
    MLCL_TEST(test_linked_list_search)
    MLCL_TEST(test_linked_list_remove)
    MLCL_TEST(test_linked_list_shift)
    MLCL_TEST(test_linked_list_pop)
    MLCL_TEST(test_linked_list_filter)
    return 1;
}

int test_new_linked_list(){
    LinkedList ll;
    int x;
    printf("├ test_new_linked_list:");
    x = 5;
    ll = new_linked_list(&x, new_type_descriptor(int_manifest));
    if(!ll)
        MLCL_ERR(1, MLCL_ERR_ALLOC)
    if((*(int *) ll->data) != 5)
        MLCL_ERR(2, MLCL_ERR_NEQ)
    ll->d->free(&ll);
    return 1;
}

int test_linked_list_prepend(){
    LinkedList ll;
    float x;
    printf("├ test_linked_list_prepend:");
    x = 5.2f;
    ll = new_linked_list(&x, new_type_descriptor(float_manifest));
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
    return 1;
}

int test_linked_list_append(){
    LinkedList ll;
    float x;
    printf("├ test_linked_list_append:");
    x = 5.2f;
    ll = new_linked_list(&x, new_type_descriptor(float_manifest));
    if(!ll)
    MLCL_ERR(1, MLCL_ERR_ALLOC)
    x = 7.9f;
    ll->d->append(&ll, &x);
    if(!ll)
        MLCL_ERR(2, MLCL_ERR_ALLOC)
    if(!ll->next)
        MLCL_ERR(3, MLCL_ERR_ALLOC)
    if((* (float *) ll->next->data) != 7.9f)
        MLCL_ERR(4, MLCL_ERR_EQ)
    if((* (float *) ll->data) != 5.2f)
        MLCL_ERR(5, MLCL_ERR_EQ)
    ll->d->free(&ll);
    return 1;
}

int test_linked_list_insert(){
    /* @Todo Insert test*/
    return 1;
}

int test_linked_list_search(){
    LinkedList ll;
    int x;
    printf("├ test_linked_list_search:");
    x = 5;
    ll = new_linked_list(&x, new_type_descriptor(int_manifest));
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
    return 1;
}

int test_linked_list_remove(){
    LinkedList ll;
    int x;
    printf("├ test_linked_list_remove:");
    x = 5;
    ll = new_linked_list(&x, new_type_descriptor(int_manifest));
    if(!ll)
        MLCL_ERR(1, MLCL_ERR_ALLOC)
    x = 6;
    ll->d->prepend(&ll, &x);
    ll->d->remove(&ll, &x);
    if((* (int *) ll->data) != 5)
        MLCL_ERR(2, MLCL_ERR_EQ)
    x = 5;
    ll->d->remove(&ll, &x);
    if(ll)
        MLCL_ERR(3, MLCL_ERR_TRUE)
    if(ll)
        ll->d->free(&ll);
    return 1;
}

int test_linked_list_shift(){
    LinkedList ll;
    int x;
    void * data;
    printf("├ test_linked_list_shift:");
    x = 5;
    ll = new_linked_list(&x, new_type_descriptor(int_manifest));
    if(!ll)
        MLCL_ERR(1, MLCL_ERR_ALLOC)
    x = 6;
    ll->d->prepend(&ll, &x);
    data = ll->d->shift(&ll);
    if((* (int *) data) != 6)
        MLCL_ERR(2, MLCL_ERR_TRUE)
    if(!ll)
        MLCL_ERR(3, MLCL_ERR_FALSE)
    ll->d->free(&ll);
    free(data);
    return 1;
}

int test_linked_list_pop(){
    LinkedList ll;
    int x;
    void * data;
    printf("├ test_linked_list_pop:");
    x = 5;
    ll = new_linked_list(&x, new_type_descriptor(int_manifest));
    if(!ll)
        MLCL_ERR(1, MLCL_ERR_ALLOC)
    x = 6;
    ll->d->prepend(&ll, &x);
    data = ll->d->pop(&ll);
    if((* (int *) data) != 5)
        MLCL_ERR(2, MLCL_ERR_TRUE)
    if(!ll)
        MLCL_ERR(3, MLCL_ERR_FALSE)
    ll->d->free(&ll);
    free(data);
    return 1;
}

int test_linked_list_filter(){
    printf("├ test_linked_list_filter:");
    /* @Todo filter test */
    return 1;
}
