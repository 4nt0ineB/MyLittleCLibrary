/*
 *   This file is part of the MLCL Library
 *   Antoine Bastos 2022
 *   SPDX-License-Identifier: Apache-2.0
 */

#include "../../../include/data-structures/Trees/MLCL_BKTree.h"
#include "../../../include/core/MLCL_primitive_types.h"
#include "../../../include/utils/MLCL_utils.h"


/***************************************************
 * BKTreeNode
 ***************************************************/

BKTreeNode * new_bk_tree_node(void *data){
    BKTreeNode *node;
    if(!data) return NULL;
    node = (BKTreeNode *) malloc(sizeof(BKTreeNode));
    if(!node) return NULL;
    node->value = 0;
    node->data = data;
    node->child = node->siblings = NULL;
    return node;
}

void bk_tree_node_free(BKTreeNode **self, void (data_free) (void *)){
    if(!*self) return;
    if(data_free)
        data_free((*self)->data);
    free(*self);
    *self = NULL;
}


/***************************************************
 * BKTree
 ***************************************************/


BKTree * new_bk_tree(){
    BKTree *tree;
    tree = (BKTree *) malloc(sizeof(BKTree));
    if(!tree) return NULL;
    tree->n = 0;
    tree->root = NULL;
    tree->td = new_type_descriptor(str_m);
    if(!tree->td)
        bk_tree_free(&tree);
    return tree;
}

static int bk_tree_insert_node_(BKTreeNode **root, BKTreeNode *bk_tree_node) {
    int d;
    BKTreeNode **tmp;
    /* Empty tree */
    if (!*root) {
        *root = bk_tree_node;
        return 1;
    }
    d = mlevenshtein((*root)->data, bk_tree_node->data);

    /* Already exists ?*/
    if (d == 0) {
        return 0;
    }

    /* Child ? */
    if ((*root)->value == bk_tree_node->value) {
        bk_tree_node->value = d;
        return bk_tree_insert_node_(&(*root)->child, bk_tree_node);
    }
    /* Look up on siblings / (siblings as ordered list) */
    tmp = &(*root)->siblings;

    /* No siblings */
    if (!*tmp) {
        *tmp = bk_tree_node;
        return 1;

    }else if ((*tmp)->value > bk_tree_node->value){
        bk_tree_node->siblings = (*tmp);
        (*tmp) = bk_tree_node;
        return 1;

    }

    return bk_tree_insert_node_(&(*tmp), bk_tree_node);
}

static int bk_tree_add_(BKTreeNode **root, char *word){
    BKTreeNode *node;
    if(!word) return 0;
    node = new_bk_tree_node(new_str(word));
    if(!node) return 0;
    return bk_tree_insert_node_(root, node);
}

int bk_tree_add(BKTree *self, char * word){
    if(!self) return 0;
    return bk_tree_add_(&self->root, word) && (++self->n || 1);
}

static void bk_tree_fprint_(const BKTreeNode *root, FILE *stream, int t, void (*data_fprint) (const void *, FILE *stream)){
    int i;
    if(!root) return;
    for(i = 0; i < t; i++)
        printf("      ");
    fprintf(stream, "%s%d─> ",(root->siblings) ? "├─" : "└─", root->value);
    data_fprint(root->data, stream);
    fprintf(stream, "\n");
    bk_tree_fprint_(root->child, stream, t + 1, data_fprint);
    bk_tree_fprint_(root->siblings, stream, t, data_fprint);
}

void bk_tree_fprint(const BKTree *self, FILE *stream){
    if(!self || !self->root) return;
    self->td->fprint(self->root->data, stream);
    if(self->root->child || self->root->siblings){
        fprintf(stream, "\n");
        bk_tree_fprint_(self->root->child, stream, 0, self->td->fprint);
        bk_tree_fprint_(self->root->siblings, stream, 0, self->td->fprint);
    }
}

void bk_tree_print(const BKTree *self){
    bk_tree_fprint(self, stdout);
}

int bk_tree_fuzzy_search_(const BKTreeNode *root, int *s, const char *word, List *r_suggestions){
    int d;
    BKTreeNode *tmp;
    if(!root) return 0;
    d = mlevenshtein(word, root->data);

    if(d < *s){
        *s = d;
        /* list_get_td(r_suggestions)->data_free */
        list_clear(r_suggestions, str_free);
    }

    /* Word exits in the tree */
    if(d == 0){
        list_clear(r_suggestions, str_free);
        return 1;
    }

    if(d <= *s)
        list_prepend(r_suggestions, new_str(root->data));

    if(root->child){
        if(abs(d - root->child->value) <= *s){
            bk_tree_fuzzy_search_(root->child, s, word, r_suggestions);
        }

        if(!root->child->siblings)
            return !list_length(r_suggestions);
        tmp = root->child->siblings;
        while(tmp){
            if(abs(d - tmp->value) <= *s){
                bk_tree_fuzzy_search_(tmp, s, word, r_suggestions);
            }
            tmp = tmp->siblings;
        }
    }
    return 0;
}

int bk_tree_fuzzy_search(const BKTree *self, const char *word, List *r_suggestions){
    int x;
    x = __INT_MAX__;
    if(!self || !word) return 0;
    return bk_tree_fuzzy_search_(self->root, &x, word, r_suggestions);
}

static void bk_tree_clear_(BKTreeNode **root, void (*data_free) (void *)){
    if(!*root) return;

    bk_tree_clear_(&(*root)->siblings, data_free);
    bk_tree_clear_(&(*root)->child, data_free);

    free((*root)->data);

    free(*root);
    *root = NULL;
}

void bk_tree_clear(BKTree *self){
    if(!self) return;
    bk_tree_clear_(&self->root, self->td->data_free);
    self->n = 0;
}

void bk_tree_free(BKTree **self){
    if(!*self) return;
    bk_tree_clear(*self);
    type_descriptor_free(&(*self)->td);
    free(*self);
    *self = NULL;
}

void bk_tree_to_dot_(const BKTreeNode *root, FILE *stream, void (*data_fprint) (const void *, FILE *)){
    BKTreeNode *tmp;
    if(!root || !data_fprint) return;
    fprintf(stream, "  n%p [label=\"", (void *) &*root);
    data_fprint(root->data, stream);
    fprintf(stream, "\"]\n");
    if(root->child){
        fprintf(stream,
                "  n%p -> n%p [color=\"#2257ab\", label=\" %d \"]\n",
                (void *) &*root, (void *) root->child, root->child->value);
        bk_tree_to_dot_(root->child, stream, data_fprint);

        if(!(tmp = root->child->siblings))
            return;

        while(tmp){
            fprintf(stream, "  n%p [label=\"",(void *) &*tmp);
            data_fprint(tmp->data, stream);
            fprintf(stream, "\"]\n");
            fprintf(stream, "  n%p -> n%p [color=\"#2257ab\", label=\" %d \"]\n", (void *) &*root, (void *) tmp, tmp->value);
            /* @Todo bad: do not use while use proper recursion */
            bk_tree_to_dot_(tmp, stream, data_fprint);
            tmp = tmp->siblings;
        }
    }
}

void bk_tree_to_dot(const BKTree *self, const char *path){
    FILE *file = fopen(path, "w");
    fprintf(file, "digraph tree {\n"
                  "\n"
                  "   \n"
                  "  \n\n");
    bk_tree_to_dot_(self->root, file, self->td->fprint);
    fprintf(file, "\n}");
}