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

#ifndef MYLITTLECLIBRARY_MLCL_TERNARYSEARCHTREE_H
#define MYLITTLECLIBRARY_MLCL_TERNARYSEARCHTREE_H

#include "../../core/MLCL_TypeDescriptor.h"
#include "../Lists/MLCL_List.h"

#define MLCL_TST_STOP_CHAR '\0'

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
    void (*to_dot_) (const TernarySearchTree, FILE *);
    void (*to_dot) (const TernarySearchTree, const char *);
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
void ternary_tree_to_dot_(const TernarySearchTree t, FILE * stream);
void ternary_tree_to_dot(const TernarySearchTree t, const char * path);
#endif /* MYLITTLECLIBRARY_MLCL_TERNARYSEARCHTREE_H */
