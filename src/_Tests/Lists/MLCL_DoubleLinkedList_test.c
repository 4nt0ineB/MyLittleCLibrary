/*
 *   This file is part of the MLCL Library.
 *   Antoine Bastos 2022
 *
 *    This Library is free software: you can redistribute it and/or modify
 *    it under the terms of the GNU General Public License as published by
 *    the Free Software Foundation, either version 3 of the License, or
 *    (at your option) any later version.
 *
 *    This Library is distributed in the hope that it will be useful,
 *    but WITHOUT ANY WARRANTY; without even the implied warranty of
 *    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *    GNU General Public License for more details.
 *
 *    You should have received a copy of the GNU General Public License
 *    along with this Library.  If not, see <http://www.gnu.org/licenses/>.
  */

#include "../../../include/_Tests/Lists/MLCL_DoubleLinkedList_test.h"
#include "../../../include/_Tests/MLCL_exceptions.h"
#include "../../../include/Lists/MLCL_DoubleLinkedList.h"
#include "../../../include/MLCL_basic_types.h"


int run_all_double_linked_list_tests(){
    printf("▒▒▒ Running all DoubleLinkedList tests ▒▒▒\n");
    MLCL_TEST(test_new_double_linked_list, "test_new_double_linked_list")
    MLCL_TEST(test_double_linked_list_ordered_add, "test_double_linked_list_ordered_add")
    MLCL_TEST(test_double_linked_list_prepend, "test_double_linked_list_prepend")
    MLCL_TEST(test_double_linked_list_append, "test_double_linked_list_append")
    MLCL_TEST(test_double_linked_list_search, "test_double_linked_list_search")
    MLCL_TEST(test_double_linked_list_remove, "test_double_linked_list_remove")
    MLCL_TEST(test_double_linked_list_shift, "test_double_linked_list_shift")
    MLCL_TEST(test_double_linked_list_pop, "test_double_linked_list_pop")
    MLCL_TEST(test_double_linked_list_filter, "test_double_linked_list_filter")
    return 1;
}

int test_new_double_linked_list(){
    DoubleLinkedList ll;
    int x;
    x = 5;
    ll = new_double_linked_list(&x, int_m);
    if(!ll)
        MLCL_ERR(1, MLCL_ERR_ALLOC)
    if((*(int *) ll->data) != 5)
        MLCL_ERR(2, MLCL_ERR_NEQ)
    ll->d->free(&ll);
    return 1;
}

int test_double_linked_list_ordered_add(){
    DoubleLinkedList dll;
    int x;
    x = 5;
    dll = new_double_linked_list(&x, int_m);
    x = 6;
    dll->d->ordered_add(&dll, &x);
    x = 2;
    dll->d->ordered_add(&dll, &x);
    x = 3;
    dll->d->ordered_add(&dll, &x);

    x = 2;
    if(dll->d->type_descriptor->cmp(&x, dll->data) != 0)
        MLCL_ERR(1, MLCL_ERR_TRUE)
    x = 3;
    if(dll->d->type_descriptor->cmp(&x, dll->next->data) != 0)
        MLCL_ERR(2, MLCL_ERR_TRUE)
    x = 5;
    if(dll->d->type_descriptor->cmp(&x, dll->next->next->data) != 0)
        MLCL_ERR(3, MLCL_ERR_TRUE)
    x = 6;
    if(dll->d->type_descriptor->cmp(&x, dll->next->next->next->data) != 0)
        MLCL_ERR(4, MLCL_ERR_TRUE)
    dll->d->free(&dll);
    return 1;
}

int test_double_linked_list_prepend(){
    DoubleLinkedList ll;
    float x;
    x = 5.2f;
    ll = new_double_linked_list(&x, float_m);
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

int test_double_linked_list_append(){
    DoubleLinkedList ll;
    float x;
    x = 5.2f;
    ll = new_double_linked_list(&x, float_m);
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

int test_double_linked_list_insert(){
    /* @Todo Insert test*/
    return 1;
}

int test_double_linked_list_search(){
    DoubleLinkedList ll;
    int x;
    x = 5;
    ll = new_double_linked_list(&x, int_m);
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

int test_double_linked_list_remove(){
    DoubleLinkedList ll;
    int x;
    x = 5;
    ll = new_double_linked_list(&x, int_m);
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

int test_double_linked_list_shift(){
    DoubleLinkedList ll;
    int x;
    void * data;
    x = 5;
    ll = new_double_linked_list(&x, int_m);
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

int test_double_linked_list_pop(){
    DoubleLinkedList ll;
    int x;
    void * data;
    x = 5;
    ll = new_double_linked_list(&x, int_m);
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

int test_double_linked_list_filter(){
    /* @Todo filter test */
    return 1;
}
