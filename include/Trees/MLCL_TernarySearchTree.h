/*
 *   This file is part of the MLCL Library.
 *   Antoine Bastos 2022
 *
 *   This Library is free software under the terms of
 *   the MIT license.
 */

#ifndef MYLITTLECLIBRARY_MLCL_TERNARYSEARCHTREE_H
#define MYLITTLECLIBRARY_MLCL_TERNARYSEARCHTREE_H

#include "../MLCL_TypeDescriptor.h"
#include "../Lists/MLCL_List.h"

#define MLCL_TST_STOP_CHAR '\0'
#define MLCL_TST_BUFF_SIZE 500

/**
 * Ternary search tree with char / prefix tree / lexical tree
 */
typedef struct s_ternary_search_node {
    void *data;
    struct s_ternary_search_tree_descriptor *d;
    struct s_ternary_search_node *left, *child, *right;
} TernarySearchNode, *TernarySearchTree;

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
} TernarySearchTreeDescriptor;

TernarySearchTreeDescriptor * ternary_search_tree_descriptor();
TernarySearchNode * ternary_search_tree_builder(const void * data, TernarySearchTreeDescriptor *d);
TernarySearchTree new_ternary_search_tree(const char * word);

int ternary_search_tree_insert_branch(TernarySearchTree * ancestor, TernarySearchTree * t, const char * word);
int ternary_search_tree_add(TernarySearchTree *t, const char * word);
int ternary_search_tree_search(const TernarySearchTree t, const char *word);
void ternary_search_tree_remove(TernarySearchTree *t, const char * word);
void ternary_search_tree_print(const TernarySearchTree t);
void ternary_search_tree_fprint_(FILE *stream, const TernarySearchTree t, List *l, int i);
void ternary_search_tree_fprint(FILE *stream, const TernarySearchTree t);
void ternary_search_tree_free_descriptor(TernarySearchTreeDescriptor **tstd);
void ternary_search_tree_free(TernarySearchTree *t);

#endif /* MYLITTLECLIBRARY_MLCL_TERNARYSEARCHTREE_H */
