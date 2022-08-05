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
    MLCL_TEST(test_new_list)
    MLCL_TEST(test_list_append)

    return 1;
}
int test_new_list(){
    List *l;
    int x;
    printf("├ test_new_list:");
    l = new_list(ARRAY_LIST, int_m);
    x = 1;
    l->append(l, &x);
    l->print(l);
    l->free(&l);
    return 1;
}
int test_list_append(){
    printf("├ test_list_append:");

    return 1;
}