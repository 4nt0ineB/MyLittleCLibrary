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

#include "../../../../include/_tests/data-structures/Lists/MLCL_List_test.h"

#include "../../../../include/data-structures/Lists/MLCL_List.h"
#include "../../../../include/_tests/MLCL_exceptions.h"
#include "../../../../include/core/MLCL_basic_types.h"

int run_all_list_tests(){
    printf("▒▒▒ Running all List tests ▒▒▒\n");
    MLCL_TEST(test_list_append, "test_list_append")
    return 1;
}

int test_list_append(){

    List * l;

    l = new_list(LINKED_LIST, str_m);

    if(!l)
        MLCL_ERR(1, MLCL_ERR_ALLOC)

    l->append(l, "hell");
    l->append(l, "shell");
    l->append(l, "Foo");
    l->append(l, "bar");
    l->append(l, "Bubble");
    l->s.linked_list->d->merge_sort(&l->s.linked_list, l->s.linked_list->d->type_descriptor->lt);

    if(l->s.linked_list->d->type_descriptor->eq(l->s.linked_list->data, "Bubble") != 1)
        MLCL_ERR(2, MLCL_ERR_TRUE)

    l->free(&l);
    return 1;
}
