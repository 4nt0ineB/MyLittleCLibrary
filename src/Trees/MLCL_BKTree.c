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

#include "../../include/Trees/MLCL_BKTree.h"
#include "../../include/MLCL_basic_types.h"
#include "../../include/MLCL_utils.h"


BKtreeDescriptor * bk_tree_descriptor(){
    BKtreeDescriptor *d;
    d = (BKtreeDescriptor *) malloc(sizeof(BKtreeDescriptor));
    if(!d) return NULL;
    d->n = 1; /* Descriptor shall not exist if there is not at least one node  */
    /* Methods */
    d->insert_node = bk_tree_insert_node;
    d->add = bk_tree_add;
    d->fuzzy_search_ = bk_tree_fuzzy_search_;
    d->fuzzy_search = bk_tree_fuzzy_search;
    d->free = bk_tree_free;
    d->print = bk_tree_print;
    d->fprint = bk_tree_fprint;
    d->fprint_ = bk_tree_fprint_;
    d->to_dot_ = bk_tree_to_dot_;
    d->to_dot = bk_tree_to_dot;
    d->type_descriptor = NULL;
    return d;
}

BKTreeNode * bk_tree_builder(const void * data, BKtreeDescriptor *d){
    BKTreeNode *node;
    if(!data) return NULL;
    if(!d) return NULL;
    node = (BKTreeNode *) malloc(sizeof(BKTreeNode));
    if(!node) return NULL;
    node->child = node->siblings = NULL;
    node->value = 0;
    node->data = d->type_descriptor->copy(data);
    if(!node->data) return NULL;
    node->d = d;
    return node;
}

BKTree new_bk_tree(const char * word){
    BKtreeDescriptor * d;
    if(!word) return NULL;
    d = bk_tree_descriptor();
    if(!d) return NULL;
    d->type_descriptor = new_type_descriptor(str_m);
    if(!d->type_descriptor) return NULL;
    return bk_tree_builder(word, d);
}

int bk_tree_insert_node(BKTree * root, BKTreeNode * bk_tree_node) {
    int d;
    BKTree *tmp;
    /* Empty tree */
    if (!*root) {
        *root = bk_tree_node;
        (*root)->d->n++;
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
        return (*root)->d->insert_node(&(*root)->child, bk_tree_node);
    }
    /* Look up on siblings / (siblings as ordered list) */
    tmp = &(*root)->siblings;

    /* No siblings */
    if (!*tmp) {
        *tmp = bk_tree_node;
        (*root)->d->n++;
        return 1;

    }else if ((*tmp)->value > bk_tree_node->value){
        bk_tree_node->siblings = (*tmp);
        (*tmp) = bk_tree_node;
        (*root)->d->n++;
        return 1;

    }

    return (*tmp)->d->insert_node(&(*tmp), bk_tree_node);
}

int bk_tree_add(BKTree * root, const char * word){
    BKTreeNode * new_node;
    if(!*root) return 0;
    if(!word)
        return 0;
    if(!(new_node = bk_tree_builder(word, (*root)->d)))
        return 0;
    return (*root)->d->insert_node(root, new_node);
}

void bk_tree_fprint_(FILE *stream, const BKTree root, int t){
    int i;
    if(!root) return;
    for(i = 0; i < t; i++)
        printf("      ");
    fprintf(stream, "%s%d─> ",(root->siblings) ? "├─" : "└─", root->value);
    root->d->type_descriptor->print(root->data);
    fprintf(stream, "\n");
    root->d->fprint_(stream, root->child, t + 1);
    root->d->fprint_(stream, root->siblings, t);
}

void bk_tree_fprint(FILE *stream, const BKTree root){
    if(!root) return;
    root->d->type_descriptor->fprint(stream, root->data);
    fprintf(stream, "\n");
    root->d->fprint_(stream, root->child, 0);
    root->d->fprint_(stream, root->siblings, 0);
}

void bk_tree_print(const BKTree root){
    if(!root) return;
    root->d->fprint(stdout, root);
}

int bk_tree_fuzzy_search_(const BKTree *root, int *s, const char *word, List *r_suggestions){
    int d;
    BKTree tmp;
    if(!*root) return 0;
    d = mlcl_levenshtein(word, (*root)->data);

    if(d < *s){
        *s = d;
        r_suggestions->empty(r_suggestions);
    }

    /* Word exits in the tree */
    if(d == 0){
        r_suggestions->empty(r_suggestions);
        return 1;
    }

    if(d <= *s)
        r_suggestions->prepend(r_suggestions, (*root)->data);

    if((*root)->child){
        if(abs(d - (*root)->child->value) <= *s){
            (*root)->d->fuzzy_search_(&(*root)->child, s, word, r_suggestions);
        }

        if(!(*root)->child->siblings)
            return r_suggestions->is_empty(r_suggestions);
        tmp = (*root)->child->siblings;
        while(tmp){
            if(abs(d - tmp->value) <= *s){
                (*root)->d->fuzzy_search_(&tmp, s, word, r_suggestions);
            }
            tmp = tmp->siblings;
        }
    }
    return 0;
}

int bk_tree_fuzzy_search(const BKTree *root, const char *word, List *r_suggestions){
    int x;
    x = __INT_MAX__;
    if(!*root || !word) return 0;
    return (*root)->d->fuzzy_search_(root, &x, word, r_suggestions);
}


void bk_tree_free_descriptor(BKtreeDescriptor **d){
    if(!*d) return;
    if((*d)->type_descriptor)
        type_descriptor_free(&(*d)->type_descriptor);
    free(*d);
    *d = NULL;
}

void bk_tree_free(BKTree *root){
    if(!*root) return;

    (*root)->d->free(&(*root)->child);
    (*root)->d->free(&(*root)->siblings);

    if((*root)->data)
        (*root)->d->type_descriptor->free_data(&(*root)->data);

    /* The tree will decrease of 1 node. */
    (*root)->d->n--;
    /* After that, the tree may be empty. Thus, the descriptor could no longer exist. */
    if((*root)->d->n == 0)
        bk_tree_free_descriptor(&(*root)->d);

    free(*root);
    *root = NULL;
}

void bk_tree_to_dot_(const BKTree root, FILE *file){
    BKTree tmp;
    if(!root) return;

    fprintf(file, "  n%p [label=\"", (void *) &*root);
    root->d->type_descriptor->fprint(file, root->data);
    fprintf(file, "\"]\n");
    if(root->child){
        fprintf(file,
                "  n%p -> n%p [color=\"#2257ab\", label=\" %d \"]\n",
                (void *) &*root, (void *) root->child, root->child->value);
        root->d->to_dot_(root->child, file);

        if(!(tmp = root->child->siblings))
            return;

        while(tmp){
            fprintf(file, "  n%p [label=\"",(void *) &*tmp);
            root->d->type_descriptor->fprint(file, tmp->data);
            fprintf(file, "\"]\n");
            fprintf(file, "  n%p -> n%p [color=\"#2257ab\", label=\" %d \"]\n", (void *) &*root, (void *) tmp, tmp->value);
            root->d->to_dot_(tmp, file);
            tmp = tmp->siblings;
        }
    }
}

void bk_tree_to_dot(const BKTree root, const char *path){
    FILE *file = fopen(path, "w");
    fprintf(file, "digraph arbre {\n"
                  "\n"
                  "   \n"
                  "  \n\n");
    root->d->to_dot_(root, file);
    fprintf(file, "\n}");
}
