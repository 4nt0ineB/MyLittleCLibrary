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

#include "../../../../include/_tests/data-structures/Trees/MLCL_BKTree_test.h"
#include "../../../../include/data-structures/Trees/MLCL_BKTree.h"
#include "../../../../include/_tests/MLCL_exceptions.h"
#include "../../../../include/core/MLCL_basic_types.h"

int run_all_bk_tree_tests(){
    printf("▒▒▒ Running all BKTree tests ▒▒▒\n");
    MLCL_TEST(test_bk_tree_add, "test_avl_tree_add")
    MLCL_TEST(test_bk_tree_fuzzy_search, "test_avl_tree_fuzzy_search")
    return 1;
}

int test_bk_tree_add(){
    BKTree t;

    t = new_bk_tree("dog");
    if(!t)
        MLCL_ERR(1, MLCL_ERR_ALLOC)

    t->d->add(&t, "god");
    t->d->add(&t, "house");
    t->d->add(&t, "mouse");
    t->d->add(&t, "Dogma");

    t->d->free(&t);
    return 1;
}

int test_bk_tree_fuzzy_search(){
    BKTree t;
    List *l;

    t = new_bk_tree("dog");
    if(!t)
        MLCL_ERR(1, MLCL_ERR_ALLOC)

    t->d->add(&t, "god");
    t->d->add(&t, "house");
    t->d->add(&t, "mouse");
    t->d->add(&t, "Dogma");
    t->d->add(&t, "Dogma 95");
    t->d->add(&t, "Doctrine");
    t->d->add(&t, "Django");
    t->d->add(&t, "Dodecahedron");

    /*printf("\n");
    t->d->print(t);
    printf("\n");*/

    /*t->d->to_dot(t, "test.dot");*/

    l = new_list(LINKED_LIST, str_m);
    t->d->fuzzy_search(&t, "jan", l);
    /*l->print(l);*/

    if(str_cmp(l->s.linked_list->data, "Django") != 0)
        MLCL_ERR(2, MLCL_ERR_TRUE)


    t->d->free(&t);
    l->free(&l);
    return 1;
}