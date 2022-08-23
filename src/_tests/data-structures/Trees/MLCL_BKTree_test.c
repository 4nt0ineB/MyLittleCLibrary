/*
 *   This file is part of the MLCL Library
 *   Copyright 2022 Antoine Bastos
 *   SPDX-License-Identifier: Apache-2.0
 */

#include "../../../../include/_tests/data-structures/Trees/MLCL_BKTree_test.h"
#include "../../../../include/data-structures/Trees/MLCL_BKTree.h"
#include "../../../../include/_tests/MLCL_exceptions.h"
#include "../../../../include/core/MLCL_basic_types.h"
/*

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

    */
/*printf("\n");
    t->d->print(t);
    printf("\n");*//*


    */
/*t->d->to_dot(t, "test.dot");*//*


    l = new_list(LINKED_LIST, str_m);
    t->d->fuzzy_search(&t, "jan", l);
    */
/*l->print(l);*//*


    if(str_cmp(l->s.linked_list->data, "Django") != 0)
        MLCL_ERR(2, MLCL_ERR_TRUE)


    t->d->free(&t);
    l->free(&l);
    return 1;
}*/
