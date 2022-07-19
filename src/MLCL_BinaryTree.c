/*
 *   This file is part of the MLCL Library.
 *   Antoine Bastos 2022
 *
 *   This Library is free software under the terms of
 *   the MIT license.
 */

#include "../include/MLCL_BinaryTree.h"
#include <assert.h>

BinaryTreeDescriptor * binary_tree_descriptor(){
    BinaryTreeDescriptor * bt_descriptor;
    bt_descriptor = (BinaryTreeDescriptor *) malloc(sizeof(BinaryTreeDescriptor));
    if(!bt_descriptor) return NULL;
    /* functions affectation */
    bt_descriptor->height = binary_tree_height;
    bt_descriptor->nb_nodes = binary_tree_nb_nodes;
    bt_descriptor->nb_leaves = binary_tree_nb_leaves;
    bt_descriptor->nb_internal_nodes = binary_tree_nb_internal_nodes;
    bt_descriptor->nb_two_children = binary_tree_nb_two_children;
    bt_descriptor->is_bt = binary_tree_is_bt;
    bt_descriptor->is_bst = binary_tree_is_bst;
    bt_descriptor->node_print = binary_tree_node_print;
    bt_descriptor->node_fprint = binary_tree_node_fprint;
    bt_descriptor->fprint_preorder = binary_tree_fprint_preorder;
    bt_descriptor->fprint_inorder = binary_tree_fprint_inorder;
    bt_descriptor->fprint_postorder = binary_tree_fprint_postorder;
    return bt_descriptor;
}

BinaryNode * binary_tree_builder(const void * data, BinaryTreeDescriptor * descriptor){
    BinaryNode * node;
    node = (BinaryNode *) calloc(1, sizeof(BinaryNode));
    assert(descriptor);
    if(!node) return NULL;
    if(!(node->data = descriptor->type_descriptor->copy(data))
       && descriptor->type_descriptor->data_size)
        return NULL;
    node->d = descriptor;
    node->left = node->right = NULL;
    return node;
}

BinaryTree new_binary_tree(const void * data, void (*type_manifest) (TypeDescriptor *)){
    BinaryTreeDescriptor * btd;
    if(!type_manifest) return NULL;
    if(!(btd = binary_tree_descriptor())) return NULL;
    btd->type_descriptor = new_type_descriptor(type_manifest);
    return binary_tree_builder(data, btd);
}

int binary_tree_height(BinaryTree t){
    int hln, hrn;
    if (!t) return -1;
    if (!t->left && !t->right) return 0;
    hln = t->d->height(t->left);
    hrn = t->d->height(t->right);
    return 1 + ((hln > hrn) ? hln : hrn);
}

int binary_tree_nb_nodes(BinaryTree t){
    if (!t) return 0;
    return 1 + t->d->nb_nodes(t->left) + t->d->nb_nodes(t->right);
}

int binary_tree_nb_leaves(BinaryTree t){
    if (!t) return 0;
    if (!t->left && !t->right) return 1;
    return t->d->nb_leaves(t->left) + t->d->nb_leaves(t->right);
}

int binary_tree_nb_internal_nodes(BinaryTree t){
    if (!t) return 0;
    if (!t->left && !t->right) return 0;
    return 1 + t->d->nb_internal_nodes(t->left) + t->d->nb_internal_nodes(t->right);
}

int binary_tree_nb_two_children(BinaryTree t){
    int x = 0;
    if (!t) return 0;
    if (t->left && t->right) x = 1;
    return x + t->d->nb_two_children(t->left) + t->d->nb_two_children(t->right);
}

int binary_tree_is_bt(BinaryTree t){
    if (!t) return 1;
    if ((!t->left && t->right) || (t->left && !t->right)) return 0;
    return t->d->is_bst(t->left) && t->d->is_bst(t->right);
}

int binary_tree_is_bst(BinaryTree t){
    /* @Todo: is bst */
    return 0;
}

int binary_tree_insert(BinaryTree * t, const void * data){
    /* @todo */
    return 0;
}

int binary_tee_remove(BinaryTree * t, const void * data){
    /* @todo */
    return 0;
}

int binary_tee_search(BinaryTree * t, const void * data){
    /* @todo */
    return 0;
}

void binary_tree_node_print (BinaryNode * n){
    if(n) n->d->node_fprint(stdout, n);
}

void binary_tree_node_fprint (FILE * stream, BinaryNode * n){
    if(n) n->d->type_descriptor->fprint(stream, n->data);
}

void binary_tree_fprint_preorder(FILE * stream, BinaryTree t){
    if(!t) return;
    t->d->node_fprint(stream, t);
    t->d->fprint_preorder(stream, t->left);
    t->d->fprint_preorder(stream, t->right);
}

void binary_tree_fprint_inorder(FILE * stream, BinaryTree t){
    if(!t) return;
    t->d->fprint_inorder(stream, t->left);
    t->d->node_fprint(stream, t);
    t->d->fprint_inorder(stream, t->right);
}

void binary_tree_fprint_postorder(FILE * stream, BinaryTree t){
    if(!t) return;
    t->d->fprint_postorder(stream, t->left);
    t->d->fprint_postorder(stream, t->right);
    t->d->node_fprint(stream, t);
}