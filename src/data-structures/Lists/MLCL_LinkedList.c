/*
 *   This file is part of the MLCL Library
 *   Antoine Bastos 2022
 *   SPDX-License-Identifier: Apache-2.0
 */

#include "../../../include/data-structures/Lists/MLCL_LinkedList.h"
#include <assert.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

/***************************************************
 * LinkedListNode
 ***************************************************/

LinkedListNode * new_linked_list_node(void *data){
    LinkedListNode *node;
    if(!data) return NULL;
    node = (LinkedListNode *) malloc(sizeof(LinkedListNode));
    if(!node) return NULL;
    node->data = data;
    node->next = NULL;
    return node;
}

int linked_list_node_insert(LinkedListNode **self, void *data){
    LinkedListNode *node;
    if(!*self) return 0;
    node = new_linked_list_node(data);
    if(!node) return 0;
    node->next = (*self)->next;
    (*self)->next = node;
    return 1;
}

void linked_list_node_fprint(const LinkedListNode *self, FILE *stream, void (*data_fprint) (const void *, FILE *)){
    if(!self || !stream || !data_fprint) return;
    data_fprint(self->data, stream);
}

void linked_list_node_print(const LinkedListNode *self, void (*data_fprint) (const void *, FILE *)){
    if(!self || !data_fprint) return;
    linked_list_node_fprint(self, stdout, data_fprint);
}

void linked_list_node_free(LinkedListNode **self, void (*data_free) (void *)){
    if(!*self) return;
    if(data_free) data_free((*self)->data);
    free(*self);
    *self = NULL;
}

static void linked_list_merge_(LinkedListNode **l, LinkedListNode **r, int (*ordering) (const void *, const void *)){
    LinkedListNode *head_r, *head_l, *merged, *tmp;

    if(!*l){
        *l = *r;
        return;
    }

    if(!*r) return;

    head_r = *r;
    head_l = *l;

    if(ordering(head_l->data, head_r->data) == 1){
        merged = head_l;
        head_l = head_l->next;
    }else{
        merged = head_r;
        head_r = head_r->next;
    }

    tmp = merged;

    while(head_l && head_r){
        if(ordering(head_l->data, head_r->data) > 0){
            tmp->next = head_l;
            head_l = head_l->next;
        }else{
            tmp->next = head_r;
            head_r = head_r->next;
        }
        tmp = tmp->next;
    }

    while(head_l){
        tmp->next = head_l;
        head_l = head_l->next;
        tmp = tmp->next;
    }

    while(head_r){
        tmp->next = head_r;
        head_r = head_r->next;
        tmp = tmp->next;
    }

    *l = merged;
}

static void linked_list_merge_sort_(LinkedListNode **l, int (*ordering) (const void *, const void *)){
    LinkedListNode *mid;
    LinkedListNode *left;
    LinkedListNode *right;

    LinkedListNode *slow, *fast;

    if(!*l || !(*l)->next) return;

    slow = *l;
    fast = (*l)->next;
    while(fast && fast->next){
        slow = slow->next;
        fast = fast->next->next;
    }
    mid = slow;

    left = *l;
    right = mid->next;
    mid->next = NULL;

    linked_list_merge_sort_(&left, ordering);
    linked_list_merge_sort_(&right, ordering);

    linked_list_merge_(&left, &right, ordering);
    *l = left;
}

/***************************************************
 * LinkedList
 ***************************************************/

LinkedList * new_linked_list(void (*type_manifest) (TypeDescriptor *td)){
    LinkedList *list;
    if(!type_manifest) return NULL;
    list = (LinkedList *) malloc(sizeof(LinkedList));
    if(!list) return NULL;
    list->head = NULL;
    list->length = 0;
    list->td = new_type_descriptor(type_manifest);
    strcpy(list->separator, ", ");
    if(!list->td) return NULL;
    return list;
}
int linked_list_append(LinkedList *self, void *data){
    LinkedListNode  *node;
    LinkedListNode *tmp;
    if(!self || !data) return 0;
    node = new_linked_list_node(data);
    if(!node) return 0;
    if(!self->head){
        self->head = node;
        return 1;
    }
    tmp = self->head;
    while(tmp->next)
        tmp = tmp->next;
    tmp->next = node;
    self->length++;
    return 1;
}

/*
int linked_list_append_sorted(LinkedList *self, const void *, int (*ordering) (const void *, const void *));
*/

int linked_list_prepend(LinkedList *self, void *data){
    LinkedListNode *node;
    if(!self || !data) return 0;
    node = new_linked_list_node(data);
    if(!node) return 0;
    node->next = self->head;
    self->head = node;
    self->length++;
    return 1;
}
void linked_list_merge_sort(LinkedList *self, int (*ordering) (const void *, const void *)){
    if(!self || !self->head || !ordering) return;
    linked_list_merge_sort_(&self->head, ordering);
}
void * linked_list_shift(LinkedList *self){
    LinkedListNode *tmp;
    void *data;
    if(!self || !self->head) return NULL;
    tmp = self->head;
    data = tmp->data;
    self->head = tmp->next;
    self->length--;
    linked_list_node_free(&tmp, NULL);
    return data;
}
void * linked_list_pop(LinkedList *self){
    LinkedListNode *tmp, *tmp_2;
    void *data;
    if(!self || !self->head) return NULL;
    /* Head */
    if(!self->head->next){
        data = self->head->data;
        tmp_2 = self->head;
        self->head = NULL;
    }else{
        tmp = self->head;
        while(tmp->next->next)
            tmp = tmp->next;
        data = tmp->next->data;
        tmp_2 = tmp->next;
        tmp->next = NULL;
    }
    linked_list_node_free(&tmp_2, NULL);
    self->length--;
    return data;
}

void * linked_list_search(const LinkedList *self, Filter *filter){
    LinkedListNode *tmp;
    if(!self || !self->head || !filter) return NULL;
    tmp = self->head;
    while(tmp){
        if(filter->evaluate(filter, tmp->data))
            return tmp->data;
        tmp = tmp->next;
    }
    return NULL;
}

LinkedList * linked_list_search_all(const LinkedList *self, Filter *filter){
    LinkedList *filtered_data;
    LinkedListNode *tmp;
    if(!self || !self->head || !filter) return NULL;
    filtered_data = new_linked_list(self->td->manifest);
    tmp = self->head;
    while(tmp){
        if(filter->evaluate(filter, tmp->data))
            /* prepend - complexity concern */
            linked_list_prepend(filtered_data, tmp->data);
        tmp = tmp->next;
    }
    return filtered_data;
}

void * linked_list_extract(LinkedList *self, Filter *filter){
    LinkedListNode *cursor, *tmp;
    void *data;
    if(!self || !self->head || !filter) return NULL;
    cursor = self->head;
    /* Head */
    if(filter->evaluate(filter, cursor->data)){
        tmp = self->head->next;
        data = self->head->data;
        linked_list_node_free(&self->head, NULL);

        self->head = tmp;
        self->length--;
        return data;
    }
    /* not head */
    while(cursor->next){
        tmp = cursor->next;
        if(filter->evaluate(filter, tmp->data)){
            cursor->next = tmp->next;
            data = tmp->data;
            linked_list_node_free(&tmp, NULL);
            self->length--;
            return data;
        }
        cursor = cursor->next;
    }
    return NULL;
}


LinkedList * linked_list_extract_all(LinkedList *self, Filter *filter){
    LinkedListNode *tocheck, *tmp, *prev;
    LinkedList *filtered_data;
    int i;
    if(!self || !self->head || !filter) return NULL;
    filtered_data = new_linked_list(self->td->manifest);
    i = 0;
    prev = tocheck = NULL;
    tmp = self->head;
    while(tmp){
        tocheck = tmp->next;
        if(filter->evaluate(filter, tmp->data)){
            if(prev)
                prev->next = tocheck;
            else
                self->head = NULL;
            /* prepend - complexity concern */
            linked_list_prepend(filtered_data, tmp->data);
            linked_list_node_free(&tmp, NULL);
            i++;
        }else{
            /* become the last seen existing node */
            if(!prev)
                self->head = tmp;
            else
                prev = tmp;
        }
        tmp = tocheck;
    }
    self->length -= i;
    if(filtered_data->length == 0)
        linked_list_free(&filtered_data);
    return filtered_data;
}

int linked_list_remove_w(LinkedList *self, Filter *filter, void (data_free) (void *)){
    void *data;
    data = linked_list_extract(self, filter);
    if(data){
        if(data_free) data_free(data);
        return 1;
    }
    return 0;
}

int linked_list_remove(LinkedList *self, Filter *filter){
    return linked_list_remove_w(self, filter, self->td->data_free);
}

int linked_list_remove_all_w(LinkedList *self, Filter *filter, void (data_free) (void *)){
    LinkedList *filtered_data;
    int n = 0;
    filtered_data = linked_list_extract_all(self, filter);
    if(filtered_data){
        n = filtered_data->length;
        linked_list_free_w(&filtered_data, data_free);
    }
    return n;
}

int linked_list_remove_all(LinkedList *self, Filter *filter){
    return linked_list_remove_all_w(self, filter, self->td->data_free);
}

void linked_list_fprint(const LinkedList *self, FILE *stream){
    LinkedListNode *cursor;
    if(!self || !self->head || !stream) return;
    cursor = self->head;
    while(cursor->next){
        linked_list_node_fprint(cursor, stream, self->td->fprint);
        fprintf(stream, "%s", self->separator);
        cursor = cursor->next;
    }
    linked_list_node_fprint(cursor, stream, self->td->fprint);
}

void linked_list_print(const LinkedList *self){
    linked_list_fprint(self, stdout);
}

void linked_list_to_dot_(LinkedList *self, FILE *stream){
    LinkedListNode *cursor;
    if(!self || !stream) return;
    cursor = self->head;
    while(cursor){
        fprintf(stream, "  n%p [label=\"", (void *) cursor);
        linked_list_node_fprint(cursor, stream, self->td->fprint);
        fprintf(stream, "\" color=\"#000000\"]\n");
        if(cursor->next)
            fprintf(stream, " n%p -> n%p\n", (void *) cursor, (void *) cursor->next);
        cursor = cursor->next;
    }
}

void linked_list_to_dot(LinkedList *self, const char * path){
    FILE * stream;
    if(!self || !self->head) return;
    stream = fopen(path, "w");
    if(!stream) printf("Can't write in %s\n", path);
    fprintf(stream, "digraph {\n"
                    "rankdir=\"LR\";\n"
                    "splines=ortho;\n"
                    "node [shape=square , height=.1, rank = same]\n"
    );
    linked_list_to_dot_(self, stream);
    fprintf(stream, "}\n");
    fclose(stream);
}

void linked_list_clear_w(LinkedList *self, void (*data_free) (void *data)){
    LinkedListNode *cursor, *tmp;
    if(!self || !self->head) return;
    cursor = self->head;
    while(cursor){
        tmp = cursor;
        cursor = tmp->next;
        linked_list_node_free(&tmp, data_free);
    }
    self->head = NULL;
    self->length = 0;
}

void linked_list_clear(LinkedList *self){
    linked_list_clear_w(self, self->td->data_free);
}

void linked_list_free_w(LinkedList **self, void (*data_free) (void *)){
    if(!*self) return;
    linked_list_clear_w(*self, data_free);
    type_descriptor_free(&(*self)->td);
    free(*self);
    *self = NULL;
}

void linked_list_free(LinkedList **self){
    linked_list_free_w(self, (*self)->td->data_free);
}

/*int linked_list_add_(LinkedList * ll, const void *data, int (*cmp) (const void *, const void *)){
    LinkedCell * new_cell;
    *//* End of list OR Inside the list but inferior to the current cell *//*
    if(!*ll) return 0;
    if(cmp(data, (*ll)->data)){
        if(!(new_cell = linked_list_builder(data, (*ll)->d)))
            return 0;
        new_cell->next = *ll;
        (*ll) = new_cell;
        (*ll)->d->length++;
        return 1;
    }else if(!(*ll)->next){
        if(!(new_cell = linked_list_builder(data, (*ll)->d)))
            return 0;
        (*ll)->next = new_cell;
        (*ll)->d->length++;
        return 1;
    }
    return (*ll)->d->add_(&(*ll)->next, data, cmp);
}*/
/*

int linked_list_ordered_add(LinkedList * ll, const void *data){
    if(!*ll) return 0;
    return (*ll)->d->add_(ll,  data, (*ll)->d->type_descriptor->lt);
}

int linked_list_reverse_ordered_add(LinkedList * ll, const void *data){
    if(!*ll) return 0;
    return (*ll)->d->add_(ll,  data, (*ll)->d->type_descriptor->ge);
}
*/
