/*
 *   This file is part of the MLCL Library
 *   Copyrleft 2022 Antoine Bastos
 *   SPDX-License-Identifier: Apache-2.0
 */

#ifndef MYLITTLECLIBRARY_MLCL_AVLTREE_H
#define MYLITTLECLIBRARY_MLCL_AVLTREE_H

#include "MLCL_BinarySearchTree.h"

/**
 * @brief A generic AVL tree
 */
typedef struct AVLTreeNode {
    void *data;
    int balance; /* To help balancing the tree each node has relative balance */
    struct AVLTreeNode *left, *right;
} AVLTreeNode;

typedef struct AVLTree {
    int n;
    AVLTreeNode *root;
    TypeDescriptor *td;
}AVLTree;


/***************************************************
 * AVlTreeNode
 ***************************************************/

AVLTreeNode * new_avl_tree_node(void *data);

void avl_tree_node_free(AVLTreeNode **self, void (*data_free) (void *));

/**
 * @brief Print the given node on stdout
 * @param n
 */
void avl_tree_node_print(const AVLTreeNode *self,  void (data_fprint) (const void *, FILE *));

/**
 * @brief Print the given node on the given stream
 * @param n
 */
void avl_tree_node_fprint (const AVLTreeNode *self, FILE * stream,  void (data_fprint) (const void *, FILE *));



/***************************************************
 * AVlTree
 ***************************************************/

/**
 * @brief Allocate a new AVL Trees
 * @param val
 * @return
 */
AVLTree * new_avl_tree(void (*type_manifest) (TypeDescriptor *));

/**
 * @brief Return the height of the tree
 * @param a tree
 * @return Binary tree height
 */
int avl_tree_height(const AVLTree *self);

/**
 * @brief Return the number of nodes
 * @param a tree
 * @return
 */
int avl_tree_nb_nodes(const AVLTree *self);

/**
 * @brief Return the number of leaves
 * @param a tree
 * @return
 */
int avl_tree_nb_leaves(const AVLTree *self);

/**
 * @brief Return the number of internal nodes
 * @param a tree
 * @return
 */
int avl_tree_nb_internal_nodes(const AVLTree *self);

/**
 * @brief Return the number nodes having two children
 * @param t
 * @return
 */
int avl_tree_nb_two_children(const AVLTree *self);

/**
 * @brief Return true if a given tree is a perfect
 * binary tree
 * @param t
 * @return
 */
int avl_tree_is_perfect_bt(const AVLTree *self);

/**
 * @brief Return a pointer to the min node
 * @param t
 * @return
 */
AVLTreeNode * avl_tree_min(AVLTree *self);

/**
 * @brief Return a pointer to the the max node
 * @param t
 * @return
 */
AVLTreeNode * avl_tree_max(AVLTree *self);

/**
 * @brief Return 1 if the binary tree is BST
 * and without duplicate
 *
 * @param a
 * @return int
 */
int avl_tree_is_bst(const AVLTree *self);

/**
 * @brief add data to the tree
 * @param t
 * @param data
 * @return
 */
int avl_tree_add(AVLTree *self, void *data);

/**
 * @brief Remove the minx node in the tree and return the pointer of its data
 * @param r
 * @param rdata
 * @return
 */
int avl_tree_extract_min(AVLTree *self, void * rdata);

/**
 * @brief Remove the max node in the tree and return the pointer of its data
 * @param r
 * @param rdata
 * @return
 */
int avl_tree_extract_max(AVLTree *r, void * rdata);

/**
 * @brief Remove the first occurrence of the given data trough preorder traversal
 * @param t
 * @param data
 * @return
 */
int avl_tree_remove(AVLTree *self, const void *data);

/**
 * @brief Return a pointer to the first occurrence of the node having data equal to the given one, trough preorder traversal
 * @param t
 * @param data
 * @return
 */
AVLTreeNode * avl_tree_search(AVLTree *self, const void *data);

/* Depth First Traversals */
void avl_tree_fprint_preorder(const AVLTree *self, FILE *stream);
void avl_tree_fprint_inorder(const AVLTree *self, FILE *stream);
void avl_tree_fprint_postorder(const AVLTree *self, FILE *stream);

/**
 * @brief Make a formatted dot file of the struct
 * @param ll
 * @param dest_path
 */
void avl_tree_to_dot(const AVLTree *self, const char *dest_path);

/**
 * @brief Clear the binary search tree
 * @param t
 */
void avl_tree_clear(AVLTree *self, void (*data_free) (void *));

/**
 * @brief Free the binary search tree
 * @param t
 */
void avl_tree_free(AVLTree **self);

#endif /* MYLITTLECLIBRARY_MLCL_AVLTREE_H */
