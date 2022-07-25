/*
 *   This file is part of the MLCL Library.
 *   Antoine Bastos 2022
 *
 *   This Library is free software under the terms of
 *   the MIT license.
 */

#include "../../include/Tree/MLCL_AVLTree.h"
#include <assert.h>

AVLTreeDescriptor  * avl_tree_descriptor(){
    AVLTreeDescriptor * avl_descriptor;
    avl_descriptor = (AVLTreeDescriptor *) malloc(sizeof(AVLTreeDescriptor));
    if(!avl_descriptor) return NULL;
    /* functions affectation */
    avl_descriptor->height = avl_tree_height;
    avl_descriptor->nb_nodes = avl_tree_nb_nodes;
    avl_descriptor->nb_leaves = avl_tree_nb_leaves;
    avl_descriptor->nb_internal_nodes = avl_tree_nb_internal_nodes;
    avl_descriptor->nb_two_children = avl_tree_nb_two_children;
    avl_descriptor->is_perfect_bt = avl_tree_is_perfect_bt;
    avl_descriptor->is_bst = avl_tree_is_bst;
    avl_descriptor->add = avl_tree_add;
    avl_descriptor->search = avl_tree_search;
    avl_descriptor->min = avl_tree_min;
    avl_descriptor->max = avl_tree_max;
    avl_descriptor->extract_min = avl_tree_extract_min;
    avl_descriptor->extract_max = avl_tree_extract_max;
    avl_descriptor->remove = avl_tree_remove;
    avl_descriptor->node_print = avl_tree_node_print;
    avl_descriptor->node_fprint = avl_tree_node_fprint;
    avl_descriptor->fprint_preorder = avl_tree_fprint_preorder;
    avl_descriptor->fprint_inorder = avl_tree_fprint_inorder;
    avl_descriptor->fprint_postorder = avl_tree_fprint_postorder;
    avl_descriptor->to_dot = avl_tree_to_dot;
    avl_descriptor->free = avl_tree_free;
    avl_descriptor->n = 1; /*<! For the descriptor to exists at least one node exists */
    return avl_descriptor;
}



AVLTreeNode * avl_tree_builder(const void * data, AVLTreeDescriptor * descriptor){
    AVLTreeNode * node;
    node = (AVLTreeNode *) calloc(1, sizeof(AVLTreeNode));
    assert(descriptor);
    if(!node) return NULL;
    if(!(node->data = descriptor->type_descriptor->copy(data))
       && descriptor->type_descriptor->data_size)
        return NULL;
    node->d = descriptor;
    node->balance = 0;
    node->left = node->right = NULL;
    return node;
}


AVLTree new_avl_tree(const void * data, void (*type_manifest) (TypeDescriptor *)){
    AVLTreeDescriptor * btd;
    if(!type_manifest) return NULL;
    if(!(btd = avl_tree_descriptor())) return NULL;
    btd->type_descriptor = new_type_descriptor(type_manifest);
    return avl_tree_builder(data, btd);
}


static void avl_tree_l_rotation(AVLTree *r){
    AVLTree newr;
    int i, j;
    if(!*r || !(*r)->right)
        return;
    /* Update subtrees */
    newr = (*r)->right;
    (*r)->right = newr->left;
    newr->left = *r;

    /* Updates balances */
    i = (*r)->balance;
    j = newr->balance;

    /* Update root balance */
    if(j >= 0)
        (*r)->balance = i - j - 1;
    else
        (*r)->balance = i - 1;

    /* Update new root balance */
    if((*r)->balance <= 0)
        newr->balance = j + (*r)->balance - 1;
    else
        newr->balance = j - 1;

    /* switch roots */
    *r = newr;
}

static void avl_tree_r_rotation(AVLTree *r){
    AVLTree newr;
    int i, j;
    if(!*r || !(*r)->left)
        return;

    /* Update subtrees */
    newr = (*r)->left;
    (*r)->left = newr->right;
    newr->right = *r;

    /* Update balances */
    i = (*r)->balance;
    j = newr->balance;

    /* Update root balance */
    if(j > 0)
        (*r)->balance = i + 1;
    else
        (*r)->balance = i - j + 1;

    /* Update new root balance */
    if((*r)->balance <= 0)
        newr->balance = j + 1;
    else
        newr->balance = j + (*r)->balance + 1;

    /* switch roots */
    *r = newr;
}

static void avl_tree_lr_rotation(AVLTree *r){
    avl_tree_l_rotation(&(*r)->left);
    avl_tree_r_rotation(r);
}

static void avl_tree_rl_rotation(AVLTree *r){
    avl_tree_r_rotation(&(*r)->right);
    avl_tree_l_rotation(r);
}

static void avl_tree_balance(AVLTree *r){
    if((*r)->balance == 2){
        if((*r)->right->balance >= 0)
            avl_tree_l_rotation(r);
        else
            avl_tree_rl_rotation(r);

    }else if((*r)->balance == -2){
        if((*r)->left->balance <= 0)
            avl_tree_r_rotation(r);
        else
            avl_tree_lr_rotation(r);
    }
}

int avl_tree_add(AVLTree *r, const void * data){
    int var;
    if(!*r) return 0;
    var = 0;
    /* no duplicates */
    if((*r)->d->type_descriptor->eq((*r)->data, data))
        return 0;
    if((*r)->d->type_descriptor->le(data, (*r)->data)){
        if(!(*r)->left){
            if(((*r)->left = avl_tree_builder(data, (*r)->d))){
                var = -1;
                (*r)->d->n++;
            }
        }else
            var = -(*r)->d->add(&(*r)->left, data);
    }else{
        if(!(*r)->right){
            if(((*r)->right = avl_tree_builder(data, (*r)->d))){
                var = 1;
                (*r)->d->n++;
            }
        }else
            var = (*r)->d->add(&(*r)->right, data);
    }
    if(var != 0){
        (*r)->balance += var;
        avl_tree_balance(r);
        if((*r)->balance == 0)
            return 0;
        else
            return 1;
    } else
        return 0;
}

int avl_tree_extract_min(AVLTree *r, void * rdata){
    if (!*r)
        return 0;
    if (!(*r)->left) {
        AVLTree tmp = *r;
        rdata = tmp->data;
        *r = (*r)->right;
        tmp->left = tmp->right = NULL;
        tmp->d->n--;
        /* After that, the tree may be empty. Thus, the descriptor could no longer exist. */
        if(tmp->d->n == 0){
            avl_tree_descriptor_free(&tmp->d);
            *r = NULL;
        }
        free(tmp);
        return 1;
    }
    return (*r)->d->extract_min(&(*r)->left, rdata);
}

int avl_tree_extract_max(AVLTree *r, void * rdata){
    if (!*r)
        return 0;
    if (!(*r)->right) {
        AVLTree tmp = *r;
        rdata = tmp->data;
        *r = (*r)->left;
        tmp->left = tmp->right = NULL;
        tmp->d->n--;
        /* After that, the tree may be empty. Thus, the descriptor could no longer exist. */
        if(tmp->d->n == 0){
            avl_tree_descriptor_free(&tmp->d);
            *r = NULL;
        }
        free(tmp);
        return 1;
    }
    return (*r)->d->extract_max(&(*r)->right, rdata);
}

int avl_tree_remove(AVLTree *r, const void * data){
    /* return 1 if height decreased */
    AVLTree tmp;
    int maj;

    if(!*r)
        return 0;

    if((*r)->d->type_descriptor->lt(data, (*r)->data))
        maj = (*r)->d->remove(&(*r)->left, data);

    else if((*r)->d->type_descriptor->gt(data, (*r)->data))
        maj = -(*r)->d->remove(&(*r)->right, data);

    else{
        /* On a une égalité. On supprime le noeud.*/

        if(!(*r)->left && !(*r)->right){
            /* Est une feuille */
            (*r)->d->free(r);
            return 1;

        }else{
            if(!(*r)->left){
                /* Ne possède qu'un fils droit */
                tmp = *r;
                *r = (*r)->right;
                tmp->right = tmp->left = NULL;
                (*r)->d->free(r);
                return 1;

            } else if(!(*r)->right){
                /* Ne possède qu'un fils gauche */
                tmp = *r;
                *r = (*r)->left;
                tmp->right = tmp->left = NULL;
                (*r)->d->free(r);
                return 1;

            }else{
                /* Possède deux fils */
                if((*r)->balance <= 0) {
                    if ((maj = (*r)->d->extract_max(&(*r)->left, &(*r)->data)))
                        (*r)->d->n++;
                }else{
                    /* Négatif, car l'extraction dans fg fait pencher vers fd */
                    if((maj = -(*r)->d->extract_min(&(*r)->right, &(*r)->data)))
                        (*r)->d->n++;
                }
            }
        }
    }

    /* Si on a réalisé une modif */
    if(maj != 0){

        /* On met à jour la balance de la racine */
        (*r)->balance = (*r)->balance + maj;

        /* Si la balance devient 1 ou -1, rien à faire */
        if((*r)->balance == 1 || (*r)->balance == -1)
            return 0;

        /* si 0, alors n'était pas équilibré avant suppression  */
        if((*r)->balance == 0)
            return 1;

        if((*r)->balance == -2){
            if((*r)->left->balance == 0)
                maj = 0;
            else
                maj = 1;
        }

        if((*r)->balance == 2){
            if((*r)->right->balance == 0)
                maj = 0;
            else
                maj = 1;
        }
        avl_tree_balance(r);
        return maj;
    }
    return 0;
}

int avl_tree_height(AVLTree t){
    int hln, hrn;
    if (!t) return -1;
    if (!t->left && !t->right) return 0;
    hln = t->d->height(t->left);
    hrn = t->d->height(t->right);
    return 1 + ((hln > hrn) ? hln : hrn);
}

int avl_tree_nb_nodes(AVLTree t){
    if (!t) return 0;
    return 1 + t->d->nb_nodes(t->left) + t->d->nb_nodes(t->right);
}

int avl_tree_nb_leaves(AVLTree t){
    if (!t) return 0;
    if (!t->left && !t->right) return 1;
    return t->d->nb_leaves(t->left) + t->d->nb_leaves(t->right);
}

int avl_tree_nb_internal_nodes(AVLTree t){
    if (!t) return 0;
    if (!t->left && !t->right) return 0;
    return 1 + t->d->nb_internal_nodes(t->left) + t->d->nb_internal_nodes(t->right);
}

int avl_tree_nb_two_children(AVLTree t){
    int x = 0;
    if (!t) return 0;
    if (t->left && t->right) x = 1;
    return x + t->d->nb_two_children(t->left) + t->d->nb_two_children(t->right);
}

int avl_tree_is_perfect_bt(AVLTree t){
    if (!t) return 1;
    if ((!t->left && t->right) || (t->left && !t->right)) return 0;
    return t->d->is_perfect_bt(t->left) && t->d->is_perfect_bt(t->right);
}

int avl_tree_is_bst(AVLTree t){
    AVLTree tmp, tmp2;
    if (!t)
        return 1;
    tmp = t->d->max(t->left);
    if (tmp && t->d->type_descriptor->eq(tmp->data, t->data))
        return 0;
    tmp2 = t->d->min(t->right);
    if (tmp2 && t->d->type_descriptor->eq(tmp2->data, t->data))
        return 0;
    return t->d->is_bst(t->left) && t->d->is_bst(t->right);
}

AVLTree avl_tree_min(AVLTree t) {
    if (!t)
        return NULL;
    if (!t->left)
        return t;
    return t->d->min(t->left);
}

AVLTree avl_tree_max(AVLTree t) {
    if (!t)
        return NULL;
    if (!t->right)
        return t;
    return t->d->max(t->right);
}

AVLTree avl_tree_search(AVLTree * t, const void * data){
    if (!*t)
        return NULL;
    if ((*t)->d->type_descriptor->gt((*t)->data, data))
        return (*t)->d->search(&(*t)->left, data);
    if ((*t)->d->type_descriptor->lt((*t)->data, data))
        return (*t)->d->search(&(*t)->right, data);
    return *t;
}

void avl_tree_node_print (AVLTreeNode * n){
    if(n) n->d->node_fprint(stdout, n);
}

void avl_tree_node_fprint (FILE * stream, AVLTreeNode * n){
    if(n) n->d->type_descriptor->fprint(stream, n->data);
}

void avl_tree_fprint_preorder(FILE * stream, AVLTree t){
    if(!t) return;
    t->d->node_fprint(stream, t);
    t->d->fprint_preorder(stream, t->left);
    t->d->fprint_preorder(stream, t->right);
}

void avl_tree_fprint_inorder(FILE * stream, AVLTree t){
    if(!t) return;
    t->d->fprint_inorder(stream, t->left);
    t->d->node_fprint(stream, t);
    t->d->fprint_inorder(stream, t->right);
}

void avl_tree_fprint_postorder(FILE * stream, AVLTree t){
    if(!t) return;
    t->d->fprint_postorder(stream, t->left);
    t->d->fprint_postorder(stream, t->right);
    t->d->node_fprint(stream, t);
}

static void _avl_tree_to_dot(AVLTree avl, FILE * file){
    if(!avl) return;
    fprintf(file, "  n%p [label=\"<gauche>|{%d  | ", (void *) &*avl, avl->balance);
    avl->d->node_fprint(file, avl);
    fprintf(file, "}|<droit>\"]\n");
    if(avl->left){
        fprintf(file, "  n%p:gauche -> n%p:n [color=\"#ab2222\"]\n", (void *) &*avl, (void *) avl->left);
        _avl_tree_to_dot(avl->left, file);
    }
    if(avl->right){
        fprintf(file, "  n%p:droit -> n%p:n [color=\"#2257ab\"]\n", (void *) &*avl, (void *) avl->right);
        _avl_tree_to_dot(avl->right, file);
    }
}

void avl_tree_to_dot(AVLTree avl, const char * dest_path){
    FILE * file;
    if(!avl) return;
    file = fopen(dest_path, "w");
    if(!file)
        printf("File can't be opened\n");
    fprintf(file, "digraph arbre {\n"
                  "  node [shape=record , height=.1 ]\n"
                  "  edge [tailclip=false , arrowtail = dot , dir=both];\n");
    _avl_tree_to_dot(avl, file);
    fprintf(file, "}\n");
    fclose(file);
}

void avl_tree_descriptor_free(AVLTreeDescriptor ** bstd) {
    if (!*bstd) return;
    type_descriptor_free(&(*bstd)->type_descriptor);
    free(*bstd);
    *bstd = NULL;
}

void avl_tree_free(AVLTree * t){
    if(!*t) return;
    (*t)->d->free(&(*t)->left);
    (*t)->d->free(&(*t)->right);
    (*t)->d->type_descriptor->free_data(&(*t)->data);
    /* The tree will decrease of 1 node. */
    (*t)->d->n--;
    /* After that, the tree may be empty. Thus, the descriptor could no longer exist. */
    if((*t)->d->n == 0)
        avl_tree_descriptor_free(&(*t)->d);
    free(*t);
    *t = NULL;
}