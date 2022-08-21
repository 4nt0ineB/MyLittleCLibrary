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

#ifndef MYLITTLECLIBRARY_MLCL_BinarySearchTree_H
#define MYLITTLECLIBRARY_MLCL_BinarySearchTree_H

#include "../../core/MLCL_TypeDescriptor.h"
#include <stdlib.h>
#include <stdio.h>

/**
 * @brief A generic binary search tree
 */
typedef struct s_binary_search_tree_node {
    void * data;
    struct s_binary_search_tree_node * left; /* left child */
    struct s_binary_search_tree_node * right; /* right child */
    struct s_binary_search_tree_descriptor * d; /*!< Descriptor of the binary search tree */
} BinarySearchTreeNode,  * BinarySearchTree;

/**
 * @brief Descriptor of the binary tree
 * The tree - the nodes - refers to a binary tree descriptor,
 * gathering implemented functions of the BinarySearchTree type, including
 * a TypeDescriptor allowing manipulation of the data, and the the number of nodes.
 */
typedef struct s_binary_search_tree_descriptor {
    int n; /**< Number of nodes in the tree */
    TypeDescriptor * type_descriptor;
    int (*height) (BinarySearchTree); /**< Return the height of the tree */
    int (*nb_nodes) (BinarySearchTree); /**< Return the number of nodes. O(1) by the struct */
    int (*nb_leaves) (BinarySearchTree); /**< Return the number of leaves */
    int (*nb_internal_nodes) (BinarySearchTree); /**< Return the number of internal nodes */
    int (*nb_two_children) (BinarySearchTree); /**< Number of nodes having two children */
    int  (*add) (BinarySearchTree *, const void *); /**< add data to the tree */
    BinarySearchTree (*min) (BinarySearchTree); /**< Return a pointer to the min node */
    BinarySearchTree (*max) (BinarySearchTree); /**< Return a pointer to the the max node */
    void * (*extract_min) (BinarySearchTree *); /**< Remove the min node in the tree and return the pointer of its data */
    void * (*extract_max) (BinarySearchTree *); /**< Remove the max node in the tree and return the pointer of its data */
    int  (*remove) (BinarySearchTree *, const void *); /**< Remove the first occurrence of the given data trough preorder traversal  */
    BinarySearchTree  (*search) (BinarySearchTree *, const void *); /**< Return a pointer to the first occurrence of the node having data equal to the given one, trough preorder traversal */
    int (*is_perfect_bt) (BinarySearchTree); /**< Return 1 if the tree is a perfect binary tree, else 0 */
    int (*is_bst) (BinarySearchTree); /**< Return 1 if the tree is a binary search tree, else 0 */
    void (*node_print) (BinarySearchTreeNode *); /**< Print the given node on stdout */
    void (*node_fprint) (FILE *, BinarySearchTreeNode *); /**< Print the given node on the given stream */
    void (*fprint_preorder) (FILE *, BinarySearchTree);
    void (*fprint_inorder) (FILE *, BinarySearchTree);
    void (*fprint_postorder) (FILE *, BinarySearchTree);
    /* breadth-first traversal */
    void (*to_dot) (BinarySearchTree, const char *); /**< Make a formatted dot file of the struct */
    void (*free) (BinarySearchTree *); /**< Free to tree */
} BinarySearchTreeDescriptor;

/**
 * @brief Allocate and return a default
 * binary tree descriptor. Type descriptor set to null.
 * @return
 */
BinarySearchTreeDescriptor * binary_search_tree_descriptor();

/**
 * @brief A detailed constructor for the nodes of a binary tree.
 * @param data First cell's data.
 * @param descriptor The binary tree descriptor.
 * @return
 */
BinarySearchTreeNode * binary_search_tree_builder(const void * data, BinarySearchTreeDescriptor * descriptor);

/**
 * @brief Allocate a new binary search tree
 * @param val
 * @return
 */
BinarySearchTree new_binary_search_tree(const void * data, void (*type_manifest) (TypeDescriptor *));

/**
 * @brief Return the height of the tree
 * @param a tree
 * @return Binary tree height
 */
int binary_search_tree_height(BinarySearchTree t);

/**
 * @brief Return the number of nodes
 * @param a tree
 * @return
 */
int binary_search_tree_nb_nodes(BinarySearchTree t);

/**
 * @brief Return the number of leaves
 * @param a tree
 * @return
 */
int binary_search_tree_nb_leaves(BinarySearchTree t);

/**
 * @brief Return the number of internal nodes
 * @param a tree
 * @return
 */
int binary_search_tree_nb_internal_nodes(BinarySearchTree t);

/**
 * @brief Return the number nodes having two children
 * @param t
 * @return
 */
int binary_search_tree_nb_two_children(BinarySearchTree t);

/**
 * @brief Return true if a given tree is a perfect
 * binary tree
 * @param t
 * @return
 */
int binary_search_tree_is_perfect_bt(BinarySearchTree t);

/**
 * @brief Return a pointer to the min node
 * @param t
 * @return
 */
BinarySearchTree binary_search_tree_min(BinarySearchTree t);

/**
 * @brief Return a pointer to the the max node
 * @param t
 * @return
 */
BinarySearchTree binary_search_tree_max(BinarySearchTree t);

/**
 * @brief Return 1 if the binary tree is BST
 * and without duplicate
 *
 * @param a
 * @return int
 */
int binary_search_tree_is_bst(BinarySearchTree t);

/**
 * @brief add data to the tree
 * @param t
 * @param data
 * @return
 */
int binary_search_tree_add(BinarySearchTree * t, const void * data);

/**
 * @brief Remove the minx node in the tree and return the pointer of its data
 * @param t
 * @return
 */
void * binary_search_tree_extract_min(BinarySearchTree * t);

/**
 * @brief Remove the max node in the tree and return the pointer of its data
 * @param t
 * @return
 */
void * binary_search_tree_extract_max(BinarySearchTree * t);

/**
 * @brief Remove the first occurrence of the given data trough preorder traversal
 * @param t
 * @param data
 * @return
 */
int binary_search_tree_remove(BinarySearchTree * t, const void * data);

/**
 * @brief Return a pointer to the first occurrence of the node having data equal to the given one, trough preorder traversal
 * @param t
 * @param data
 * @return
 */
BinarySearchTree binary_search_tree_search(BinarySearchTree * t, const void * data);

/**
 * @brief Print the given node on stdout
 * @param n
 */
void binary_search_tree_node_print(BinarySearchTreeNode * n);

/**
 * @brief Print the given node on the given stream
 * @param n
 */
void binary_search_tree_node_fprint (FILE * stream, BinarySearchTreeNode * n);

/* Depth First Traversals */
void binary_search_tree_fprint_preorder(FILE * stream, BinarySearchTree t);
void binary_search_tree_fprint_inorder(FILE * stream, BinarySearchTree t);
void binary_search_tree_fprint_postorder(FILE * stream, BinarySearchTree t);

/**
 * @brief Make a formatted dot file of the struct
 * @param ll
 * @param dest_path
 */
void binary_search_tree_to_dot(BinarySearchTree t, const char * dest_path);

/**
 * @brief Free the descriptor of the Binary search tree
 * @param bstd
 */
void binary_search_tree_descriptor_free(BinarySearchTreeDescriptor ** bstd);

/**
 * @brief Free the binary search tree
 * @param t
 */
void binary_search_tree_free(BinarySearchTree * t);

#endif /* MYLITTLECLIBRARY_MLCL_BinarySearchTree_H */
