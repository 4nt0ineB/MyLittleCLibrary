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

#include "../../include/Tree/MLCL_BinarySearchTree.h"
#include "../../include/MLCL_utils.h"
#include <assert.h>

BinarySearchTreeDescriptor * binary_search_tree_descriptor(){
    BinarySearchTreeDescriptor * bt_descriptor;
    bt_descriptor = (BinarySearchTreeDescriptor *) malloc(sizeof(BinarySearchTreeDescriptor));
    if(!bt_descriptor) return NULL;
    /* functions affectation */
    bt_descriptor->height = binary_search_tree_height;
    bt_descriptor->nb_nodes = binary_search_tree_nb_nodes;
    bt_descriptor->nb_leaves = binary_search_tree_nb_leaves;
    bt_descriptor->nb_internal_nodes = binary_search_tree_nb_internal_nodes;
    bt_descriptor->nb_two_children = binary_search_tree_nb_two_children;
    bt_descriptor->is_perfect_bt = binary_search_tree_is_perfect_bt;
    bt_descriptor->is_bst = binary_search_tree_is_bst;
    bt_descriptor->add = binary_search_tree_add;
    bt_descriptor->search = binary_search_tree_search;
    bt_descriptor->min = binary_search_tree_min;
    bt_descriptor->max = binary_search_tree_max;
    bt_descriptor->extract_min = binary_search_tree_extract_min;
    bt_descriptor->extract_max = binary_search_tree_extract_max;
    bt_descriptor->remove = binary_search_tree_remove;
    bt_descriptor->node_print = binary_search_tree_node_print;
    bt_descriptor->node_fprint = binary_search_tree_node_fprint;
    bt_descriptor->fprint_preorder = binary_search_tree_fprint_preorder;
    bt_descriptor->fprint_inorder = binary_search_tree_fprint_inorder;
    bt_descriptor->fprint_postorder = binary_search_tree_fprint_postorder;
    bt_descriptor->to_dot = binary_search_tree_to_dot;
    bt_descriptor->free = binary_search_tree_free;
    bt_descriptor->n = 1; /*<! For the descriptor to exists at least one node exists */
    return bt_descriptor;
}

BinarySearchTreeNode * binary_search_tree_builder(const void * data, BinarySearchTreeDescriptor * descriptor){
    BinarySearchTreeNode * node;
    node = (BinarySearchTreeNode *) calloc(1, sizeof(BinarySearchTreeNode));
    assert(descriptor);
    if(!node) return NULL;
    if(!(node->data = descriptor->type_descriptor->copy(data))
       && descriptor->type_descriptor->data_size)
        return NULL;
    node->d = descriptor;
    node->left = node->right = NULL;
    return node;
}

BinarySearchTree new_binary_search_tree(const void * data, void (*type_manifest) (TypeDescriptor *)){
    BinarySearchTreeDescriptor * btd;
    if(!type_manifest) return NULL;
    if(!(btd = binary_search_tree_descriptor())) return NULL;
    btd->type_descriptor = new_type_descriptor(type_manifest);
    return binary_search_tree_builder(data, btd);
}

int binary_search_tree_height(BinarySearchTree t){
    int hln, hrn;
    if (!t) return -1;
    if (!t->left && !t->right) return 0;
    hln = t->d->height(t->left);
    hrn = t->d->height(t->right);
    return 1 + ((hln > hrn) ? hln : hrn);
}

int binary_search_tree_nb_nodes(BinarySearchTree t){
    if (!t) return 0;
    /*return 1 + t->d->nb_nodes(t->left) + t->d->nb_nodes(t->right);*/
    return t->d->n;
}

int binary_search_tree_nb_leaves(BinarySearchTree t){
    if (!t) return 0;
    if (!t->left && !t->right) return 1;
    return t->d->nb_leaves(t->left) + t->d->nb_leaves(t->right);
}

int binary_search_tree_nb_internal_nodes(BinarySearchTree t){
    if (!t) return 0;
    if (!t->left && !t->right) return 0;
    return 1 + t->d->nb_internal_nodes(t->left) + t->d->nb_internal_nodes(t->right);
}

int binary_search_tree_nb_two_children(BinarySearchTree t){
    int x = 0;
    if (!t) return 0;
    if (t->left && t->right) x = 1;
    return x + t->d->nb_two_children(t->left) + t->d->nb_two_children(t->right);
}

int binary_search_tree_is_perfect_bt(BinarySearchTree t){
    if (!t) return 1;
    if ((!t->left && t->right) || (t->left && !t->right)) return 0;
    return t->d->is_perfect_bt(t->left) && t->d->is_perfect_bt(t->right);
}

BinarySearchTree binary_search_tree_min(BinarySearchTree t) {
    if (!t)
        return NULL;
    if (!t->left)
        return t;
    return t->d->min(t->left);
}

BinarySearchTree binary_search_tree_max(BinarySearchTree t) {
    if (!t)
        return NULL;
    if (!t->right)
        return t;
    return t->d->max(t->right);
}

int binary_search_tree_is_bst(BinarySearchTree t){
    BinarySearchTree tmp, tmp2;
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

int binary_search_tree_add(BinarySearchTree * t, const void * data){
    if(!t) return 0;
    /* less or equal -> left */
    if((*t)->d->type_descriptor->le(data, (*t)->data)) {
        if (!(*t)->left) {
            if(!((*t)->left = binary_search_tree_builder(data, (*t)->d)))
                return 0;
            (*t)->d->n++;
            return 1;
        }
        return (*t)->d->add(&(*t)->left, data);
    }
    /* greater -> right */
    if (!(*t)->right) {
        if(!((*t)->right = binary_search_tree_builder(data, (*t)->d)))
            return 0;
        (*t)->d->n++;
        return 1;
    }
    return (*t)->d->add(&(*t)->right, data);
}

void * binary_search_tree_extract_min(BinarySearchTree * t){
    if (!*t)
        return NULL;
    if (!(*t)->left) {
        BinarySearchTree tmp;
        void * data;
        tmp = *t;
        data = tmp->data;
        *t = tmp->right;
        tmp->d->n--;
        /* After that, the tree may be empty. Thus, the descriptor could no longer exist. */
        if(tmp->d->n == 0){
            binary_search_tree_descriptor_free(&tmp->d);
            *t = NULL;
        }
        free(tmp);
        return data;
    }
    return (*t)->d->extract_min(&(*t)->left);
}

void * binary_search_tree_extract_max(BinarySearchTree * t) {
    if (!*t)
        return NULL;
    if (!(*t)->right) {
        BinarySearchTree tmp;
        void * data;
        tmp = *t;
        data = tmp->data;
        *t = tmp->left;
        tmp->d->n--;
        /* After that, the tree may be empty. Thus, the descriptor could no longer exist. */
        if(tmp->d->n == 0){
            binary_search_tree_descriptor_free(&tmp->d);
            *t = NULL;
        }
        free(tmp);
        return data;
    }
    return (*t)->d->extract_min(&(*t)->left);
}

int binary_search_tree_remove(BinarySearchTree * t, const void * data){
    if (!*t)
        return 0;
    if ((*t)->d->type_descriptor->eq((*t)->data, data)) {
        BinarySearchTree tmp;
        void * data;
        tmp = *t;
        if(!(*t)->right && !(*t)->left){
            tmp->d->free(t);
        }else{
            if ((*t)->right){
                data = (*t)->d->extract_min(&(*t)->right);
                *t = binary_search_tree_builder(data, (*t)->d);
                (*t)->d->n++;
            } else if ((*t)->left){
                data = (*t)->d->extract_max(&(*t)->left);
                *t = binary_search_tree_builder(data, (*t)->d);
                (*t)->d->n++;
            }
            (*t)->right = tmp->right;
            (*t)->left = tmp->left;
            tmp->left = tmp->right = NULL;
            if(data) {
                tmp->d->type_descriptor->free_data(&data);
            }
            tmp->d->free(&tmp);
        }
        return 1;
    }
    if ((*t)->d->type_descriptor->lt(data, (*t)->data))
        return (*t)->d->remove(&(*t)->left, data);
    return (*t)->d->remove(&(*t)->right, data);
}

BinarySearchTree binary_search_tree_search(BinarySearchTree * t, const void * data){
    if (!*t)
        return NULL;
    if ((*t)->d->type_descriptor->gt((*t)->data, data))
        return (*t)->d->search(&(*t)->left, data);
    if ((*t)->d->type_descriptor->lt((*t)->data, data))
        return (*t)->d->search(&(*t)->right, data);
    return *t;
}

void binary_search_tree_node_print (BinarySearchTreeNode * n){
    if(n) n->d->node_fprint(stdout, n);
}

void binary_search_tree_node_fprint (FILE * stream, BinarySearchTreeNode * n){
    if(n) n->d->type_descriptor->fprint(stream, n->data);
}

void binary_search_tree_fprint_preorder(FILE * stream, BinarySearchTree t){
    if(!t) return;
    t->d->node_fprint(stream, t);
    t->d->fprint_preorder(stream, t->left);
    t->d->fprint_preorder(stream, t->right);
}

void binary_search_tree_fprint_inorder(FILE * stream, BinarySearchTree t){
    if(!t) return;
    t->d->fprint_inorder(stream, t->left);
    t->d->node_fprint(stream, t);
    t->d->fprint_inorder(stream, t->right);
}

void binary_search_tree_fprint_postorder(FILE * stream, BinarySearchTree t){
    if(!t) return;
    t->d->fprint_postorder(stream, t->left);
    t->d->fprint_postorder(stream, t->right);
    t->d->node_fprint(stream, t);
}

static void _binary_search_tree_to_dot(BinarySearchTree t, FILE * stream){
    if(!t) return;
    fprintf(stream, "  n%p [label=\"<left> | <valeur> ", (void *) &*t);
    t->d->node_fprint(stream, t);
    fprintf(stream, " | <right>\", color=\"#918d8d\"]\n");
    if(t->left)
        fprintf(stream, "  n%p:left:c -> n%p:valeur [color=red];\n", (void *) &*t, (void *) t->left);
    _binary_search_tree_to_dot(t->left, stream);
    if(t->right)
        fprintf(stream, "  n%p:right:c -> n%p:valeur [color=blue];\n", (void *) &*t, (void *) t->right);
    _binary_search_tree_to_dot(t->right, stream);
}

void binary_search_tree_to_dot(BinarySearchTree t, const char * dest_path){
    FILE * stream;
    if(!t) return;
    stream =fopen(dest_path, "w");
    if(!stream)
        printf("File can't be opened\n");
    fprintf(stream, "digraph arbre {\n"
               "  node [shape=record , height=.1 ]\n"
               "  edge [tailclip=false , arrowtail = dot , dir=both];\n");
    _binary_search_tree_to_dot(t, stream);
    fprintf(stream, "}\n");
    fclose(stream);
}

void binary_search_tree_descriptor_free(BinarySearchTreeDescriptor ** bstd) {
    if (!*bstd) return;
    type_descriptor_free(&((*bstd)->type_descriptor));
    free(*bstd);
    *bstd = NULL;
}

void binary_search_tree_free(BinarySearchTree * t){
    if(!*t) return;
    (*t)->d->free(&(*t)->left);
    (*t)->d->free(&(*t)->right);
    (*t)->d->type_descriptor->free_data(&(*t)->data);
    /* The tree will decrease of 1 node. */
    (*t)->d->n--;
    /* After that, the tree may be empty. Thus, the descriptor could no longer exist. */
    if((*t)->d->n == 0)
        binary_search_tree_descriptor_free(&(*t)->d);
    free(*t);
    *t = NULL;
}