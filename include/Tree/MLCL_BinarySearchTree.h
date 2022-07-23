/*
 *   This file is part of the MLCL Library.
 *   Antoine Bastos 2022
 *
 *   This Library is free software under the terms of
 *   the MIT license.
 */

#ifndef MYLITTLECLIBRARY_MLCL_BinarySearchTree_H
#define MYLITTLECLIBRARY_MLCL_BinarySearchTree_H

#include "../MLCL_TypeDescriptor.h"
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
    TypeDescriptor * type_descriptor;
    int n;
    int (*height) (BinarySearchTree);
    int (*nb_nodes) (BinarySearchTree);
    int (*nb_leaves) (BinarySearchTree);
    int (*nb_internal_nodes) (BinarySearchTree);
    int (*nb_two_children) (BinarySearchTree);
    int  (*binary_search_tree_is_bst) (BinarySearchTree t);
    int  (*add) (BinarySearchTree *, const void *);
    BinarySearchTree (*min) (BinarySearchTree);
    BinarySearchTree (*max) (BinarySearchTree);
    void * (*extract_min) (BinarySearchTree *);
    void * (*extract_max) (BinarySearchTree *);
    int  (*remove) (BinarySearchTree *, const void *);
    BinarySearchTree  (*search) (BinarySearchTree *, const void *);
    int (*is_perfect_bt) (BinarySearchTree);
    int (*is_bst) (BinarySearchTree);
    void (*node_print) (BinarySearchTreeNode *);
    void (*node_fprint) (FILE *, BinarySearchTreeNode *);
    void (*fprint_preorder) (FILE *, BinarySearchTree);
    void (*fprint_inorder) (FILE *, BinarySearchTree);
    void (*fprint_postorder) (FILE *, BinarySearchTree);
    void (*to_dot) (BinarySearchTree, const char *);
    void (*free) (BinarySearchTree *);
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
 *
 * @param val
 * @return
 */
BinarySearchTree new_binary_search_tree(const void * data, void (*type_manifest) (TypeDescriptor *));

/**
 *
 * @param a tree
 * @return Binary tree height
 */
int binary_search_tree_height(BinarySearchTree t);

/**
 * Return the number of nodes
 * @param a tree
 * @return
 */
int binary_search_tree_nb_nodes(BinarySearchTree t);

/**
 * Return the number of leaves
 * @param a tree
 * @return
 */
int binary_search_tree_nb_leaves(BinarySearchTree t);

/**
 * Return the number of internal nodes
 * @param a tree
 * @return
 */
int binary_search_tree_nb_internal_nodes(BinarySearchTree t);

/**
 * Return the number nodes having two children
 * @param t
 * @return
 */
int binary_search_tree_nb_two_children(BinarySearchTree t);

/**
 * Return true if a given tree is a perfect
 * binary tree
 * @param t
 * @return
 */
int binary_search_tree_is_perfect_bt(BinarySearchTree t);

BinarySearchTree binary_search_tree_min(BinarySearchTree t);

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
 *
 * @param t
 * @param data
 * @return
 */
int binary_search_tree_add(BinarySearchTree * t, const void * data);

void * binary_search_tree_extract_min(BinarySearchTree * t);

void * binary_search_tree_extract_max(BinarySearchTree * t);

/**
 *
 * @param t
 * @param data
 * @return
 */
int binary_search_tree_remove(BinarySearchTree * t, const void * data);

/**
 *
 * @param t
 * @param data
 * @return
 */
BinarySearchTree binary_search_tree_search(BinarySearchTree * t, const void * data);

/**
 *
 * @param n
 */
void binary_search_tree_node_print (BinarySearchTreeNode * n);

/**
 *
 * @param n
 */
void binary_search_tree_node_fprint (FILE * stream, BinarySearchTreeNode * n);



/* Depth First Traversals */
void binary_search_tree_fprint_preorder(FILE * stream, BinarySearchTree t);
void binary_search_tree_fprint_inorder(FILE * stream, BinarySearchTree t);
void binary_search_tree_fprint_postorder(FILE * stream, BinarySearchTree t);

/**
 *
 * @param ll
 * @param dest_path
 */
void binary_search_tree_to_dot(BinarySearchTree t, const char * dest_path);

/**
 *
 * @param bstd
 */
void binary_search_tree_descriptor_free(BinarySearchTreeDescriptor ** bstd);

/**
 *
 * @param t
 */
void binary_search_tree_free(BinarySearchTree * t);

#endif /* MYLITTLECLIBRARY_MLCL_BinarySearchTree_H */
