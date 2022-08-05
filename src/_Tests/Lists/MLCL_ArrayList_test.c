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

#include "../../../include/_Tests/Lists/MLCL_ArrayList_test.h"
#include "../../../include/Lists/MLCL_ArrayList.h"
#include "../../../include/_Tests/MLCL_exceptions.h"
#include "../../../include/MLCL_basic_types.h"


int run_all_array_list_tests(){
    printf("▒▒▒ Running all ArrayList tests ▒▒▒\n");
    MLCL_TEST(test_array_list_append, "test_array_list_append")
    MLCL_TEST(test_array_list_pop, "test_array_list_pop")
    MLCL_TEST(test_array_list_pop_i, "test_array_list_pop_i")
    MLCL_TEST(test_array_list_is_sorted, "test_array_list_is_sorted")
    MLCL_TEST(test_array_list_bubble_sort, "test_array_list_bubble_sort")
    MLCL_TEST(test_array_list_selection_sort, "test_array_list_selection_sort")
    MLCL_TEST(test_array_list_insertion_sort, "test_array_list_insertion_sort")
    MLCL_TEST(test_array_list_quick_sort, "test_array_list_quick_sort")
    MLCL_TEST(test_array_list_merge_sort, "test_array_list_merge_sort")
    MLCL_TEST(test_array_list_search, "test_array_list_search")
    MLCL_TEST(test_array_list_binary_search, "test_array_list_binary_search")
    return 1;
}

int test_array_list_append(){
    ArrayList * l;
    int i;

    l = new_array_list(int_m);
    if(!l)
        MLCL_ERR(1, MLCL_ERR_ALLOC)

    for(i = 0; i < 10; i++)
        l->d->append(l, &i);

    if(*(int *) l->array[5] != 5)
        MLCL_ERR(2, MLCL_ERR_TRUE)

    if(l->count != 10)
        MLCL_ERR(3, MLCL_ERR_TRUE)

    if(l->size != 10)
        MLCL_ERR(4, MLCL_ERR_TRUE)

    l->d->free(&l);
    return 1;
}

int test_array_list_pop(){
    ArrayList * l;
    int i;
    void * x;

    l = new_array_list(int_m);
    if(!l)
        MLCL_ERR(1, MLCL_ERR_ALLOC)

    for(i = 0; i < 5; i++)
        l->d->append(l, &i);

    x = l->d->pop(l);

    if(*(int *) x != 4)
        MLCL_ERR(2, MLCL_ERR_TRUE)
    free(x);
    free(l->d->pop(l));
    free(l->d->pop(l));
    free(l->d->pop(l));
    free(l->d->pop(l));

    if(l->count != 0)
        MLCL_ERR(3, MLCL_ERR_TRUE)
    if(l->size != 10)
        MLCL_ERR(4, MLCL_ERR_TRUE)

    l->d->free(&l);
    return 1;
}

int test_array_list_pop_i(){
    ArrayList * l;
    int i;
    void * x;

    l = new_array_list(int_m);
    if(!l)
        MLCL_ERR(1, MLCL_ERR_ALLOC)

    for(i = 0; i < 5; i++)
        l->d->append(l, &i);

    x = l->d->pop_i(l, 0);
    if(*(int *) x != 0)
        MLCL_ERR(2, MLCL_ERR_TRUE)
    free(x);

    x = l->d->pop_i(l, 1);
    if(*(int *) x != 2)
        MLCL_ERR(2, MLCL_ERR_TRUE)
    free(x);

    if(l->count != 3)
        MLCL_ERR(3, MLCL_ERR_TRUE)
    if(l->size != 10)
        MLCL_ERR(4, MLCL_ERR_TRUE)

    l->d->free(&l);
    return 1;
}

int test_array_list_is_sorted(){
    ArrayList * l;
    int i;

    l = new_array_list(int_m);
    if(!l)
        MLCL_ERR(1, MLCL_ERR_ALLOC)

    for(i = 0; i < 5; i++)
        l->d->append(l, &i);

    if(!l->d->is_sorted(l, l->d->type_descriptor->le))
        MLCL_ERR(2, MLCL_ERR_TRUE)

    l->d->free(&l);
    return 1;
}

int test_array_list_bubble_sort(){
    ArrayList * l;
    int x;

    l = new_array_list(int_m);
    if(!l)
        MLCL_ERR(1, MLCL_ERR_ALLOC)

    x = 6;
    l->d->append(l, &x);
    x = 3;
    l->d->append(l, &x);
    x = 2;
    l->d->append(l, &x);
    x = 1;
    l->d->append(l, &x);

    l->d->bublle_sort(l, l->d->type_descriptor->le);

    if(!l->d->is_sorted(l, l->d->type_descriptor->le))
        MLCL_ERR(2, MLCL_ERR_TRUE)

    l->d->free(&l);
    return 1;
}

int test_array_list_selection_sort(){
    ArrayList * l;
    int x;

    l = new_array_list(int_m);
    if(!l)
    MLCL_ERR(1, MLCL_ERR_ALLOC)

    x = 6;
    l->d->append(l, &x);
    x = 3;
    l->d->append(l, &x);
    x = 28;
    l->d->append(l, &x);
    x = 2;
    l->d->append(l, &x);
    x = 1;
    l->d->append(l, &x);

    l->d->selection_sort(l, l->d->type_descriptor->le);

    if(!l->d->is_sorted(l, l->d->type_descriptor->le))
        MLCL_ERR(2, MLCL_ERR_TRUE)

    l->d->free(&l);
    return 1;
}

int test_array_list_insertion_sort(){
    ArrayList * l;
    int x;

    l = new_array_list(int_m);
    if(!l)
    MLCL_ERR(1, MLCL_ERR_ALLOC)

    x = 6;
    l->d->append(l, &x);
    x = 3;
    l->d->append(l, &x);
    x = 28;
    l->d->append(l, &x);
    x = 2;
    l->d->append(l, &x);
    x = 1;
    l->d->append(l, &x);

    l->d->insertion_sort(l, l->d->type_descriptor->ge);

    if(!l->d->is_sorted(l, l->d->type_descriptor->ge))
        MLCL_ERR(2, MLCL_ERR_TRUE)

    l->d->free(&l);
    return 1;
}

int test_array_list_quick_sort(){
    ArrayList * l;
    int x;

    l = new_array_list(int_m);
    if(!l)
    MLCL_ERR(1, MLCL_ERR_ALLOC)

    x = 6;
    l->d->append(l, &x);
    x = 3;
    l->d->append(l, &x);
    x = 28;
    l->d->append(l, &x);
    x = 2;
    l->d->append(l, &x);
    x = 1;
    l->d->append(l, &x);

    l->d->quick_sort(l, l->d->type_descriptor->le);

    if(!l->d->is_sorted(l, l->d->type_descriptor->le))
    MLCL_ERR(2, MLCL_ERR_TRUE)

    l->d->free(&l);
    return 1;
}

int test_array_list_merge_sort(){
    ArrayList * l;
    int x;

    l = new_array_list(int_m);
    if(!l)
        MLCL_ERR(1, MLCL_ERR_ALLOC)

    x = 6;
    l->d->append(l, &x);
    x = 3;
    l->d->append(l, &x);
    x = 28;
    l->d->append(l, &x);
    x = 2;
    l->d->append(l, &x);
    x = 1;
    l->d->append(l, &x);

    l->d->merge_sort(l, l->d->type_descriptor->le);

    if(!l->d->is_sorted(l, l->d->type_descriptor->le))
        MLCL_ERR(2, MLCL_ERR_TRUE)

    l->d->free(&l);
    return 1;
}

int test_array_list_search(){
    ArrayList * l;
    int x, index;

    l = new_array_list(int_m);
    if(!l)
        MLCL_ERR(1, MLCL_ERR_ALLOC)

    x = 6;
    l->d->append(l, &x);
    x = 3;
    l->d->append(l, &x);
    x = 28;
    l->d->append(l, &x);
    x = 2;
    l->d->append(l, &x);
    x = 1;
    l->d->append(l, &x);

    l->d->quick_sort(l, l->d->type_descriptor->le);

    x = 28;
    if(!l->d->search(l, &x, &index))
        MLCL_ERR(2, MLCL_ERR_TRUE)

    if(index != 4)
        MLCL_ERR(3, MLCL_ERR_TRUE)

    l->d->free(&l);
    return 1;
}

int test_array_list_binary_search(){
    ArrayList * l;
    int x, index;

    l = new_array_list(int_m);
    if(!l)
        MLCL_ERR(1, MLCL_ERR_ALLOC)

    x = 6;
    l->d->append(l, &x);
    x = 3;
    l->d->append(l, &x);
    x = 28;
    l->d->append(l, &x);
    x = 2;
    l->d->append(l, &x);
    x = 1;
    l->d->append(l, &x);

    l->d->quick_sort(l, l->d->type_descriptor->le);

    x = 28;
    if(!l->d->binary_search(l, &x, &index))
        MLCL_ERR(2, MLCL_ERR_TRUE)

    if(index != 4)
        MLCL_ERR(3, MLCL_ERR_TRUE)

    l->d->free(&l);
    return 1;
}