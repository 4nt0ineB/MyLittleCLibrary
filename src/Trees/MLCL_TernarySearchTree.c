/*
 *   This file is part of the MLCL Library.
 *   Antoine Bastos 2022
 *
 *   This Library is free software under the terms of
 *   the MIT license.
 */

#include "../../include/Trees/MLCL_TernarySearchTree.h"
#include "../../include/MLCL_basic_types.h"

TernarySearchTreeDescriptor * ternary_search_tree_descriptor(){
    TernarySearchTreeDescriptor *d;
    d = (TernarySearchTreeDescriptor *) malloc(sizeof(TernarySearchTreeDescriptor));
    if(!d) return NULL;
    d->n = 1; /* Descriptor shall not exist if there is not at least one node  */
    /* Methods */
    d->insert_branch = ternary_search_tree_insert_branch;
    d->add = ternary_search_tree_add;
    /*d->search = ternary_search_tree_search;
    d->remove = ternary_search_tree_remove;*/
    d->print = ternary_search_tree_print;
    d->fprint_ = ternary_search_tree_fprint_;
    d->fprint = ternary_search_tree_fprint;
    d->free = ternary_search_tree_free;
    /* */
    d->type_descriptor = NULL;
    return d;
}

TernarySearchNode * ternary_search_tree_builder(const void * data, TernarySearchTreeDescriptor *d){
    TernarySearchNode *node;
    if(!data) return NULL;
    if(!d) return NULL;
    node = (TernarySearchNode *) malloc(sizeof(TernarySearchNode));
    if(!node) return NULL;
    node->left = node->child = node->right = NULL;
    node->data = d->type_descriptor->copy(data);
    if(!node->data) return NULL;
    node->d = d;
    return node;
}

TernarySearchTree new_ternary_search_tree(const char * word){
    TernarySearchTreeDescriptor * tstd;
    TernarySearchTree tst;
    if(!word) return NULL;
    tstd = ternary_search_tree_descriptor();
    if(!tstd) return NULL;
    tstd->type_descriptor = new_type_descriptor(char_m);
    if(!tstd->type_descriptor) return NULL;
    tst = ternary_search_tree_builder(word, tstd);
    if(!tst) return NULL;
    ternary_search_tree_insert_branch(&tst, &tst->child, word + 1);
    return tst;
}

/**
 * Insert a branch of letters
 * (Straight line of child carrying the letters left of the word)
 * @param A
 */
int ternary_search_tree_insert_branch(TernarySearchTree * ancestor, TernarySearchTree * t, const char * word){
    if(!ancestor) return 0;
    if(!word) return 0;
    if((*t = ternary_search_tree_builder(word, (*ancestor)->d))){
        (*t)->d->n++;
        if(*word) {
            return (*t)->d->insert_branch(ancestor, &(*t)->child, word + 1);
        }
        return 1;
    }
    return 0;
}

int ternary_search_tree_add(TernarySearchTree *t, const char * word){
    char c;
    if(!*t) return 0;
    else{
        c = *word;
        if((*t)->d->type_descriptor->lt(&c, (*t)->data) == 1){
            if(!(*t)->left){ /* Add branch while descriptor is accessible */
                return (*t)->d->insert_branch(t, &(*t)->left, word);
            }
            return (*t)->d->add(&(*t)->left, word);

        }else if((*t)->d->type_descriptor->gt(&c, (*t)->data) == 1){
            if(!(*t)->right){ /* Add branch while descriptor is accessible */
                return (*t)->d->insert_branch(t, &(*t)->right, word);
            }
            return (*t)->d->add(&(*t)->right, word);

        }else{
            if(*word == MLCL_TST_STOP_CHAR)
                return 1;
            if(!(*t)->child){ /* Add branch while descriptor is accessible */
                return (*t)->d->insert_branch(t, &(*t)->child, ++word);
            }
            return (*t)->d->add(&(*t)->child, ++word);
        }
    }
}

/*void ternary_search_tree_remove(TernarySearchTree *t, const char * word);

int ternary_search_tree_search(const TernarySearchTree t, const char *word);*/

void ternary_search_tree_print(const TernarySearchTree t){
    if(!t) return;
    t->d->fprint(stdout, t);
}

void ternary_search_tree_fprint_(FILE *stream, const TernarySearchTree t, List *l, int i){
    if(t){

        t->d->fprint_(stream, t->left, l, i);

        while(!l->is_empty(l) && i < l->length(l))
            free(l->pop(l));

        l->append(l, t->data);
        if(* (char *) t->data == MLCL_TST_STOP_CHAR){
            l->fprint(stream, l);
            fprintf(stream, "\n");
        }
        else
            t->d->fprint_(stream, t->child, l, i + 1);
        t->d->fprint_(stream, t->right, l, i);
    }
}

void ternary_search_tree_fprint(FILE *stream, const TernarySearchTree t){
    List *l;
    if(!t || !stream) return;
    l = (List *) new_list(ARRAY_LIST, char_m);
    if(!l) return;
    t->d->fprint_(stream, t, l, 0);
    l->free(&l);
}

void ternary_search_tree_free_descriptor(TernarySearchTreeDescriptor **tstd){
    if(!*tstd) return;
    if((*tstd)->type_descriptor)
        type_descriptor_free(&(*tstd)->type_descriptor);
    free(*tstd);
    *tstd = NULL;
}

void ternary_search_tree_free(TernarySearchTree *t){
    if(!*t) return;

    (*t)->d->free(&(*t)->left);
    (*t)->d->free(&(*t)->child);
    (*t)->d->free(&(*t)->right);

    if((*t)->data)
        (*t)->d->type_descriptor->free_data(&(*t)->data);

    /* The tree will decrease of 1 node. */
    (*t)->d->n--;
    /* After that, the tree may be empty. Thus, the descriptor could no longer exist. */
    if((*t)->d->n == 0)
        ternary_search_tree_free_descriptor(&(*t)->d);


    free(*t);
    *t = NULL;
}
