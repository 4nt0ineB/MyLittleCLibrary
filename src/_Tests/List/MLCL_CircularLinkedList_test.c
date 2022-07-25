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

#include "../../../include/_Tests/List/MLCL_CircularLinkedList_test.h"

#include "../../../include/_Tests/MLCL_exceptions.h"
#include "../../../include/MLCL_basic_types.h"
#include "../../../include/List/MLCL_CircularLinkedList.h"

#include <stdio.h>

int run_all_circular_linked_list_tests(){
    printf("▒▓ Running all CircularLinkedList tests\n");
    MLCL_TEST(test_circular_linked_list_ordered_add)
    MLCL_TEST(test_circular_linked_list_prepend)
    MLCL_TEST(test_circular_linked_list_append)
    MLCL_TEST(test_circular_linked_list_search)
    MLCL_TEST(test_circular_linked_list_pop)
    MLCL_TEST(test_circular_linked_list_shift)
    return 1;
}

int test_circular_linked_list_ordered_add(){
    CircularLinkedList cll;
    int x;
    printf("├ test_circular_linked_list_ordered_add:");
    x = 5;
    cll = new_circular_linked_list(&x, int_m);
    x = 6;
    cll->d->ordered_add(&cll, &x);
    x = 2;
    cll->d->ordered_add(&cll, &x);
    x = 3;
    cll->d->ordered_add(&cll, &x);
    x = 2;
    if(cll->d->type_descriptor->cmp(&x, cll->data) != 0)
        MLCL_ERR(1, MLCL_ERR_TRUE)
    x = 3;
    if(cll->d->type_descriptor->cmp(&x, cll->next->data) != 0)
        MLCL_ERR(2, MLCL_ERR_TRUE)
    x = 5;
    if(cll->d->type_descriptor->cmp(&x, cll->next->next->data) != 0)
        MLCL_ERR(3, MLCL_ERR_TRUE)
    x = 6;
    if(cll->d->type_descriptor->cmp(&x, cll->next->next->next->data) != 0)
        MLCL_ERR(4, MLCL_ERR_TRUE)
    cll->d->free(&cll);
    return 1;
}

int test_circular_linked_list_append(){
    CircularLinkedList ll;
    float x;
    printf("├ test_cll_append:");
    x = 5.4f;
    ll = new_circular_linked_list(&x, float_m);
    if(!ll)
        MLCL_ERR(1, MLCL_ERR_ALLOC);
    x = 5.3f;
    ll->d->append(&ll, &x);
    ll->d->append(&ll, &x);
    x = 5.96f;
    ll->d->append(&ll, &x);
    if(ll->next->next->next->next != ll)
        MLCL_ERR(2, MLCL_ERR_TRUE);
    ll->d->free(&ll);
    return 1;
}

int test_circular_linked_list_search(){
    CircularLinkedList ll;
    int x;
    printf("├ test_search:");
    x = 5;
    ll = new_circular_linked_list(&x, int_m);
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

int test_circular_linked_list_prepend(){
    CircularLinkedList ll;
    float x;
    printf("├ test_cell_prepend:");
    x = 5.4f;
    ll = new_circular_linked_list(&x, float_m);
    if(!ll)
        MLCL_ERR(1, MLCL_ERR_ALLOC)
    x = 5.3f;
    ll->d->prepend(&ll, &x);
    if(ll != ll->next->next)
        MLCL_ERR(2, MLCL_ERR_TRUE)
    ll->d->free(&ll);
    return 1;
}

int test_circular_linked_list_pop(){
    CircularLinkedList ll;
    int x;
    void * data;
    printf("├ test_ll_pop:");
    x = 5;
    ll = new_circular_linked_list(&x, int_m);
    if(!ll)
        MLCL_ERR(1, MLCL_ERR_ALLOC)
    x = 6;
    ll->d->prepend(&ll, &x);
    data = ll->d->pop(&ll);
    if((* (int *) data) != 5)
        MLCL_ERR(2, MLCL_ERR_TRUE)
    ll->d->free(&ll);
    free(data);
    return 1;
}

int test_circular_linked_list_shift(){
    CircularLinkedList cll;
    float x;
    printf("├ test_cll_shift:");
    x = 5.4f;
    cll = new_circular_linked_list(&x, float_m);
    x = 5.5f;
    cll->d->append(&cll, &x);
    if(!cll)
        MLCL_ERR(1, MLCL_ERR_ALLOC)
    free((float *) cll->d->shift(&cll));
    if(cll->next->next != cll)
        MLCL_ERR(2, MLCL_ERR_TRUE)
    cll->d->free(&cll);
    return 1;
}
