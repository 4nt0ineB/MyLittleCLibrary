/*
 *   This file is part of the MLCL Library
 *   Antoine Bastos 2022
 *   SPDX-License-Identifier: Apache-2.0
 */

#include "../../../include/data-structures/Trees/MLCL_BinarySearchTree.h"
#include "../../../include/utils/MLCL_utils.h"

/***************************************************
 * BinarySearchTreeNode
 ***************************************************/

BinarySearchTreeNode * new_binary_search_tree_node(void *data){
    BinarySearchTreeNode *node;
    node = (BinarySearchTreeNode *) calloc(1, sizeof(BinarySearchTreeNode));
    if(!node) return NULL;
    node->data = data;
    node->left = node->right = NULL;
    return node;
}

void binary_search_tree_node_free(BinarySearchTreeNode **self, void (*data_free) (void *)){
    if(!*self) return;
    if(data_free) data_free((*self)->data);
    free(*self);
    *self = NULL;
}

void binary_search_tree_node_print(const BinarySearchTreeNode *self, void (data_fprint) (const void *, FILE *)){
    binary_search_tree_node_fprint(self, stdout, data_fprint);
}

void binary_search_tree_node_fprint(const BinarySearchTreeNode *self, FILE * stream, void (data_fprint) (const void *, FILE *)){
    if(self) data_fprint(self->data, stream);
}

/***************************************************
 * BinarySearchTree
 ***************************************************/


BinarySearchTree * new_binary_search_tree(void (*type_manifest) (TypeDescriptor *)){
    BinarySearchTree *tree;
    if(!type_manifest) return NULL;
    tree = (BinarySearchTree *) malloc(sizeof(BinarySearchTree));
    if(!tree) return NULL;
    tree->td = new_type_descriptor(type_manifest);
    if(!tree->td){
        binary_search_tree_free(&tree);
    }
    tree->n = 0;
    tree->root = NULL;
    return tree;
}

static int binary_search_tree_height_(const BinarySearchTreeNode *root){
    int hln, hrn;
    if (!root) return -1;
    if (!root->left && !root->right) return 0;
    hln = binary_search_tree_height_(root->left);
    hrn = binary_search_tree_height_(root->right);
    return 1 + ((hln > hrn) ? hln : hrn);
}

int binary_search_tree_height(const BinarySearchTree *self){
    if(!self) return -1;
    return binary_search_tree_height_(self->root);
}

/*static int binary_search_tree_nb_nodes_(const BinarySearchTreeNode *root) {
    if(!root) return 0;
    return 1
            + binary_search_tree_nb_nodes_(root->left)
            + binary_search_tree_nb_nodes_(root->right);
}*/
int binary_search_tree_nb_nodes(const BinarySearchTree *self){
    if (!self) return 0;
    return self->n;
}

static int binary_search_tree_nb_leaves_(const BinarySearchTreeNode *root){
    if (!root) return 0;
    if (!root->left && !root->right) return 1;
    return binary_search_tree_nb_leaves_(root->left)
            + binary_search_tree_nb_leaves_(root->right);
}

int binary_search_tree_nb_leaves(const BinarySearchTree *self){
    if(!self) return 0;
    return binary_search_tree_nb_leaves_(self->root);
}


static int binary_search_tree_nb_internal_nodes_(const BinarySearchTreeNode *root){
    if (!root) return 0;
    if (!root->left && !root->right) return 0;
    return 1
            + binary_search_tree_nb_internal_nodes_(root->left)
            + binary_search_tree_nb_internal_nodes_(root->right);
}
int binary_search_tree_nb_internal_nodes(const BinarySearchTree *self){
    if(!self) return 0;
    return binary_search_tree_nb_internal_nodes_(self->root);
}


static int binary_search_tree_nb_two_children_(const BinarySearchTreeNode *root){
    int x = 0;
    if (!root) return 0;
    if (root->left && root->right) x = 1;
    return x
            + binary_search_tree_nb_two_children_(root->left)
            + binary_search_tree_nb_two_children_(root->right);
}

int binary_search_tree_nb_two_children(const BinarySearchTree *self){
    if(!self) return 0;
    return binary_search_tree_nb_two_children_(self->root);
}

static int binary_search_tree_is_perfect_bt_(const BinarySearchTreeNode *root){
    if (!root) return 1;
    if ((!root->left && root->right) || (root->left && !root->right)) return 0;
    return binary_search_tree_is_perfect_bt_(root->left)
            && binary_search_tree_is_perfect_bt_(root->right);
}

int binary_search_tree_is_perfect_bt(const BinarySearchTree *self){
    if(!self) return 1;
    return binary_search_tree_is_perfect_bt_(self->root);
}

static BinarySearchTreeNode * binary_search_tree_min_(BinarySearchTreeNode *root){
    if (!root)
        return NULL;
    if (!root->left)
        return root;
    return binary_search_tree_min_(root->left);
}

BinarySearchTreeNode * binary_search_tree_min(BinarySearchTree *self){
    if(!self) return NULL;
    return binary_search_tree_min_(self->root);
}

static BinarySearchTreeNode * binary_search_tree_max_(BinarySearchTreeNode *root){
    if (!root)
        return NULL;
    if (!root->right)
        return root;
    return binary_search_tree_max_(root->right);
}

BinarySearchTreeNode * binary_search_tree_max(BinarySearchTree *self){
    if(!self) return NULL;
    return binary_search_tree_max_(self->root);
}

static int binary_search_tree_is_bst_(const BinarySearchTreeNode *root, int (*cmp) (const void *, const void *)){
    BinarySearchTreeNode *tmp, *tmp2;
    if (!root)
        return 1;
    tmp = binary_search_tree_max_(root->left);
    if (tmp && cmp(tmp->data, root->data) >= 0)
        return 0;
    tmp2 = binary_search_tree_min_(root->right);
    if (tmp2 && cmp(tmp2->data, root->data) <= 0)
        return 0;
    return binary_search_tree_is_bst_(root->left, cmp) && binary_search_tree_is_bst_(root->right, cmp);
}

int binary_search_tree_is_bst(const BinarySearchTree *self){
    if(!self) return 1;
    return binary_search_tree_is_bst_(self->root, self->td->cmp);
}

static int binary_search_tree_add_(BinarySearchTreeNode **root, void *data, int (*cmp) (const void *, const void *)){
    if (!*root)
        return (*root = new_binary_search_tree_node(data)) ? 1 : 0;
    if (cmp((*root)->data, data) > 0)
        return binary_search_tree_add_(&(*root)->left, data, cmp);
    if (cmp((*root)->data, data) <= 0)
        return binary_search_tree_add_(&(*root)->right, data, cmp);
    return 0;
}

int binary_search_tree_add(BinarySearchTree *self, void *data){
    if(!self) return 0;
    return binary_search_tree_add_(&self->root, data, self->td->cmp) && ++self->n;
}

static void * binary_search_tree_extract_min_(BinarySearchTreeNode **root){
    if (!*root)
        return NULL;
    if (!(*root)->left) {
        BinarySearchTreeNode *tmp;
        void *data;
        tmp = *root;
        data = tmp->data;
        *root = tmp->right;
        binary_search_tree_node_free(&tmp, NULL);
        return data;
    }
    return binary_search_tree_extract_min_(&(*root)->left);
}

void * binary_search_tree_extract_min(BinarySearchTree *self){
    void *tmp;
    if(!self) return NULL;
    tmp = binary_search_tree_extract_min_(&self->root);
    if(tmp) --self->n;
    return tmp;
}

static void * binary_search_tree_extract_max_(BinarySearchTreeNode **root) {
    if (!*root)
        return NULL;
    if (!(*root)->right) {
        BinarySearchTreeNode *tmp;
        void *data;
        tmp = *root;
        data = tmp->data;
        *root = tmp->left;
        binary_search_tree_node_free(&tmp, NULL);
        return data;
    }
    return binary_search_tree_extract_max_(&(*root)->left);
}
void * binary_search_tree_extract_max(BinarySearchTree *self) {
    if(!self) return NULL;
    return binary_search_tree_extract_max_(&self->root);
}

static int binary_search_tree_remove_(BinarySearchTreeNode **root, const void *data, int (*cmp) (const void *, const void *), void (*data_free) (void *)){
    if (!*root)
        return 0;
    if (cmp((*root)->data, data) == 0) {
        BinarySearchTreeNode *tmp;
        void *data_tmp;
        tmp = *root;
        if(!(*root)->right && !(*root)->left){
            binary_search_tree_node_free(root, data_free);
        }else{
            if ((*root)->right){
                data_tmp = binary_search_tree_extract_min_(&(*root)->right);
                *root = new_binary_search_tree_node(data_tmp);
            } else if ((*root)->left){
                data_tmp = binary_search_tree_extract_max_(&(*root)->left);
                *root = new_binary_search_tree_node(data_tmp);
            }
            (*root)->right = tmp->right;
            (*root)->left = tmp->left;
            tmp->left = tmp->right = NULL;
            binary_search_tree_node_free(&tmp, data_free);
        }
        return 1;
    }
    if (cmp(data, (*root)->data) < 0)
        return binary_search_tree_remove_(&(*root)->left, data, cmp, data_free);
    return binary_search_tree_remove_(&(*root)->right, data, cmp, data_free);
}

int binary_search_tree_remove(BinarySearchTree *self, const void *data){
    if(!self) return 0;
    return binary_search_tree_remove_(&self->root, data, self->td->cmp, self->td->data_free);
}

BinarySearchTreeNode * binary_search_tree_search_(BinarySearchTreeNode **root, const void *data, int (*cmp) (const void *, const void *)){
    if (!*root)
        return NULL;
    if (cmp((*root)->data, data) > 0)
        return binary_search_tree_search_(&(*root)->left, data, cmp);
    if (cmp((*root)->data, data) < 0)
        return binary_search_tree_search_(&(*root)->right, data, cmp);
    return *root;
}

BinarySearchTreeNode * binary_search_tree_search(BinarySearchTree *self, const void *data){
    if(!self || !self->root) return NULL;
    return binary_search_tree_search_(&self->root, data, self->td->cmp);
}


static void binary_search_tree_fprint_preorder_(const BinarySearchTreeNode *root, FILE *stream, void (*data_fprint) (const void *, FILE *)){
    if(!root) return;
    binary_search_tree_node_fprint(root, stream, data_fprint);
    binary_search_tree_fprint_preorder_(root->left, stream, data_fprint);
    binary_search_tree_fprint_preorder_(root->right, stream, data_fprint);
}

void binary_search_tree_fprint_preorder(const BinarySearchTree *self, FILE *stream){
    if(!self) return;
    binary_search_tree_fprint_preorder_(self->root, stream, self->td->fprint);
}

static void binary_search_tree_fprint_inorder_(const BinarySearchTreeNode *root, FILE *stream, void (*data_fprint) (const void *, FILE *)){
    if(!root) return;
    binary_search_tree_fprint_inorder_(root->left, stream, data_fprint);
    binary_search_tree_node_fprint(root, stream, data_fprint);
    binary_search_tree_fprint_inorder_(root->right, stream, data_fprint);
}

void binary_search_tree_fprint_inorder(const BinarySearchTree *self, FILE *stream){
    if(!self) return;
    binary_search_tree_fprint_inorder_(self->root, stream, self->td->fprint);
}

static void binary_search_tree_fprint_postorder_(const BinarySearchTreeNode *root, FILE *stream, void (*data_fprint) (const void *, FILE *)){
    if(!root) return;
    binary_search_tree_fprint_postorder_(root->left, stream, data_fprint);
    binary_search_tree_fprint_postorder_(root->right, stream, data_fprint);
    binary_search_tree_node_fprint(root, stream, data_fprint);
}

void binary_search_tree_fprint_postorder(const BinarySearchTree *self, FILE *stream){
    if(!self) return;
    binary_search_tree_fprint_postorder_(self->root, stream, self->td->fprint);
}

static void binary_search_tree_to_dot_(const BinarySearchTreeNode *root, FILE * stream, void (*data_fprint) (const void *, FILE *)){
    if(!root) return;
    fprintf(stream, "  n%p [label=\"<left> | <value> ", (void *) &*root);
    binary_search_tree_node_fprint(root, stream, data_fprint);
    fprintf(stream, " | <right>\", color=\"#000000\"]\n");
    if(root->left)
        fprintf(stream, "  n%p:left:c -> n%p:valeur [color=red];\n", (void *) &*root, (void *) root->left);
    binary_search_tree_to_dot_(root->left, stream, data_fprint);
    if(root->right)
        fprintf(stream, "  n%p:right:c -> n%p:valeur [color=blue];\n", (void *) &*root, (void *) root->right);
    binary_search_tree_to_dot_(root->right, stream, data_fprint);
}

void binary_search_tree_to_dot(const BinarySearchTree *self, const char * dest_path){
    FILE * stream;
    if(!self) return;
    stream = fopen(dest_path, "w");
    if(!stream)
        printf("File can't be opened\n");
    fprintf(stream, "digraph tree {\n"
               "  node [shape=record , height=.1 ]\n"
               "  edge [tailclip=false , arrowtail = dot , dir=both];\n");
    binary_search_tree_to_dot_(self->root, stream, self->td->fprint);
    fprintf(stream, "}\n");
    fclose(stream);
}




static void binary_search_tree_clear_(BinarySearchTreeNode **root, void (*data_free) (void *)){
    if(!*root) return;
    binary_search_tree_clear_(&(*root)->left, data_free);
    binary_search_tree_clear_(&(*root)->right, data_free);
    binary_search_tree_node_free(root, data_free);
}

void binary_search_tree_clear(BinarySearchTree *self, void (*data_free) (void *)){
    if(!self) return;
    binary_search_tree_clear_(&self->root, data_free);
    self->n = 0;
}

void binary_search_tree_free(BinarySearchTree **self){
    if(!*self) return;
    binary_search_tree_clear(*self, (*self)->td->data_free);
    type_descriptor_free(&(*self)->td);
    free(*self);
    *self = NULL;
}
