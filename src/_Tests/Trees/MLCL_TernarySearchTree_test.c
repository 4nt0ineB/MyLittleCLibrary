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

#include "../../../include/_Tests/Trees/MLCL_TernarySearchTree_test.h"
#include "../../../include/Trees/MLCL_TernarySearchTree.h"
#include "../../../include/_Tests/MLCL_exceptions.h"

int run_all_ternary_search_tree_tests(){
    printf("▒▒▒ Running all TernarySearchTree tests ▒▒▒\n");
    MLCL_TEST(test_ternary_search_tree_add, "test_ternary_search_tree_add")
    return 1;
}


int test_ternary_search_tree_add(){
    TernarySearchTree t;

    t = new_ternary_search_tree("Beetlejuice");
    t->d->add(&t, "Foo");
    t->d->add(&t, "Bar");

    /*t->d->to_dot(t, "test.dot");*/
    /*t->d->print(t);*/

    t->d->free(&t);
    return 1;
}