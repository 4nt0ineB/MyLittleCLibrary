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
    /*avl_descriptor->height = avl_tree_height;
    avl_descriptor->nb_nodes = avl_tree_nb_nodes;
    avl_descriptor->nb_leaves = avl_tree_nb_leaves;
    avl_descriptor->nb_internal_nodes = avl_tree_nb_internal_nodes;
    avl_descriptor->nb_two_children = avl_tree_nb_two_children;
    avl_descriptor->is_perfect_bt = avl_tree_is_perfect_bt;
    avl_descriptor->is_bst = avl_tree_is_bst;*/
    avl_descriptor->add = avl_tree_add;
    /*avl_descriptor->search = avlh_tree_search;
    avl_descriptor->min = avl_tree_min;
    avl_descriptor->max = avl_tree_max;*/
    avl_descriptor->extract_min = avl_tree_extract_min;
    avl_descriptor->extract_max = avl_tree_extract_max;
    avl_descriptor->remove = avl_tree_remove;
    /*avl_descriptor->node_print = avl_tree_node_print;
    avl_descriptor->node_fprint = avl_tree_node_fprint;
    avl_descriptor->fprint_preorder = avl_tree_fprint_preorder;
    avl_descriptor->fprint_inorder = avl_tree_fprint_inorder;
    avl_descriptor->fprint_postorder = avl_tree_fprint_postorder;*/
    avl_descriptor->to_dot = avl_tree_to_dot;
    /*avl_descriptor->free = avl_tree_free;*/
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

static void avl_tree_l_rotation(AVLTree *r){
    AVLTree newr;
    int i, j;
    if(!*r || !(*r)->right)
        return;
    /* Update subtrees */
    newr = (*r)->right;
    (*r)->right = newr->left,
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
    if(!*r || !(*r)->right)
        return;

    /* Update subtrees */
    newr = (*r)->left;
    (*r)->left = newr->right,
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
            if((*r = avl_tree_builder(data, (*r)->d)))
                var = -1;
        }else
            var = -(*r)->d->add(&(*r)->left, data);
    }else{
        if(!(*r)->left){
            if((*r = avl_tree_builder(data, (*r)->d)))
                var = 1;
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

    return 1;
}

int avl_tree_extract_max(AVLTree *r, void * rdata){

    return 1;
}

int avl_tree_remove(AVLTree *r, const void * data);

/*static void avl_tree_to_dot(AVLTree avl, FILE * file);*/

void avl_vers_dot(AVLTree avl, const char * path);
