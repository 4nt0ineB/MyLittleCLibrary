/*
 *   This file is part of the MLCL Library.
 *   Antoine Bastos 2022
 *
 *   This Library is free software under the terms of
 *   the MIT license.
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

    t = new_ternary_search_tree("bop");
    t->d->add(&t, "yulo");
    t->d->add(&t, "gu");

    /*printf("\n");
    t->d->print(t);*/

    t->d->free(&t);
    return 1;
}