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

#include "../../../include/_Tests/List/MLCL_ArrayList_test.h"
#include "../../../include/List/MLCL_ArrayList.h"
#include "../../../include/_Tests/MLCL_exceptions.h"
#include "../../../include/MLCL_basic_types.h"


int run_all_array_list_tests(){
    printf("▒▒▒ Running all ArrayList tests ▒▒▒\n");
    MLCL_TEST(test_new_array_list)
    MLCL_TEST(test_array_list_append)
    return 1;
}

int test_new_array_list(){
    ArrayList * l;
    int i;
    printf("├ test_new_array_list:");

    l = new_array_list(int_m);

    for(i = 0; i < 10; i++)
        l->d->append(l, &i);
/*
    printf("Count: %d\n", l->count);
*/

    l->d->print(l);
    l->d->free(&l);
    return 1;
}

int test_array_list_append(){
    printf("├ test_array_list_append:");

    return 1;
}