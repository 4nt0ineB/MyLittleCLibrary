/*
 *   This file is part of the MLCL Library
 *   Copyright 2022 Antoine Bastos
 *   SPDX-License-Identifier: Apache-2.0
 */

#ifndef MYLITTLECLIBRARY_MLCL_BKTREE_H
#define MYLITTLECLIBRARY_MLCL_BKTREE_H

#include "../../core/MLCL_TypeDescriptor.h"
#include "../Lists/MLCL_List.h"


typedef struct BKTreeNode {
    int value;
    void *data;
    struct BKTreeNode *child, *siblings;
} BKTreeNode;


typedef struct {
    int n;
    BKTreeNode *root;
    TypeDescriptor *td;
} BKTree;

typedef struct s_bk_tree_descriptor {
    int n;
    TypeDescriptor *type_descriptor;

    int (*insert_node) (BKTree *, BKTreeNode *);
    int (*add) (BKTree *, const char *);
    int (*fuzzy_search_) (const BKTree *, int *, const char *, List *);
    int (*fuzzy_search) (const BKTree *, const char *, List * );

    void (*fprint_) (FILE *, const BKTree, int);
    void (*fprint) (FILE *, const BKTree);
    void (*print) (const BKTree);

    void (*to_dot_) (const BKTree, FILE *);
    void (*to_dot) (const BKTree, const char *);
    void (*free) (BKTree *);
} BKtreeDescriptor;

/***************************************************
 * BKTreeNode
 ***************************************************/
BKTreeNode * new_bk_tree_node(void *data);
void bk_tree_node_free(BKTreeNode **self, void (data_free) (void *));


/***************************************************
 * BKTree
 ***************************************************/
BKTree * new_bk_tree();
int bk_tree_insert_node(BKTree *root, BKTreeNode *bk_tree_node);
int bk_tree_add(BKTree *root, char *word);
void bk_tree_fprint(const BKTree *self, FILE *stream);
void bk_tree_print(const BKTree *self);

/**
 *
 * @param root
 * @param s maximum edit distance for suggestions
 * @param word
 * @param r_suggestions
 * @return
 */
int bk_tree_fuzzy_search_(const BKTreeNode *root, int *s, const char *word, List *r_suggestions);
int bk_tree_fuzzy_search(const BKTree *self, const char *word, List *r_suggestions);
void bk_tree_free(BKTree **self);
void bk_tree_to_dot_(const BKTreeNode *root, FILE *stream, void (*data_fprint) (const void *, FILE *));
void bk_tree_to_dot(const BKTree *self, const char *path);

#endif /* MYLITTLECLIBRARY_MLCL_BKTREE_H */