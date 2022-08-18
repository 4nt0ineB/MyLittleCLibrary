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

#ifndef MYLITTLECLIBRARY_MLCL_AVLTREE_H
#define MYLITTLECLIBRARY_MLCL_AVLTREE_H

#include "MLCL_BinarySearchTree.h"

/**
 * @brief A generic AVL tree
 */
typedef struct s_avl_node {
    void * data;
    int balance; /* To help balancing the tree each node has relative balance */
    struct s_avl_node *left, *right;
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
    int n; /**< Number of nodes in the tree */
    int (*height) (AVLTree); /**< Return the height of the tree */
    int (*nb_nodes) (AVLTree); /**< Return the number of nodes. O(1) by the struct */
    int (*nb_leaves) (AVLTree); /**< Return the number of leaves */
    int (*nb_internal_nodes) (AVLTree); /**< Return the number of internal nodes */
    int (*nb_two_children) (AVLTree); /**< Number of nodes having two children */
    int  (*add) (AVLTree *, const void *); /**< add data to the tree */
    AVLTree (*min) (AVLTree); /**< Return a pointer to the min node */
    AVLTree (*max) (AVLTree); /**< Return a pointer to the the max node */
    int (*extract_min) (AVLTree *, void *);  /**< Remove the min node in the tree and return the pointer of its data */
    int (*extract_max) (AVLTree *, void *);  /**< Remove the max node in the tree and return the pointer of its data */
    int (*remove) (AVLTree *, const void *); /**< Remove the first occurrence of the given data trough preorder traversal  */
    AVLTree (*search) (AVLTree *, const void *); /**< Return a pointer to the first occurrence of the node having data equal to the given one, trough preorder traversal */
    int (*is_perfect_bt) (AVLTree); /**< Return 1 if the tree is a perfect binary tree, else 0 */
    int (*is_bst) (AVLTree); /**< Return 1 if the tree is a binary search tree, else 0 */
    void (*node_print) (AVLTreeNode *);  /**< Print the given node on stdout */
    void (*node_fprint) (FILE *, AVLTreeNode *); /**< Print the given node on the given stream */
    void (*fprint_preorder) (FILE *, AVLTree);
    void (*fprint_inorder) (FILE *, AVLTree);
    void (*fprint_postorder) (FILE *, AVLTree);
    void (*to_dot) (AVLTree, const char *); /**< Make a formatted dot file of the struct */
    void (*free) (AVLTree *); /**< Free to tree */
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
 * @brief Allocate a new AVL Trees
 * @param val
 * @return
 */
AVLTree new_avl_tree(const void * data, void (*type_manifest) (TypeDescriptor *));

/**
 * @brief Return the height of the tree
 * @param a tree
 * @return Binary tree height
 */
int avl_tree_height(AVLTree t);

/**
 * @brief Return the number of nodes
 * @param a tree
 * @return
 */
int avl_tree_nb_nodes(AVLTree t);

/**
 * @brief Return the number of leaves
 * @param a tree
 * @return
 */
int avl_tree_nb_leaves(AVLTree t);

/**
 * @brief Return the number of internal nodes
 * @param a tree
 * @return
 */
int avl_tree_nb_internal_nodes(AVLTree t);

/**
 * @brief Return the number nodes having two children
 * @param t
 * @return
 */
int avl_tree_nb_two_children(AVLTree t);

/**
 * @brief Return true if a given tree is a perfect
 * binary tree
 * @param t
 * @return
 */
int avl_tree_is_perfect_bt(AVLTree t);

/**
 * @brief Return a pointer to the min node
 * @param t
 * @return
 */
AVLTree avl_tree_min(AVLTree t);

/**
 * @brief Return a pointer to the the max node
 * @param t
 * @return
 */
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
 * @brief add data to the tree
 * @param t
 * @param data
 * @return
 */
int avl_tree_add(AVLTree * t, const void * data);

/**
 * @brief Remove the minx node in the tree and return the pointer of its data
 * @param r
 * @param rdata
 * @return
 */
int avl_tree_extract_min(AVLTree *r, void * rdata);

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
int avl_tree_remove(AVLTree * t, const void * data);

/**
 * @brief Return a pointer to the first occurrence of the node having data equal to the given one, trough preorder traversal
 * @param t
 * @param data
 * @return
 */
AVLTree avl_tree_search(AVLTree * t, const void * data);

/**
 * @brief Print the given node on stdout
 * @param n
 */
void avl_tree_node_print (AVLTreeNode * n);

/**
 * @brief Print the given node on the given stream
 * @param n
 */
void avl_tree_node_fprint (FILE * stream, AVLTreeNode * n);

/* Depth First Traversals */
void avl_tree_fprint_preorder(FILE * stream, AVLTree t);
void avl_tree_fprint_inorder(FILE * stream, AVLTree t);
void avl_tree_fprint_postorder(FILE * stream, AVLTree t);

/**
 * @brief Make a formatted dot file of the struct
 * @param ll
 * @param dest_path
 */
void avl_tree_to_dot(AVLTree t, const char * dest_path);

/**
 * @brief Free the descriptor of the Binary search tree
 * @param bstd
 */
void avl_tree_descriptor_free(AVLTreeDescriptor ** bstd);

/**
 * @brief Free the binary search tree
 * @param t
 */
void avl_tree_free(AVLTree * t);

#endif /* MYLITTLECLIBRARY_MLCL_AVLTREE_H */
