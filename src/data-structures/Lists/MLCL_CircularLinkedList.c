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

#include "../../../include/data-structures/Lists/MLCL_CircularLinkedList.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/***************************************************
 * CircularLinkedListNode
 ***************************************************/
CircularLinkedListNode * new_circular_linked_list_node(void *data){
    CircularLinkedListNode *node;
    node = new_linked_list_node(data);
    if(!node) return NULL;
    node->next = node;
    return node;
}
void circular_linked_list_node_fprint(const CircularLinkedListNode *self, FILE *stream, void (data_fprint) (FILE *, const void *)){
    linked_list_node_fprint(self, stream, data_fprint);
}
void circular_linked_list_node_print(const CircularLinkedListNode *self, void (data_fprint) (FILE *, const void *)){
    linked_list_node_print(self, data_fprint);
}
void circular_linked_list_node_free(CircularLinkedListNode *self, void (*data_free) (void *data)){
    linked_list_node_free(self, data_free);
}

LinkedList * new_circular_linked_list(void (*type_manifest) (TypeDescriptor *td)){
    return new_linked_list(type_manifest);
}
int linked_list_append(CircularLinkedList *self, void *data){
    LinkedListNode *tmp;
    if(!self || data) return 0;
    if(!self->head){
        self->head = new_circular_linked_list_node(data);
        self->length++;
        return 1;
    }
    tmp = self->head;
    while(tmp->next != self->head)
        tmp = tmp->next;
    tmp->next = new_circular_linked_list_node(data);
    if(!tmp->next) return 0;
    tmp->next->next = self->head;
    self->length++;
    return 1;
}

/*
int linked_list_append_sorted(LinkedList *self, const void *, int (*ordering) (const void *, const void *));
*/

int circular_linked_list_prepend(LinkedList *self, void *data){
    LinkedListNode *tmp;
    if(!self || data) return 0;
    if(!self->head){
        self->head = new_circular_linked_list_node(data);
        self->length++;
        return 1;
    }
    tmp = self->head;
    while(tmp->next != self->head)
        tmp = tmp->next;
    tmp->next = new_circular_linked_list_node(data);
    if(!tmp->next) return 0;
    tmp->next->next = self->head;
    /* shift head */
    self->head = tmp->next;
    self->length++;
    return 1;
}

void * circular_linked_list_shift(LinkedList *self){
    LinkedListNode *tmp, *tmp_2;
    void * data;
    if(!self || !self->head) return NULL;
    data = self->head->data;
    tmp = self->head;
    tmp_2 = self->head->next;
    self->head = tmp_2;
    self->length--;
    circular_linked_list_node_free(tmp_2, self->td->free_data);
    return data;
}
void * circular_linked_list_pop(LinkedList *self){
    CircularLinkedListNode *tmp, *tmp_2;
    void * data;
    if(!self || !self->head) return NULL;
    tmp = self->head->next;
    /*
     1->2->3->4 - - >1
     we want to get the 3 to make it point to 1, and free the 4
    */
    while(tmp->next->next != self->head)
        tmp = tmp->next;
    tmp_2 = tmp->next;
    tmp->next = tmp->next->next;
    data = tmp_2->data;
    if(tmp == tmp_2)
        self->head = NULL;
    self->length--;
    circular_linked_list_node_free(tmp_2, self->td->free_data);
    return data;
    /*
     CircularLinkedListNode *tmp, *tmp_2;
    void * data;
    if(!self || !self->head) return NULL;
    tmp = self->head->next;
    if(tmp == self->head){
        data = self->head->data;
        circular_linked_list_node_free(tmp_2, self->td->free_data);
        self->head = NULL;
        return data;
    }
    while(tmp->next->next != self->head)
        tmp = tmp->next;
    tmp_2 = tmp->next;
    tmp->next = tmp->next->next;
    data = tmp_2->data;

    self->length--;
    circular_linked_list_node_free(tmp_2, self->td->free_data);
    return data;
     */
}
void * circular_linked_list_search(const LinkedList *self, int (*filter) (const void *)){
    CircularLinkedListNode *tmp;
    if(!self || !self->head || !filter) return 0;
    if(filter(self->head))
        return self->head->data;
    tmp = self->head->next;
    while(tmp->next != self->head){
        if(filter(tmp->data))
            return tmp->data;
        tmp = tmp->next;
    }
    return NULL;
}

/*
int circular_linked_list_remove(LinkedList *self, int (*filter) (const void *), void (*data_free) (void *data));
int circular_linked_list_remove_all(LinkedList *self, int (*filter) (const void *), void (*data_free) (void *data));
*/

void circular_linked_list_fprint(const LinkedList *self, FILE *stream){
    CircularLinkedListNode *tmp;
    if(!self || !self->head || !stream) return;
    tmp = self->head;
    while(tmp->next != self->head){
        circular_linked_list_node_fprint(tmp, stream, self->td->fprint);
        fprintf(stream, "%s", self->separator);
        tmp = tmp->next;
    }
    circular_linked_list_node_fprint(tmp, stream, self->td->fprint);
}
void circular_linked_list_print(const LinkedList *self){
    circular_linked_list_fprint(self, stdout);
}
void circular_linked_list_to_dot_(LinkedList *self, FILE *stream){
    CircularLinkedListNode *tmp;
    if(!self || !self->head || !stream) return;
    tmp = self->head;
    while(tmp->next != self->head){
        fprintf(stream, "  n%p [label=\"", (void *) tmp);
        circular_linked_list_node_fprint(tmp, stream, self->td->fprint);
        fprintf(stream, "\"]\n");
        fprintf(stream, " n%p -> n%p\n", (void *) tmp, (void *) tmp->next);
        tmp = tmp->next;
    }
    fprintf(stream, "  n%p [label=\"", (void *) tmp);
    circular_linked_list_node_fprint(tmp, stream, self->td->fprint);
    fprintf(stream, "\"]\n");
    fprintf(stream, " n%p -> n%p\n", (void *) tmp, (void *) tmp->next);
}
void circular_linked_list_to_dot(LinkedList *self, const char *path){
    FILE * stream;
    if(!self || !self->head || !path) return;
    stream = fopen(path, "w");
    if(!stream) printf("Can't write in %s\n", path);
    fprintf(stream, "digraph {\n"
                    "rankdir=\"LR\";\n"
                    "node [shape=square , height=.1, rank = same, color=\"#918d8d\"]\n"
    );
    circular_linked_list_to_dot_(self, stream);
    fprintf(stream, "}\n");
    fclose(stream);
}
void circular_linked_list_clear(LinkedList *self, void (*data_free) (void *data)){
    CircularLinkedListNode *tmp, *tmp_2;
    if(!self || !self->head || !data_free) return;
    tmp = self->head->next;
    while(tmp != self->head){
        tmp_2 = tmp->next;
        circular_linked_list_node_free(tmp, data_free);
        tmp = tmp_2;
    }
    circular_linked_list_node_free(tmp, data_free);
    self->head = NULL;
    self->length = 0;
}
void circular_linked_list_free(LinkedList *self, void (*data_free) (void *data)){
    if(!self || !self->head || !data_free) return;
    circular_linked_list_clear(self, data_free);
    type_descriptor_free(self->td);
    free(self);
}

/*************************
 **************************/


/*int circular_linked_list_add_(CircularLinkedList * cll, const void * data, int (*cmp) (const void *, const void *)){
    LinkedCell * new_cell;
    LinkedCell * tmp;
    if(!*cll) return 0;
    *//* Prepend *//*
    if(cmp(data, (*cll)->data))
        return (*cll)->d->prepend(cll, data);
    *//* Insert *//*
    if(!(new_cell = linked_list_builder(data, (*cll)->d)))
        return 0;
    tmp = (*cll)->next;
    while(tmp != *cll){
        if(cmp(data, (*cll)->data)){
            new_cell->next = tmp->next;
            tmp->next = new_cell;
            (*cll)->d->length++;
            return 1;
        }
        tmp = tmp->next;
    }
    *//* after "last" cell *//*
    new_cell->next = tmp->next;
    tmp->next = new_cell;
    (*cll)->d->length++;
    return 1;
}*/