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

#include "../../../include/_Tests/List/MLCL_CircularDoubleLinkedList_test.h"
#include "../../../include/_Tests/MLCL_exceptions.h"
#include "../../../include/List/MLCL_CircularDoubleLinkedList.h"
#include "../../../include/MLCL_basic_types.h"


int run_all_circular_double_linked_list_tests(){
    printf("▒▓ Running all CircularDoubleLinkedList tests\n");
    MLCL_TEST(test_circular_double_linked_list_ordered_add)
    MLCL_TEST(test_circular_double_linked_list_prepend)
    MLCL_TEST(test_circular_double_linked_list_append)
    MLCL_TEST(test_circular_double_linked_list_search)
    MLCL_TEST(test_circular_double_linked_list_pop)
    MLCL_TEST(test_circular_double_linked_list_shift)
    return 1;
}

int test_circular_double_linked_list_ordered_add(){
    CircularDoubleLinkedList cdll;
    int x;
    printf("├ test_circular_linked_list_ordered_add:");
    x = 5;
    cdll = new_circular_double_linked_list(&x, int_m);
    x = 6;
    cdll->d->ordered_add(&cdll, &x);
    x = 2;
    cdll->d->ordered_add(&cdll, &x);
    x = 3;
    cdll->d->ordered_add(&cdll, &x);
    x = 2;
    if(cdll->d->type_descriptor->cmp(&x, cdll->data) != 0)
        MLCL_ERR(1, MLCL_ERR_TRUE)
    x = 3;
    if(cdll->d->type_descriptor->cmp(&x, cdll->next->data) != 0)
        MLCL_ERR(2, MLCL_ERR_TRUE)
    x = 5;
    if(cdll->d->type_descriptor->cmp(&x, cdll->next->next->data) != 0)
        MLCL_ERR(3, MLCL_ERR_TRUE)
    x = 6;
    if(cdll->d->type_descriptor->cmp(&x, cdll->next->next->next->data) != 0)
        MLCL_ERR(4, MLCL_ERR_TRUE)
    cdll->d->free(&cdll);
    return 1;
}

int test_circular_double_linked_list_prepend(){
    CircularDoubleLinkedList ll;
    float x;
    printf("├ test_circular_double_linked_list_prepend:");
    x = 5.4f;
    ll = new_circular_double_linked_list(&x, float_m);
    if(!ll)
        MLCL_ERR(1, MLCL_ERR_ALLOC)
    x = 5.3f;
    ll->d->prepend(&ll, &x);
    if(ll != ll->next->next)
        MLCL_ERR(2, MLCL_ERR_TRUE)
    ll->d->free(&ll);
    return 1;
}

int test_circular_double_linked_list_append(){
    CircularDoubleLinkedList ll;
    float x;
    printf("├ test_circular_double_linked_list_append:");
    x = 5.4f;
    ll = new_circular_double_linked_list(&x, float_m);
    if(!ll)
        MLCL_ERR(1, MLCL_ERR_ALLOC)
    x = 5.3f;
    ll->d->append(&ll, &x);
    ll->d->append(&ll, &x);
    x = 5.96f;
    ll->d->append(&ll, &x);
    if(ll->next->next->next->next != ll)
        MLCL_ERR(2, MLCL_ERR_TRUE)
    ll->d->free(&ll);
    return 1;
}

int test_circular_double_linked_list_search(){
    CircularDoubleLinkedList ll;
    int x;
    printf("├ test_circular_double_linked_list_search:");
    x = 5;
    ll = new_circular_double_linked_list(&x, int_m);
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

int test_circular_double_linked_list_pop(){
    CircularDoubleLinkedList cdll;
    int x;
    void * data;
    printf("├ test_circular_double_linked_list_pop:");
    x = 5;
    cdll = new_circular_double_linked_list(&x, int_m);
    if(!cdll)
        MLCL_ERR(1, MLCL_ERR_ALLOC)
    x = 6;
    cdll->d->prepend(&cdll, &x);
    data = cdll->d->pop(&cdll);
    if((* (int *) data) != 5)
        MLCL_ERR(2, MLCL_ERR_TRUE)
    cdll->d->free(&cdll);
    free(data);
    return 1;
}

int test_circular_double_linked_list_shift(){
    CircularDoubleLinkedList cdll;
    float x;
    printf("├ test_circular_double_linked_list_shift:");
    x = 5.4f;
    cdll = new_circular_double_linked_list(&x, float_m);
    x = 5.5f;
    cdll->d->append(&cdll, &x);
    if(!cdll)
        MLCL_ERR(1, MLCL_ERR_ALLOC)
    free(cdll->d->shift(&cdll));
    if(cdll->next->next != cdll)
        MLCL_ERR(2, MLCL_ERR_TRUE)
    cdll->d->free(&cdll);
    return 1;
}
