/*
 *   This file is part of the MLCL Library.
 *   Antoine Bastos 2022
 *
 *   This Library is free software under the terms of
 *   the MIT license.
 */

#ifndef MYLITTLECLIBRARY_MLCL_BINARYTREE_H
#define MYLITTLECLIBRARY_MLCL_BINARYTREE_H

#include "../include/MLCL_TypeDescriptor.h"
#include <stdlib.h>
#include <stdio.h>

/**
 * @brief A generic binary tree
 */
typedef struct s_binary_node {
    void * data;
    struct s_binary_node * left; /* left child */
    struct s_binary_node * right; /* right child */
    struct s_binary_tree_descriptor * d; /*!< Descriptor of the LinkedList */
} BinaryNode,  * BinaryTree;

/**
 * @brief Descriptor of the binary tree
 * The tree - the nodes - refers to a binary tree descriptor,
 * gathering implemented functions of the BinaryTree type, including
 * a TypeDescriptor allowing manipulation of the data, and the the number of nodes.
 */
typedef struct s_binary_tree_descriptor {
    TypeDescriptor * type_descriptor;
    int n;
    int (*height) (BinaryTree);
    int (*nb_nodes) (BinaryTree);
    int (*nb_leaves) (BinaryTree);
    int (*nb_internal_nodes) (BinaryTree);
    int (*nb_two_children) (BinaryTree);
    int (*is_bt) (BinaryTree);
    int (*is_bst) (BinaryTree);
    void (*node_print) (BinaryNode *);
    void (*node_fprint) (FILE *, BinaryNode *);
    void (*fprint_preorder) (FILE *, BinaryTree);
    void (*fprint_inorder) (FILE *, BinaryTree);
    void (*fprint_postorder) (FILE *, BinaryTree);
} BinaryTreeDescriptor;

/**
 * @brief Allocate and return a default
 * binary tree descriptor. Type descriptor set to null.
 * @return
 */
BinaryTreeDescriptor * binary_tree_descriptor();

/**
 * @brief A detailed constructor for the nodes of a binary tree.
 * @param data First cell's data.
 * @param descriptor The binary tree descriptor.
 * @return
 */
BinaryNode * binary_tree_builder(const void * data, BinaryTreeDescriptor * descriptor);

/**
 *
 * @param val
 * @return
 */
BinaryTree new_binary_tree(const void * data, void (*type_manifest) (TypeDescriptor *));

/**
 *
 * @param a tree
 * @return Binary tree height
 */
int binary_tree_height(BinaryTree t);

/**
 * Return the number of nodes
 * @param a tree
 * @return
 */
int binary_tree_nb_nodes(BinaryTree t);

/**
 * Return the number of leaves
 * @param a tree
 * @return
 */
int binary_tree_nb_leaves(BinaryTree t);

/**
 * Return the number of internal nodes
 * @param a tree
 * @return
 */
int binary_tree_nb_internal_nodes(BinaryTree t);

/**
 * Return the number nodes having two children
 * @param t
 * @return
 */
int binary_tree_nb_two_children(BinaryTree t);

/**
 * Return true if a given tree is a perfect
 * binary tree
 * @param t
 * @return
 */
int binary_tree_is_bt(BinaryTree t);

/**
 * @brief Return 1 if the binary tree is BST
 * and without duplicate
 *
 * @param a
 * @return int
 */
int binary_tree_is_bst(BinaryTree t);

/**
 *
 * @param n
 */
void binary_tree_node_print (BinaryNode * n);

/**
 *
 * @param n
 */
void binary_tree_node_fprint (FILE * stream, BinaryNode * n);



/* Depth First Traversals */
void binary_tree_fprint_preorder(FILE * stream, BinaryTree t);
void binary_tree_fprint_inorder(FILE * stream, BinaryTree t);
void binary_tree_fprint_postorder(FILE * stream, BinaryTree t);



#endif /* MYLITTLECLIBRARY_MLCL_BINARYTREE_H */
