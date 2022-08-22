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

#include "../../../include/data-structures/Trees/MLCL_BKTree.h"
#include "../../../include/core/MLCL_basic_types.h"
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
    return NULL;
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


BKTree * new_bk_tree(void (*type_manifest) (TypeDescriptor *)){
    BKTree *tree;
    if(!type_manifest) return NULL;
    tree = (BKTree *) malloc(sizeof(BKTree));
    if(!tree) return NULL;
    tree->n = 0;
    tree->root = NULL;
    tree->td = new_type_descriptor(type_manifest);
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
    d = mlcl_levenshtein((*root)->data, bk_tree_node->data);

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
    if(!*root) return 0;
    if(!word)
        return 0;
    node = new_bk_tree_node(word);
    if(!node) return 0;
    return bk_tree_insert_node_(root, node);
}

int bk_tree_insert_add(BKTree *self, char * word){
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
    if(!self) return;
    self->td->fprint(self->root->data, stream);
    fprintf(stream, "\n");
    bk_tree_fprint_(self->root->child, stream, 0, self->td->fprint);
    bk_tree_fprint_(self->root->siblings, stream, 0, self->td->fprint);
}

void bk_tree_print(const BKTree *self){
    bk_tree_fprint(self, stdout);
}

int bk_tree_fuzzy_search_(const BKTreeNode *root, int *s, const char *word, List *r_suggestions){
    int d;
    BKTreeNode *tmp;
    if(!root) return 0;
    d = mlcl_levenshtein(word, root->data);

    if(d < *s){
        *s = d;
        list_clear(r_suggestions, list_get_td(r_suggestions)->data_free);
    }

    /* Word exits in the tree */
    if(d == 0){
        list_clear(r_suggestions, list_get_td(r_suggestions)->data_free);
        return 1;
    }

    if(d <= *s)
        list_prepend(r_suggestions, root->data);

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

    bk_tree_clear_(&(*root)->child, data_free);
    bk_tree_clear_(&(*root)->siblings, data_free);

    if(data_free)
        data_free(&(*root)->data);

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
    fprintf(file, "digraph arbre {\n"
                  "\n"
                  "   \n"
                  "  \n\n");
    bk_tree_to_dot_(self->root, file, self->td->fprint);
    fprintf(file, "\n}");
}