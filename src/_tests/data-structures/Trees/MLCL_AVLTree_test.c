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

#include "../../../../include/_tests/data-structures/Trees/MLCL_AVLTree_test.h"
#include "../../../../include/data-structures/Trees/MLCL_AVLTree.h"
#include "../../../../include/_tests/MLCL_exceptions.h"
#include "../../../../include/core/MLCL_TypeDescriptor.h"
#include "../../../../include/core/MLCL_basic_types.h"

#include <stdio.h>
/*

int run_all_avl_tree_tests(){
    printf("▒▒▒ Running all AVLTree tests ▒▒▒\n");
    MLCL_TEST(test_new_avl_tree, "test_new_avl_tree")
    MLCL_TEST(test_avl_tree_add, "test_avl_tree_add")
    MLCL_TEST(test_avl_remove, "test_avl_remove")
    return 1;
}

int test_new_avl_tree(){
    AVLTree avl;
    int x;
    x = 8;
    avl = new_avl_tree(&x,  int_m);
    if(!avl)
        MLCL_ERR(1, MLCL_ERR_ALLOC)
    avl->d->free(&avl);
    return 1;
}

int test_avl_tree_add(){
    AVLTree avl;
    int x;
    x = 8;
    avl = new_avl_tree(&x,  int_m);
    x = 7;
    avl->d->add(&avl, &x);
    x = 6;
    avl->d->add(&avl, &x);
    x = 4;
    avl->d->add(&avl, &x);
    x = 5;
    avl->d->add(&avl, &x);
    x = 6;
    if(!avl->d->type_descriptor->eq(avl->left->right->data, &x))
        MLCL_ERR(1, MLCL_ERR_TRUE)
    avl->d->free(&avl);
    return 1;
}

int test_avl_remove(){
    AVLTree avl;
    int x;
    x = 8;
    avl = new_avl_tree(&x,  int_m);
    x = 7;
    avl->d->add(&avl, &x);
    x = 6;
    avl->d->add(&avl, &x);
    x = 4;
    avl->d->add(&avl, &x);
    x = 5;
    avl->d->add(&avl, &x);
    x = 8;
    avl->d->remove(&avl, &x);
    x = 6;
    if(!avl->d->type_descriptor->eq(avl->right->left->data, &x))
        MLCL_ERR(1, MLCL_ERR_TRUE)
    avl->d->free(&avl);
    return 1;
}*/
