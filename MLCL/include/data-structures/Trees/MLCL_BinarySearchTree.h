/*
 *   This file is part of the MLCL Library
 *   Copyrleft 2022 Antoine Bastos
 *   SPDX-License-Identifier: Apache-2.0
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
    void *data;
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
int binary_search_tree_add(BinarySearchTree *self, void *data);

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
BinarySearchTreeNode * binary_search_tree_search(BinarySearchTree *self, const void *data);

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
