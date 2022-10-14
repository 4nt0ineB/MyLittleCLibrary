/*
 *   This file is part of the MLCL Library
 *   Antoine Bastos 2022
 *   SPDX-License-Identifier: Apache-2.0
 */

#include "../../../../include/_tests/data-structures/Trees/MLCL_BKTree_test.h"
#include "../../../../include/data-structures/Trees/MLCL_BKTree.h"
#include "../../../../include/_tests/MLCL_exceptions.h"
#include "../../../../include/core/MLCL_primitive_types.h"


int run_all_bk_tree_tests(){
    printf("▒▒▒ Running all BKTree tests \n");
    MLCL_TEST(test_bk_tree_add)
    MLCL_TEST(test_bk_tree_fuzzy_search)
    return 1;
}

int test_bk_tree_add(){
    BKTree *tree;

    tree = new_bk_tree();
    
    if(!tree)
        MLCL_ERR(1, MLCL_ERR_ALLOC)

    bk_tree_add(tree, "dog");
    bk_tree_add(tree, "god");
    bk_tree_add(tree, "house");
    bk_tree_add(tree, "mouse");
    bk_tree_add(tree, "Dogma");

    /*printf("\n");
    bk_tree_print(tree);
    printf("\n");*/

    bk_tree_free(&tree);
    return 1;
}

int test_bk_tree_fuzzy_search(){
    BKTree *tree;
    List *list;

    tree = new_bk_tree();

    if(!tree)
        MLCL_ERR(1, MLCL_ERR_ALLOC)

    bk_tree_add(tree, "dog");
    bk_tree_add(tree, "god");
    bk_tree_add(tree, "house");
    bk_tree_add(tree, "mouse");
    bk_tree_add(tree, "Dogma");
    bk_tree_add(tree, "Dogma 95");
    bk_tree_add(tree, "Doctrine");
    bk_tree_add(tree, "Django");
    bk_tree_add(tree, "Dodecahedron");

    /*printf("\n");
    bk_tree_print(tree);
    printf("\n");*/

    /*bk_tree_to_dot(tree, "test.dot");*/

    list = new_list(LINKED_LIST, str_m);
    bk_tree_fuzzy_search(tree, "jan", list);

    /*list_print(list);*/

    if(str_cmp(list->s.linked_list->head->data, "Django") != 0)
        MLCL_ERR(2, MLCL_ERR_TRUE)

    bk_tree_free(&tree);
    list_free(&list);
    return 1;
}
