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

#ifndef MYLITTLECLIBRARY_MLCL_BKTREE_H
#define MYLITTLECLIBRARY_MLCL_BKTREE_H

#include "../../core/MLCL_TypeDescriptor.h"
#include "../Lists/MLCL_List.h"


typedef struct s_bk_node {
    int value;
    void * data;
    struct s_bk_node *child;
    struct s_bk_node *siblings;
    struct s_bk_tree_descriptor *d;
} BKTreeNode, *BKTree;

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

BKTreeNode * bk_tree_builder(const void *data, BKtreeDescriptor *d);
BKTree new_bk_tree(const char *word);
int bk_tree_insert_node(BKTree *root, BKTreeNode *bk_tree_node);
int bk_tree_add(BKTree *root, const char *word);

void bk_tree_fprint_(FILE *stream, const BKTree root, int t);
void bk_tree_fprint(FILE *stream, const BKTree root);
void bk_tree_print(const BKTree root);

/**
 *
 * @param root
 * @param s maximum edit distance for suggestions
 * @param word
 * @param r_suggestions
 * @return
 */
int bk_tree_fuzzy_search_(const BKTree *root, int *s, const char *word, List *r_suggestions);
int bk_tree_fuzzy_search(const BKTree *root, const char *word, List *r_suggestions);
/*
void (*to_dot_) (const BKTree, FILE *);
void (*to_dot) (const BKTree, const char *);
*/

void bk_tree_free_descriptor(BKtreeDescriptor **d);
void bk_tree_free(BKTree *root);

void bk_tree_to_dot_(const BKTree root, FILE *file);
void bk_tree_to_dot(const BKTree root, const char *path);

#endif /* MYLITTLECLIBRARY_MLCL_BKTREE_H */
