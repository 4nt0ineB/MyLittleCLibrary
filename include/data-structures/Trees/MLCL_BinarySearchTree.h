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
typedef struct BinarySearchTreeNode {
    void * data;
    struct BinarySearchTreeNode *left, *right;
} BinarySearchTreeNode;

typedef struct {
    BinarySearchTreeNode *root;
    int n; /**< Number of nodes */
    TypeDescriptor *td;
} BinarySearchTree;

/***************************************************
 * BinarySearchTreeNode
 ***************************************************/

BinarySearchTreeNode * new_binary_search_tree_node(void *data);
void binary_search_tree_node_free(BinarySearchTreeNode **self, void (*data_free) (void *));

/**
 * @brief Print the given node on stdout
 * @param n
 */
void binary_search_tree_node_print(const BinarySearchTreeNode *self,  void (data_fprint) (const void *, FILE *));

/**
 * @brief Print the given node on the given stream
 * @param n
 */
void binary_search_tree_node_fprint (const BinarySearchTreeNode *self, FILE * stream,  void (data_fprint) (const void *, FILE *));



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


/***************************************************
 * BinarySearchTreeNode
 ***************************************************/

/**
 * @brief Allocate a new binary search tree
 * @return
 */
BinarySearchTree * new_binary_search_tree(void (*type_manifest) (TypeDescriptor *));

/**
 * @brief Return the height of the tree
 * @param a tree
 * @return Binary tree height
 */
int binary_search_tree_height(const BinarySearchTree *self);

/**
 * @brief Return the number of nodes
 * @param a tree
 * @return
 */
int binary_search_tree_nb_nodes(const BinarySearchTree *self);

/**
 * @brief Return the number of leaves
 * @param a tree
 * @return
 */
int binary_search_tree_nb_leaves(const BinarySearchTree *self);

/**
 * @brief Return the number of internal nodes
 * @param a tree
 * @return
 */
int binary_search_tree_nb_internal_nodes(const BinarySearchTree *self);

/**
 * @brief Return the number nodes having two children
 * @param t
 * @return
 */
int binary_search_tree_nb_two_children(const BinarySearchTree *self);

/**
 * @brief Return true if a given tree is a perfect
 * binary tree
 * @param t
 * @return
 */
int binary_search_tree_is_perfect_bt(const BinarySearchTree *self);

/**
 * @brief Return a pointer to the min node
 * @param t
 * @return
 */
BinarySearchTreeNode * binary_search_tree_min(BinarySearchTree *self);

/**
 * @brief Return a pointer to the the max node
 * @param t
 * @return
 */
BinarySearchTreeNode * binary_search_tree_max(BinarySearchTree *self);

/**
 * @brief Return 1 if the binary tree is BST
 * and without duplicate
 *
 * @param a
 * @return int
 */
int binary_search_tree_is_bst(const BinarySearchTree *self);

/**
 * @brief add data to the tree
 * @param t
 * @param data
 * @return
 */
int binary_search_tree_add(BinarySearchTree *self, void * data);

/**
 * @brief Remove the minx node in the tree and return the pointer of its data
 * @param t
 * @return
 */
void * binary_search_tree_extract_min(BinarySearchTree *self);

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
int binary_search_tree_remove(BinarySearchTree *self, const void *data);

/**
 * @brief Return a pointer to the first occurrence of the node having data equal to the given one, trough preorder traversal
 * @param t
 * @param data
 * @return
 */
BinarySearchTree binary_search_tree_search(BinarySearchTree * t, const void * data);

/* Depth First Traversals */
void binary_search_tree_fprint_preorder(const BinarySearchTree *self, FILE * stream);
void binary_search_tree_fprint_inorder(const BinarySearchTree *self, FILE * stream);
void binary_search_tree_fprint_postorder(const BinarySearchTree *self, FILE * stream);

/**
 * @brief Make a formatted dot file of the struct
 * @param ll
 * @param dest_path
 */
void binary_search_tree_to_dot(const BinarySearchTree *self, const char *dest_path);

void binary_search_tree_clear(BinarySearchTree *self, void (*data_free) (void *));

/**
 * @brief Free the binary search tree
 * @param t
 */
void binary_search_tree_free(BinarySearchTree **self);

#endif /* MYLITTLECLIBRARY_MLCL_BinarySearchTree_H */
