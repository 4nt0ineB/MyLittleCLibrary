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

#include "../../../include/_Tests/Trees/MLCL_BKTree_test.h"
#include "../../../include/Trees/MLCL_BKTree.h"
#include "../../../include/_Tests/MLCL_exceptions.h"
#include "../../../include/MLCL_TypeDescriptor.h"
#include "../../../include/MLCL_basic_types.h"

int run_all_bk_tree_tests(){
    printf("▒▒▒ Running all BKTree tests ▒▒▒\n");
    MLCL_TEST(test_bk_tree_add, "test_avl_tree_add")
    return 1;
}

int test_bk_tree_add(){
    BKTree t;

    t = new_bk_tree("dog");
    if(!t)
        MLCL_ERR(1, MLCL_ERR_ALLOC)

    t->d->add(&t, "Dogma");
    t->d->add(&t, "god");
    t->d->add(&t, "house");
    t->d->add(&t, "mouse");

    printf("\n");
    bk_tree_print(t);
    printf("\n");
    /*printf("MOT: %s\n", (char *) t->child->data);*/

    return 1;
}