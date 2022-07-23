/*
 *   This file is part of the MLCL Library.
 *   Antoine Bastos 2022
 *
 *   This Library is free software under the terms of
 *   the MIT license.
 */

#ifndef MYLITTLECLIBRARY_MLCL_TREE_H
#define MYLITTLECLIBRARY_MLCL_TREE_H

#include "MLCL_BinarySearchTree.h"
#include "MLCL_AVLTree.h"

typedef struct s_tree_node{
    union {
        BinarySearchTree binary_search_tree;
        AVLTree avl_tree;
    } s ;
    struct s_tree_descriptor * d;
}TreeNode, *Tree;

typedef struct s_tree_descriptor {
    int (*height) (Tree);
    int (*nb_nodes) (Tree);
    int (*nb_leaves) (Tree);
    int (*nb_internal_nodes) (Tree);
    int  (*add) (Tree, const void *);
    void * (*min) (Tree);
    void * (*max) (Tree);
    void (*node_print) (Tree *);
    void (*node_fprint) (FILE *, Tree *);
    void (*fprint_preorder) (FILE *, Tree);
    void (*fprint_inorder) (FILE *, Tree);
    void (*fprint_postorder) (FILE *, Tree);
    void (*to_dot) (BinarySearchTree, const char *);
    void (*free) (BinarySearchTree *);
} TreeDescriptor;

#endif /* MYLITTLECLIBRARY_MLCL_TREE_H */
