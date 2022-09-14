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
 *
  */

#include "../../../include/data-structures/Trees/MLCL_AVLTree.h"
#include <assert.h>


/***************************************************
 * AVlTreeNode
 ***************************************************/

AVLTreeNode * new_avl_tree_node(void *data){
    AVLTreeNode * node;
    node = (AVLTreeNode *) malloc(sizeof(AVLTreeNode));
    if(!node) return NULL;
    node->data = data;
    node->balance = 0;
    node->left = node->right = NULL;
    return node;
}

void avl_tree_node_free(AVLTreeNode **self, void (*data_free) (void *)){
    if(!*self) return;
    if(data_free)
        data_free((*self)->data);
    free(*self);
    *self = NULL;
}

void avl_tree_node_fprint (const AVLTreeNode *self, FILE * stream, void (data_fprint) (const void *, FILE *)){
    if(!self) return;
    data_fprint(self->data, stream);
}

void avl_tree_node_print(const AVLTreeNode *self,  void (data_fprint) (const void *, FILE *)){
    avl_tree_node_fprint(self, stdout, data_fprint);
}


/***************************************************
 * AVlTree
 ***************************************************/

AVLTree * new_avl_tree(void (*type_manifest) (TypeDescriptor *)){
    AVLTree *tree;
    if(!type_manifest) return NULL;
    tree = (AVLTree *) malloc(sizeof(AVLTree));
    if(!tree) return NULL;
    tree->td = new_type_descriptor(type_manifest);
    if(!tree->td){
        avl_tree_free(&tree);
        return NULL;
    }
    tree->root = NULL;
    tree->n = 0;
    return tree;
}


static void avl_tree_l_rotation(AVLTreeNode **root){
    AVLTreeNode *newr;
    int i, j;
    if(!*root || !(*root)->right)
        return;
    /* Update subtrees */
    newr = (*root)->right;
    (*root)->right = newr->left;
    newr->left = *root;

    /* Updates balances */
    i = (*root)->balance;
    j = newr->balance;

    /* Update root balance */
    if(j >= 0)
        (*root)->balance = i - j - 1;
    else
        (*root)->balance = i - 1;

    /* Update new root balance */
    if((*root)->balance <= 0)
        newr->balance = j + (*root)->balance - 1;
    else
        newr->balance = j - 1;

    /* switch roots */
    *root = newr;
}

static void avl_tree_r_rotation(AVLTreeNode **root){
    AVLTreeNode *newr;
    int i, j;
    if(!*root || !(*root)->left)
        return;

    /* Update subtrees */
    newr = (*root)->left;
    (*root)->left = newr->right;
    newr->right = *root;

    /* Update balances */
    i = (*root)->balance;
    j = newr->balance;

    /* Update root balance */
    if(j > 0)
        (*root)->balance = i + 1;
    else
        (*root)->balance = i - j + 1;

    /* Update new root balance */
    if((*root)->balance <= 0)
        newr->balance = j + 1;
    else
        newr->balance = j + (*root)->balance + 1;

    /* switch roots */
    *root = newr;
}

static void avl_tree_lr_rotation(AVLTreeNode **root){
    avl_tree_l_rotation(&(*root)->left);
    avl_tree_r_rotation(root);
}

static void avl_tree_rl_rotation(AVLTreeNode **root){
    avl_tree_r_rotation(&(*root)->right);
    avl_tree_l_rotation(root);
}


static void avl_tree_balance(AVLTreeNode **root){
    if((*root)->balance == 2){
        if((*root)->right->balance >= 0)
            avl_tree_l_rotation(root);
        else
            avl_tree_rl_rotation(root);

    }else if((*root)->balance == -2){
        if((*root)->left->balance <= 0)
            avl_tree_r_rotation(root);
        else
            avl_tree_lr_rotation(root);
    }

}

int avl_tree_add_(AVLTreeNode **root, void *data, int (*cmp) (const void *, const void *)){
    int var;
    if(!*root){
        if((*root = new_avl_tree_node(data)))
            return 1;
        return 0;
    }
    /* no duplicates */
    if(cmp(data, (*root)->data) == 0)
        return 0;
    if(cmp((*root)->data, data) > 0)
        var = -avl_tree_add_(&(*root)->left, data, cmp);
    else
        var = avl_tree_add_(&(*root)->right, data, cmp);
    if(var != 0){
        (*root)->balance += var;
        avl_tree_balance(root);
        if((*root)->balance == 0)
            return 0;
        else
            return 1;
    } else
        return 0;
}



int avl_tree_add(AVLTree *self, void *data){
    if(!self || !data) return 0;
    return avl_tree_add_(&self->root, data, self->td->cmp) && ++self->n;
}

int avl_tree_extract_min_(AVLTreeNode **root, void *rdata){
    if (!*root || !rdata) return 0;
    if (!(*root)->left) {
        AVLTreeNode *tmp = *root;
        rdata = tmp->data;
        *root = (*root)->right;
        avl_tree_node_free(&tmp, NULL);
        return 1;
    }
    return avl_tree_extract_min_(&(*root)->left, rdata);
}

int avl_tree_extract_min(AVLTree *self, void *rdata){
    if(!self || !self->root || !rdata) return 0;
    return avl_tree_extract_min_(&self->root, rdata) && --self->n;
}

int avl_tree_extract_max_(AVLTreeNode **root, void *rdata){
    if (!*root || !rdata) return 0;
    if (!(*root)->right) {
        AVLTreeNode *tmp = *root;
        rdata = tmp->data;
        *root = (*root)->left;
        avl_tree_node_free(&tmp, NULL);
        return 1;
    }
    return avl_tree_extract_max_(&(*root)->right, rdata);
}

int avl_tree_extract_max(AVLTree *self, void *rdata){
    if(!self || !self->root || !rdata) return 0;
    return avl_tree_extract_min_(&self->root, rdata) && --self->n;
}

int avl_tree_remove_(AVLTreeNode **root, const void *data, int (*cmp) (const void *, const void *), void (*data_free) (void *)){
    /* return 1 if height decreased */
    AVLTreeNode *tmp;
    int maj;

    if(!*root)
        return 0;

    if(cmp(data, (*root)->data) < 0)
        maj = avl_tree_remove_(&(*root)->left, data, cmp, data_free);

    else if(cmp(data, (*root)->data) > 0)
        maj = -avl_tree_remove_(&(*root)->right, data, cmp, data_free);

    else{
        /* Equal, so we remove the node */

        if(!(*root)->left && !(*root)->right){
            /* is a leaf */
            avl_tree_node_free(root, data_free);
            return 1;

        }else{
            if(!(*root)->left){
                /* has a right child only */
                tmp = *root;
                *root = (*root)->right;
                tmp->right = tmp->left = NULL;
                avl_tree_node_free(root, data_free);
                return 1;

            } else if(!(*root)->right){
                /* has a left child only */
                tmp = *root;
                *root = (*root)->left;
                tmp->right = tmp->left = NULL;
                avl_tree_node_free(root, data_free);
                return 1;

            }else{
                /* Possède deux fils */
                if((*root)->balance <= 0) {
                    maj = avl_tree_extract_max_(&(*root)->left, &(*root)->data);
                }else{
                    /* Négatif, car l'extraction dans fg fait pencher vers fd */
                    maj = -avl_tree_extract_min_(&(*root)->right, &(*root)->data);
                }
            }
        }
    }

    /* A modification has been made */
    if(maj != 0){

        /* Update root balance */
        (*root)->balance = (*root)->balance + maj;

        /* Balance 1 or -1, do nothing */
        if((*root)->balance == 1 || (*root)->balance == -1)
            return 0;

        /* If 0, then it was not balanced before deletion  */
        if((*root)->balance == 0)
            return 1;

        if((*root)->balance == -2){
            if((*root)->left->balance == 0)
                maj = 0;
            else
                maj = 1;
        }

        if((*root)->balance == 2){
            if((*root)->right->balance == 0)
                maj = 0;
            else
                maj = 1;
        }
        avl_tree_balance(root);
        return maj;
    }
    return 0;
}

int avl_tree_remove(AVLTree *self, const void *data){
    if(!self || !self->root || !data) return 0;
    return avl_tree_remove_(&self->root, data, self->td->cmp, self->td->data_free);
}
static int avl_tree_height_(const AVLTreeNode *root){
    int hln, hrn;
    if (!root) return -1;
    if (!root->left && !root->right) return 0;
    hln = avl_tree_height_(root->left);
    hrn = avl_tree_height_(root->right);
    return 1 + ((hln > hrn) ? hln : hrn);
}

int avl_tree_height(const AVLTree *self){
    if(!self) return -1;
    return avl_tree_height_(self->root);
}

/*static int binary_search_tree_nb_nodes_(const BinarySearchTreeNode *root) {
    if(!root) return 0;
    return 1
            + binary_search_tree_nb_nodes_(root->left)
            + binary_search_tree_nb_nodes_(root->right);
}*/
int avl_tree_nb_nodes(const AVLTree *self){
    if (!self) return 0;
    return self->n;
}

static int avl_tree_nb_leaves_(const AVLTreeNode *root){
    if (!root) return 0;
    if (!root->left && !root->right) return 1;
    return avl_tree_nb_leaves_(root->left)
           + avl_tree_nb_leaves_(root->right);
}

int avl_tree_nb_leaves(const AVLTree *self){
    if(!self) return 0;
    return avl_tree_nb_leaves_(self->root);
}


static int avl_tree_nb_internal_nodes_(const AVLTreeNode *root){
    if (!root) return 0;
    if (!root->left && !root->right) return 0;
    return 1
           + avl_tree_nb_internal_nodes_(root->left)
           + avl_tree_nb_internal_nodes_(root->right);
}
int avl_tree_nb_internal_nodes(const AVLTree *self){
    if(!self) return 0;
    return avl_tree_nb_internal_nodes_(self->root);
}


static int avl_tree_nb_two_children_(const AVLTreeNode *root){
    int x = 0;
    if (!root) return 0;
    if (root->left && root->right) x = 1;
    return x
           + avl_tree_nb_two_children_(root->left)
           + avl_tree_nb_two_children_(root->right);
}

int avl_tree_nb_two_children(const AVLTree *self){
    if(!self) return 0;
    return avl_tree_nb_two_children_(self->root);
}

static int avl_tree_is_perfect_bt_(const AVLTreeNode *root){
    if (!root) return 1;
    if ((!root->left && root->right) || (root->left && !root->right)) return 0;
    return avl_tree_is_perfect_bt_(root->left)
           && avl_tree_is_perfect_bt_(root->right);
}

int avl_tree_is_perfect_bt(const AVLTree *self){
    if(!self) return 1;
    return avl_tree_is_perfect_bt_(self->root);
}

static AVLTreeNode * avl_tree_min_(AVLTreeNode *root){
    if (!root)
        return NULL;
    if (!root->left)
        return root;
    return avl_tree_min_(root->left);
}

AVLTreeNode * avl_tree_min(AVLTree *self){
    if(!self) return NULL;
    return avl_tree_min_(self->root);
}

static AVLTreeNode * avl_tree_max_(AVLTreeNode *root){
    if (!root)
        return NULL;
    if (!root->right)
        return root;
    return avl_tree_max_(root->right);
}

AVLTreeNode * avl_tree_max(AVLTree *self){
    if(!self) return NULL;
    return avl_tree_max_(self->root);
}

static int avl_tree_is_bst_(const AVLTreeNode *root, int (*cmp) (const void *, const void *)){
    AVLTreeNode *tmp, *tmp2;
    if (!root)
        return 1;
    tmp = avl_tree_max_(root->left);
    if (tmp && cmp(tmp->data, root->data) >= 0)
        return 0;
    tmp2 = avl_tree_min_(root->right);
    if (tmp2 && cmp(tmp2->data, root->data) <= 0)
        return 0;
    return avl_tree_is_bst_(root->left, cmp) && avl_tree_is_bst_(root->right, cmp);
}

int avl_tree_is_bst(const AVLTree *self){
    if(!self) return 1;
    return avl_tree_is_bst_(self->root, self->td->cmp);
}

AVLTreeNode * avl_tree_search_(AVLTreeNode **root, const void *data, int (*cmp) (const void *, const void *)){
    if (!*root)
        return NULL;
    if (cmp((*root)->data, data) > 0)
        return avl_tree_search_(&(*root)->left, data, cmp);
    if (cmp((*root)->data, data) < 0)
        return avl_tree_search_(&(*root)->right, data, cmp);
    return *root;
}

AVLTreeNode * avl_tree_search(AVLTree *self, const void *data){
    if(!self || !self->root) return NULL;
    return avl_tree_search_(&self->root, data, self->td->cmp);
}

static void avl_tree_fprint_preorder_(const AVLTreeNode *root, FILE *stream, void (*data_fprint) (const void *, FILE *)){
    if(!root) return;
    avl_tree_node_fprint(root, stream, data_fprint);
    avl_tree_fprint_preorder_(root->left, stream, data_fprint);
    avl_tree_fprint_preorder_(root->right, stream, data_fprint);
}

void avl_tree_fprint_preorder(const AVLTree *self, FILE *stream){
    if(!self) return;
    avl_tree_fprint_preorder_(self->root, stream, self->td->fprint);
}

static void avl_tree_fprint_inorder_(const AVLTreeNode *root, FILE *stream, void (*data_fprint) (const void *, FILE *)){
    if(!root) return;
    avl_tree_fprint_inorder_(root->left, stream, data_fprint);
    avl_tree_node_fprint(root, stream, data_fprint);
    avl_tree_fprint_inorder_(root->right, stream, data_fprint);
}

void avl_tree_fprint_inorder(const AVLTree *self, FILE *stream){
    if(!self) return;
    avl_tree_fprint_inorder_(self->root, stream, self->td->fprint);
}

static void avl_tree_fprint_postorder_(const AVLTreeNode *root, FILE *stream, void (*data_fprint) (const void *, FILE *)){
    if(!root) return;
    avl_tree_fprint_postorder_(root->left, stream, data_fprint);
    avl_tree_fprint_postorder_(root->right, stream, data_fprint);
    avl_tree_node_fprint(root, stream, data_fprint);
}

void avl_tree_fprint_postorder(const AVLTree *self, FILE *stream){
    if(!self) return;
    avl_tree_fprint_postorder_(self->root, stream, self->td->fprint);
}

static void avl_tree_to_dot_(const AVLTreeNode *root, FILE * stream, void (*data_fprint) (const void *, FILE *)){
    if(!root) return;
    fprintf(stream, "  n%p [label=\"<left> | <valeur> ", (void *) &*root);
    avl_tree_node_fprint(root, stream, data_fprint);
    fprintf(stream, " | <right>\", color=\"#918d8d\"]\n");
    if(root->left)
        fprintf(stream, "  n%p:left:c -> n%p:valeur [color=red];\n", (void *) &*root, (void *) root->left);
    avl_tree_to_dot_(root->left, stream, data_fprint);
    if(root->right)
        fprintf(stream, "  n%p:right:c -> n%p:valeur [color=blue];\n", (void *) &*root, (void *) root->right);
    avl_tree_to_dot_(root->right, stream, data_fprint);
}

void avl_tree_to_dot(const AVLTree *self, const char *dest_path){
    FILE * stream;
    if(!self) return;
    stream = fopen(dest_path, "w");
    if(!stream)
        printf("File can't be opened\n");
    fprintf(stream, "digraph tree {\n"
                    "  node [shape=record , height=.1 ]\n"
                    "  edge [tailclip=false , arrowtail = dot , dir=both];\n");
    avl_tree_to_dot_(self->root, stream, self->td->fprint);
    fprintf(stream, "}\n");
    fclose(stream);
}

static void avl_tree_clear_(AVLTreeNode **root, void (*data_free) (void *)){
    if(!*root) return;
    avl_tree_clear_(&(*root)->left, data_free);
    avl_tree_clear_(&(*root)->right, data_free);
    avl_tree_node_free(root, data_free);
}

void avl_tree_clear(AVLTree *self, void (*data_free) (void *)){
    if(!self) return;
    avl_tree_clear_(&self->root, data_free);
    self->n = 0;
}

void avl_tree_free(AVLTree **self){
    if(!*self) return;
    avl_tree_clear(*self, (*self)->td->data_free);
    type_descriptor_free(&(*self)->td);
    free(*self);
    *self = NULL;
}
