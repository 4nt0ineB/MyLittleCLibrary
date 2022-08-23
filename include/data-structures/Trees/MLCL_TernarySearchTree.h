/*
 *   This file is part of the MLCL Library
 *   Copyright 2022 Antoine Bastos
 *   SPDX-License-Identifier: Apache-2.0
 */

#ifndef MYLITTLECLIBRARY_MLCL_TERNARYSEARCHTREE_H
#define MYLITTLECLIBRARY_MLCL_TERNARYSEARCHTREE_H

#include "../../core/MLCL_TypeDescriptor.h"
#include "../Lists/MLCL_List.h"

#define MLCL_TST_STOP_CHAR '\0'

/**
 * Ternary search tree with char / prefix tree / lexical tree
 */
typedef struct TernarySearchTreeNode {
    void *data;
    struct TernarySearchTreeNode *left, *child, *right;
} TernarySearchTreeNode;

typedef struct {
    int n;
    TernarySearchTreeNode *root;
    TypeDescriptor *td;
} TernarySearchTree;

typedef struct s_ternary_search_tree_descriptor {
    int n;
    TypeDescriptor *type_descriptor;
    int (*insert_branch) (TernarySearchTree *, TernarySearchTree *, const char *);
    int (*add) (TernarySearchTree *, const char *);
    int (*search) (const TernarySearchTree, const char *);
    void (*remove) (TernarySearchTree *, const char *);
    void (*print) (const TernarySearchTree);
    void (*fprint_) (FILE *stream, const TernarySearchTree, List *, int);
    void (*fprint) (FILE *, const TernarySearchTree);
    void (*free) (TernarySearchTree *);
    void (*to_dot_) (const TernarySearchTree, FILE *);
    void (*to_dot) (const TernarySearchTree, const char *);
} TernarySearchTreeDescriptor;

/***************************************************
 * TernarySearchTreeNode
 ***************************************************/
TernarySearchTreeNode * new_ternary_search_tree_node(void *data);
void ternary_search_tree_node_free(TernarySearchTreeNode **self, void (data_free) (void *));


/***************************************************
 * TernarySearchTree
 ***************************************************/

int ternary_search_tree_insert_branch_(TernarySearchTreeNode **root, char * word);
int ternary_search_tree_add_(TernarySearchTreeNode **root, char * word, int (*cmp) (const void *, const void *));
int ternary_search_tree_add(TernarySearchTree *self, char *word);
int ternary_search_tree_search_(const TernarySearchTreeNode *root, const char *word, int (cmp) (const void *, const void *));
int ternary_search_tree_search(const TernarySearchTree *self, const char *word);
int ternary_search_tree_remove_(TernarySearchTreeNode **root, char *word, int (*cmp) (const void*, const void*), void (*data_free) (void *));
int ternary_search_tree_remove(TernarySearchTree *self, char *word);
void ternary_search_tree_fprint_(const TernarySearchTreeNode *t, FILE *stream, List *l, int i);
void ternary_search_tree_fprint(const TernarySearchTree *self, FILE *stream);
void ternary_search_tree_print(const TernarySearchTree *self);
void ternary_search_tree_clear_(TernarySearchTreeNode **root, void (data_free) (void *));
void ternary_search_tree_clear(TernarySearchTree *self, void (data_free) (void *));
void ternary_search_tree_free(TernarySearchTree **self);
void ternary_tree_to_dot_(const TernarySearchTreeNode *root, FILE * stream);
void ternary_tree_to_dot(const TernarySearchTree *self, const char *path);
#endif /* MYLITTLECLIBRARY_MLCL_TERNARYSEARCHTREE_H */
