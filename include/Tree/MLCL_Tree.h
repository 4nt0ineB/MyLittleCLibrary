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
