/*
 *   This file is part of the MLCL Library
 *   Copyright 2022 Antoine Bastos
 *   SPDX-License-Identifier: Apache-2.0
 */

#include "../../../include/data-structures/Trees/MLCL_TernarySearchTree.h"
#include "../../../include/core/MLCL_basic_types.h"

/***************************************************
 * TernarySearchTreeNode
 ***************************************************/

TernarySearchTreeNode * new_ternary_search_tree_node(void *data){
    TernarySearchTreeNode *node;
    if(!data) return NULL;
    node = (TernarySearchTreeNode *) malloc(sizeof(TernarySearchTreeNode));
    if(!node) return NULL;
    node->data = data;
    node->left = node->child = node->right = NULL;
    return node;
}
void ternary_search_tree_node_free(TernarySearchTreeNode **self, void (data_free) (void *)){
    if(!*self) return;
    if(data_free)
        data_free((*self)->data);
    free(*self);
    *self = NULL;
}


/***************************************************
 * TernarySearchTree
 ***************************************************/

TernarySearchTree * new_ternary_search_tree(){
    TernarySearchTree *tree;
    tree = (TernarySearchTree *) malloc(sizeof(TernarySearchTree));
    if(!tree) return NULL;
    tree->td = new_type_descriptor(char_m);
    if(!tree->td){
        ternary_search_tree_free(&tree);
        return NULL;
    }
    tree->root = NULL;
    tree->n = 0;
    return tree;
}

/**
 * Insert a branch of letters
 * (Straight line of child carrying the letters left of the word)
 * @param A
 */
int ternary_search_tree_insert_branch_(TernarySearchTreeNode **root, char *word){
    if(!word) return 0;
    *root = new_ternary_search_tree_node(new_char(*word));
    if(*root){
        if(*word)
            return 1 + ternary_search_tree_insert_branch_(&(*root)->child, word + 1);
        return 1;
    }
    return 0;
}

int ternary_search_tree_add_(TernarySearchTreeNode **root, char *word, int (*cmp) (const void *, const void *)){
    char c;
    if(!*root) {
        return ternary_search_tree_insert_branch_(root, word);
    }
    else{
        c = *word;
        if(cmp(&c, (*root)->data) < 0){
            return ternary_search_tree_add_(&(*root)->left, word, cmp);

        }else if(cmp(&c, (*root)->data) > 0){
            return ternary_search_tree_add_(&(*root)->right, word, cmp);

        }else{
            if(*word == MLCL_TST_STOP_CHAR)
                return 1;
            return ternary_search_tree_add_(&(*root)->child, ++word, cmp);
        }
    }
}

int ternary_search_tree_add(TernarySearchTree *self, char *word){
    int i;
    if(!self) return 0;
    i = ternary_search_tree_add_(&self->root, word, self->td->cmp);
    self->n += i;
    return i;
}


int ternary_search_tree_remove_(TernarySearchTreeNode **root, char *word, int (*cmp) (const void *, const void *), void (*data_free) (void *)){
    if(!*root) return 0;
    if(cmp(word, (*root)->data) == 0){
        int i;
        if(*word == MLCL_TST_STOP_CHAR){
            TernarySearchTreeNode *tmp = (*root);
            *root = (*root)->right;
            tmp->right = NULL;
            ternary_search_tree_node_free(&tmp, data_free);
            return 1;
        }
        i = ternary_search_tree_remove_(&(*root)->child, word + 1, cmp, data_free);
        if(!(*root)->left && !(*root)->right){
            (*root)->child = NULL;
            ternary_search_tree_node_free(root, data_free);
            return 1 + i;
        }

    } else if(cmp(word, (*root)->data) > 0)
        return ternary_search_tree_remove_(&(*root)->right, word, cmp, data_free);
    return ternary_search_tree_remove_(&(*root)->left, word, cmp, data_free);
}

int ternary_search_tree_remove(TernarySearchTree *self, char *word){
    int i;
    if(!self) return 0;
    i = ternary_search_tree_remove_(&self->root, word, self->td->cmp, self->td->data_free);
    self->n -= i;
    return i;
}

int ternary_search_tree_search_(const TernarySearchTreeNode *root, const char *word, int (cmp) (const void *, const void *)){
    if(!root) return 0;
    if(cmp(word, root->data) == 0){
        if(*word == MLCL_TST_STOP_CHAR)
            return 1;
        return ternary_search_tree_search_(root->child, word + 1, cmp);
    }
    if(cmp(word, root->data) > 0)
        return ternary_search_tree_search_(root->right, word, cmp);
    return ternary_search_tree_search_(root->left, word, cmp);
}

int ternary_search_tree_search(const TernarySearchTree *self, const char *word){
    if(!self) return 0;
    return ternary_search_tree_search_(self->root, word, self->td->cmp);
}

void ternary_search_tree_fprint_(const TernarySearchTreeNode *root, FILE *stream, List *l, int i){
    if(root){
        ternary_search_tree_fprint_(root->left, stream, l, i);

        /* Resize the list to only keep the prefix */
        while(list_length(l) && i < list_length(l))
            free(list_pop(l));

        if(* (char *) root->data == MLCL_TST_STOP_CHAR){
            list_fprint_join(l, stream, "");
            fprintf(stream, "\n");
        }else{
            /* Store the char in the list */
            list_append(l, root->data);
            ternary_search_tree_fprint_(root->child, stream, l, i + 1);
        }
        ternary_search_tree_fprint_(root->right, stream, l, i);
    }
}

void ternary_search_tree_fprint(const TernarySearchTree *self, FILE *stream){
    List *l;
    if(!self || !stream) return;
    l = (List *) new_list(ARRAY_LIST, char_m);
    if(!l) return;
    ternary_search_tree_fprint_(self->root, stream, l, 0);
    list_free(&l);
}

void ternary_search_tree_print(const TernarySearchTree *self){
    if(!self) return;
    ternary_search_tree_fprint(self, stdout);
}

void ternary_search_tree_clear_(TernarySearchTreeNode **root, void (data_free) (void *)){
    if(!*root) return;
    ternary_search_tree_clear_(&(*root)->left, data_free);
    ternary_search_tree_clear_(&(*root)->child, data_free);
    ternary_search_tree_clear_(&(*root)->right, data_free);
    ternary_search_tree_node_free(root, data_free);
}

void ternary_search_tree_clear(TernarySearchTree *self, void (data_free) (void *)){
    if(!self) return;
    ternary_search_tree_clear_(&self->root, data_free);
    self->n = 0;
}

void ternary_search_tree_free(TernarySearchTree **self){
    if(!*self) return;
    ternary_search_tree_clear(*self, (*self)->td->data_free);
    type_descriptor_free(&(*self)->td);
    free(*self);
    *self = NULL;
}

void ternary_search_tree_to_dot_(const TernarySearchTreeNode *root, FILE * stream){
    char c;
    if(!root) return;

    c = * (char *) root->data;
    /* \0 will be blank in dot */
    if(c == '\0') c = '0';

    fprintf(stream, "  n%p [label=\"%c\"]\n", (void *) &*root, c);
    if(root->left){
        fprintf(stream, "  n%p:w -> n%p:c [color=\"#ab2222\"]\n", (void *) &*root, (void *) root->left);
        ternary_search_tree_to_dot_(root->left, stream);
    }
    if(root->child){
        fprintf(stream, "  n%p:s -> n%p:c  \n", (void *) &*root, (void *) root->child);
        ternary_search_tree_to_dot_(root->child, stream);
    }
    if(root->right){
        fprintf(stream, "  n%p:e -> n%p:c [color=\"#2257ab\"]\n", (void *) &*root, (void *) root->right);
        ternary_search_tree_to_dot_(root->right, stream);
    }
}

void ternary_search_tree_to_dot(const TernarySearchTree *self, const char *path){
    FILE *file = fopen(path, "w");
    fprintf(file, "digraph arbre {\n"
                  "graph [ splines=true]\n"
                  "  node [shape=circle,height=.1]\n"
                  "  \n\n");
    ternary_search_tree_to_dot_(self->root, file);
    fprintf(file, "\n}");
    fclose(file);
}