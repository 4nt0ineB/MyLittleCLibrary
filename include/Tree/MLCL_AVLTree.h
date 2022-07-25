/*
 *   This file is part of the MLCL Library.
 *   Antoine Bastos 2022
 *
 *   This Library is free software under the terms of
 *   the MIT license.
 */

#ifndef MYLITTLECLIBRARY_MLCL_AVLTREE_H
#define MYLITTLECLIBRARY_MLCL_AVLTREE_H

#include "MLCL_BinarySearchTree.h"

/**
 * @brief A generic AVL tree
 */
typedef struct s_avl_node_ {
    void * data;
    int balance;
    struct s_avl_node_ *left, *right;
    struct s_avl_tree_descriptor * d; /*!< Descriptor of the binary tree */
} AVLTreeNode, *AVLTree;

/**
 * @brief Descriptor of the AVL tree
 * The tree - the nodes - refers to a binary tree descriptor,
 * gathering implemented functions of the BinarySearchTree type, including
 * a TypeDescriptor allowing manipulation of the data, and the the number of nodes.
 */
typedef struct s_avl_tree_descriptor {
    TypeDescriptor * type_descriptor;
    int n;
    int (*height) (AVLTree);
    int (*nb_nodes) (AVLTree);
    int (*nb_leaves) (AVLTree);
    int (*nb_internal_nodes) (AVLTree);
    int (*nb_two_children) (AVLTree);
    int  (*binary_search_tree_is_bst) (AVLTree t);
    int  (*add) (AVLTree *, const void *);
    AVLTree (*min) (AVLTree);
    AVLTree (*max) (AVLTree);
    int (*extract_min) (AVLTree *, void *);
    int (*extract_max) (AVLTree *, void *);
    int (*remove) (AVLTree *, const void *);
    AVLTree (*search) (AVLTree *, const void *);
    int (*is_perfect_bt) (AVLTree);
    int (*is_bst) (AVLTree);
    void (*node_print) (AVLTreeNode *);
    void (*node_fprint) (FILE *, AVLTreeNode *);
    void (*fprint_preorder) (FILE *, AVLTree);
    void (*fprint_inorder) (FILE *, AVLTree);
    void (*fprint_postorder) (FILE *, AVLTree);
    void (*to_dot) (AVLTree, const char *);
    void (*free) (AVLTree *);
} AVLTreeDescriptor;

/**
 * @brief Allocate and return a default
 * avl tree descriptor. Type descriptor set to null.
 * @return
 */
AVLTreeDescriptor * avl_tree_descriptor();

/**
 * @brief A detailed constructor for the nodes of a avl tree.
 * @param data First cell's data.
 * @param descriptor The binary tree descriptor.
 * @return
 */
AVLTreeNode * avl_tree_builder(const void * data, AVLTreeDescriptor * descriptor);

/**
 *
 * @param val
 * @return
 */
AVLTree new_avl_tree(const void * data, void (*type_manifest) (TypeDescriptor *));

/**
 *
 * @param a tree
 * @return Binary tree height
 */
int avl_tree_height(AVLTree t);

/**
 * Return the number of nodes
 * @param a tree
 * @return
 */
int avl_tree_nb_nodes(AVLTree t);

/**
 * Return the number of leaves
 * @param a tree
 * @return
 */
int avl_tree_nb_leaves(AVLTree t);

/**
 * Return the number of internal nodes
 * @param a tree
 * @return
 */
int avl_tree_nb_internal_nodes(AVLTree t);

/**
 * Return the number nodes having two children
 * @param t
 * @return
 */
int avl_tree_nb_two_children(AVLTree t);

/**
 * Return true if a given tree is a perfect
 * binary tree
 * @param t
 * @return
 */
int avl_tree_is_perfect_bt(AVLTree t);

AVLTree avl_tree_min(AVLTree t);

AVLTree avl_tree_max(AVLTree t);

/**
 * @brief Return 1 if the binary tree is BST
 * and without duplicate
 *
 * @param a
 * @return int
 */
int avl_tree_is_bst(AVLTree t);

/**
 *
 * @param t
 * @param data
 * @return
 */
int avl_tree_add(AVLTree * t, const void * data);

int avl_tree_extract_min(AVLTree *r, void * rdata);

int avl_tree_extract_max(AVLTree *r, void * rdata);

/**
 *
 * @param t
 * @param data
 * @return
 */
int avl_tree_remove(AVLTree * t, const void * data);

/**
 *
 * @param t
 * @param data
 * @return
 */
AVLTree avl_tree_search(AVLTree * t, const void * data);

/**
 *
 * @param n
 */
void avl_tree_node_print (AVLTreeNode * n);

/**
 *
 * @param n
 */
void avl_tree_node_fprint (FILE * stream, AVLTreeNode * n);



/* Depth First Traversals */
void avl_tree_fprint_preorder(FILE * stream, AVLTree t);
void avl_tree_fprint_inorder(FILE * stream, AVLTree t);
void avl_tree_fprint_postorder(FILE * stream, AVLTree t);

/**
 *
 * @param ll
 * @param dest_path
 */
void avl_tree_to_dot(AVLTree t, const char * dest_path);

/**
 *
 * @param bstd
 */
void avl_tree_descriptor_free(AVLTreeDescriptor ** bstd);

/**
 *
 * @param t
 */
void avl_tree_free(AVLTree * t);

#endif /* MYLITTLECLIBRARY_MLCL_AVLTREE_H */
