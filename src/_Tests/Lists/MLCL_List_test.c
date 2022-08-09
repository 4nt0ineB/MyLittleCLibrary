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

#include "../../../include/_Tests/Lists/MLCL_List_test.h"

#include "../../../include/Lists/MLCL_List.h"
#include "../../../include/_Tests/MLCL_exceptions.h"
#include "../../../include/MLCL_basic_types.h"

int run_all_list_tests(){
    printf("▒▒▒ Running all List tests ▒▒▒\n");
    MLCL_TEST(test_list_append, "test_list_append")

    return 1;
}

int test_list_append(){
    List *l;
    int x;
    l = new_list(ARRAY_LIST, int_m);
    if(!l)
        MLCL_ERR(1, MLCL_ERR_ALLOC)
    x = 1;
    l->append(l, &x);
    if(l->s.array_list->d->type_descriptor->eq(l->s.array_list->array[0], &x) != 1)
        MLCL_ERR(2, MLCL_ERR_TRUE)

    l->free(&l);
    return 1;
}
