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
    d->search = ternary_search_tree_search;
    d->remove = ternary_search_tree_remove;
    d->print = ternary_search_tree_print;
    d->fprint_ = ternary_search_tree_fprint_;
    d->fprint = ternary_search_tree_fprint;
    d->free = ternary_search_tree_free;
    d->to_dot_ = ternary_tree_to_dot_;
    d->to_dot = ternary_tree_to_dot;
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

void ternary_search_tree_remove(TernarySearchTree *t, const char * word){
    if(!*t) return;
    if((*t)->d->type_descriptor->eq(word, (*t)->data)){
        if(*word == MLCL_TST_STOP_CHAR){
            TernarySearchTree tmp = (*t);
            *t = (*t)->right;
            tmp->right = NULL;
            tmp->d->free(&tmp);
            return;
        }
        (*t)->d->remove(&(*t)->child, word + 1);
        if(!(*t)->left && !(*t)->right){
            (*t)->child = NULL;
            (*t)->d->free(&(*t));
        }

    } else if((*t)->d->type_descriptor->gt(word, (*t)->data)){
        (*t)->d->remove(&(*t)->right, word);

    } else
        (*t)->d->remove(&(*t)->left, word);
}

int ternary_search_tree_search(const TernarySearchTree t, const char *word){
    if(!t) return 0;
    if(t->d->type_descriptor->eq(word, t->data)){
        if(*word == MLCL_TST_STOP_CHAR)
            return 1;
        return t->d->search(t->child, word + 1);
    }
    if(t->d->type_descriptor->gt(word, t->data))
        return t->d->search(t->right, word);
    return t->d->search(t->left, word);
}

void ternary_search_tree_print(const TernarySearchTree t){
    if(!t) return;
    t->d->fprint(stdout, t);
}

void ternary_search_tree_fprint_(FILE *stream, const TernarySearchTree t, List *l, int i){
    if(t){
        t->d->fprint_(stream, t->left, l, i);

        /* Resize the list to only keep the prefix */
        while(!l->is_empty(l) && i < l->length(l))
            free(l->pop(l));

        if(* (char *) t->data == MLCL_TST_STOP_CHAR){
            l->fprint_join(stream, l, "");
            fprintf(stream, "\n");
        }else{
            /* Store the char in the list */
            l->append(l, t->data);
            t->d->fprint_(stream, t->child, l, i + 1);
        }
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

void ternary_tree_to_dot_(const TernarySearchTree t, FILE * stream){
    char c;
    if(!t) return;

    c = * (char *) t->data;
    /* \0 will be blank in dot */
    if(c == '\0') c = '0';

    fprintf(stream, "  n%p [label=\"%c\"]\n", (void *) &*t, c);
    if(t->left){
        fprintf(stream, "  n%p:w -> n%p:c [color=\"#ab2222\"]\n", (void *) &*t, (void *) t->left);
        t->d->to_dot_(t->left, stream);
    }
    if(t->child){
        fprintf(stream, "  n%p:s -> n%p:c  \n", (void *) &*t, (void *) t->child);
        t->d->to_dot_(t->child, stream);
    }
    if(t->right){
        fprintf(stream, "  n%p:e -> n%p:c [color=\"#2257ab\"]\n", (void *) &*t, (void *) t->right);
        t->d->to_dot_(t->right, stream);
    }
}

void ternary_tree_to_dot(const TernarySearchTree t, const char * path){
    FILE *file = fopen(path, "w");
    fprintf(file, "digraph arbre {\n"
                  "graph [ splines=true]\n"
                  "  node [shape=circle,height=.1]\n"
                  "  \n\n");
    t->d->to_dot_(t, file);
    fprintf(file, "\n}");
    fclose(file);
}