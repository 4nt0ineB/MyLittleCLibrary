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
    /*d->insert_branch = ternary_search_tree_insert_branch;
    d->add = ternary_search_tree_add;
    d->search = ternary_search_tree_search;
    d->remove = ternary_search_tree_remove;*/
    /*d->print = ternary_search_tree_print;
    d->fprint_ = ternary_search_tree_fprint_;
    d->fprint = ternary_search_tree_fprint;
    d->free = ternary_search_tree_free;
    d->to_dot_ = ternary_tree_to_dot_;
    d->to_dot = ternary_tree_to_dot;*/
    /* */
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

int bk_tree_insert_node(BKTree * root, BKTreeNode * bk_tree_node){
    int d;
    BKTree * tmp;
    /* Empty tree */
    if(!*root){
        *root = bk_tree_node;
        return 1;
    }
    d = mlcl_levenshtein((*root)->data, bk_tree_node->data);

    /* Already exists ?*/
    if(d == 0) {
        return 0;
    }

    /* Child ? */
    if((*root)->value == bk_tree_node->value){
        bk_tree_node->value = d;
        return (*root)->d->insert_node(&(*root)->child, bk_tree_node);
    }
    /* Look up on siblings */
    tmp = &(*root)->siblings;
    if(!*tmp){
        *tmp = bk_tree_node;
        return 1;
    }

    while(*tmp){
        if((*tmp)->value == bk_tree_node->value)
            return (*root)->d->insert_node(tmp, bk_tree_node);
        /* Ordered insertion of sibling */
        if((*tmp)->siblings && (*tmp)->siblings->value > bk_tree_node->value){
            bk_tree_node->siblings = (*tmp)->siblings;
            (*tmp)->siblings = bk_tree_node;
            return 1;
        }
        tmp = &(*tmp)->siblings;
    }
    /* Insert add brother */
    (*tmp) = bk_tree_node;
    return 1;
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

static void bk_tree_print_(BKTree root, int t){
    int i;
    if(!root) return;
    for(i = 0; i < t; i++)
        printf("      ");
    printf("%s%d─> ",(root->siblings) ? "├─" : "└─", root->value);
    root->d->type_descriptor->print(root->data);
    printf("\n");
    bk_tree_print_(root->child, t + 1);
    bk_tree_print_(root->siblings, t);
}

void bk_tree_print(BKTree root){
    if(!root) return;
    root->d->type_descriptor->print(root->data);
    printf("\n");
    bk_tree_print_(root->child, 0);
    bk_tree_print_(root->siblings, 0);
}
