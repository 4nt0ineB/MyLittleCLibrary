/*
 *   This file is part of the MLCL Library.
 *   Antoine Bastos 2022
 *
 *   This Library is free software under the terms of
 *   the MIT license.
 */

#include "../../include/List/MLCL_CircularLinkedList.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

LinkedCell * circular_linked_list_builder(const void * data, CircularLinkedListDescriptor * descriptor){
    LinkedCell * cell;
    if((cell = linked_list_builder(data, descriptor))){
        /* Circular */
        cell->next = cell;
    }
    return cell;
}

CircularLinkedListDescriptor * circular_linked_list_descriptor(){
    CircularLinkedListDescriptor * cll_descriptor;
    if((cll_descriptor = linked_list_descriptor())){
        /* Override affected function */
        cll_descriptor->add_ = circular_linked_list_add_;
        cll_descriptor->prepend = circular_linked_list_prepend;
        cll_descriptor->append = circular_linked_list_append;
        cll_descriptor->shift = circular_linked_list_shift;
        cll_descriptor->search = circular_linked_list_search;
        cll_descriptor->pop = circular_linked_list_pop;
        cll_descriptor->free = circular_linked_list_free;
        cll_descriptor->print = circular_linked_list_print;
        cll_descriptor->fprint = circular_linked_list_fprint;
        cll_descriptor->to_dot = circular_linked_list_to_dot;
    }
    return cll_descriptor;
}

CircularLinkedList new_circular_linked_list(const void * data, void (*type_manifest) (TypeDescriptor *)){
    CircularLinkedListDescriptor * cll_descriptor;
    if(!type_manifest) return NULL;
    if((cll_descriptor = circular_linked_list_descriptor()))
        cll_descriptor->type_descriptor = new_type_descriptor(type_manifest);
    return circular_linked_list_builder(data, cll_descriptor);
}

int circular_linked_list_add_(CircularLinkedList * cll, const void * data, int (*cmp) (const void *, const void *)){
    LinkedCell * new_cell;
    LinkedCell * tmp;
    if(!*cll) return 0;
    /* Prepend */
    if(cmp(data, (*cll)->data))
        return (*cll)->d->prepend(cll, data);
    /* Insert */
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
    /* after "last" cell */
    new_cell->next = tmp->next;
    tmp->next = new_cell;
    (*cll)->d->length++;
    return 1;
}

CircularLinkedList circular_linked_list_search(CircularLinkedList ll, const void * data){
    CircularLinkedList tmp;
    if(!ll) return 0;
    if(!ll->d->type_descriptor->cmp(ll->data, data))
        return ll;
    tmp = ll->next;
    while(tmp->next != ll){
        if(!tmp->d->type_descriptor->cmp(tmp->data, data))
            return tmp;
        tmp = tmp->next;
    }
    return NULL;
}

int circular_linked_list_prepend(CircularLinkedList * cll, const void * data){
    /*LinkedCell * cell;
    void * data_tmp;
    if(!*cll)
        return 0;
    if(!(cell = linked_list_builder(data, (*cll)->d)))
        return 0;
    *//*
      We have to switch the data of the cells
      because we don't want to mess with the pointer.
      As the last cell, from the point of view of the head, which we can't reach,
      still points to the head's address.
     *//*
    *//* Add allocated cell next to the head *//*
    cell->next = (*cll)->next;
    (*cll)->next = cell;
    *//* Switch data *//*
    data_tmp = cell->data;
    cell->data = (*cll)->data;
    (*cll)->data = data_tmp;
    (*cll)->d->length++;
    return 1;*/
    LinkedCell * cell;
    LinkedCell * tmp;
    if(!*cll) return 0;
    tmp = (*cll)->next;
    while(tmp->next != *cll)
        tmp = tmp->next;
    if(!(cell = linked_list_builder(data, (*cll)->d)))
        return 0;
    cell->next = tmp->next;
    tmp->next = cell;
    *cll = cell;
    (*cll)->d->length++;
    return 1;
}

int circular_linked_list_append(CircularLinkedList * cll, const void * data){
    LinkedCell * cell;
    LinkedCell * tmp;
    if(!*cll) return 0;
    tmp = (*cll)->next;
    while(tmp->next != *cll)
        tmp = tmp->next;
    if(!(cell = linked_list_builder(data, (*cll)->d)))
        return 0;
    cell->next = tmp->next;
    tmp->next = cell;
    (*cll)->d->length++;
    return 1;
}

void * circular_linked_list_shift(CircularLinkedList * ll){
    LinkedCell * tmp;
    LinkedCell * tmp_2;
    void * data;
    if(!*ll) return NULL;
    data = (*ll)->data;
    tmp = *ll;
    tmp_2 = (*ll)->next;
    **ll = *tmp_2;
    tmp->d->length--;
    if(tmp->d->length == 0){
        linked_list_descriptor_free(&tmp->d);
        *ll = NULL;
    }
    free(tmp_2);
    return data;
}

void * circular_linked_list_pop(CircularLinkedList * cll){
    LinkedCell * tmp;
    LinkedCell * tmp_2;
    void * data;
    if(!*cll) return NULL;
    tmp = (*cll)->next;
    if(tmp != *cll){
        /*
          1->2->3->4 ..->1
          we want to get the 3 to make it point to 1 and free the 4
         */
        while(tmp->next->next != *cll)
            tmp = tmp->next;
        tmp_2 = tmp->next;
        tmp->next = tmp->next->next;
    }else{
        tmp_2 = tmp;
    }
    data = tmp_2->data;
    tmp_2->next = NULL;
    tmp->d->length--;
    if(tmp->d->length == 0){
        linked_list_descriptor_free(&tmp->d);
        *cll = NULL;
    }
    free(tmp_2);
    return data;
}

void circular_linked_list_free(CircularLinkedList * cll){
    CircularLinkedList tmp;
    CircularLinkedList tmp_2;
    if(!*cll) return;
    tmp = (*cll)->next;
    while(tmp != *cll){
        tmp_2 = tmp->next;
        tmp->d->type_descriptor->free_data(&tmp->data);
        free(tmp);
        tmp = tmp_2;
    }
    (*cll)->d->type_descriptor->free_data(&(*cll)->data);
    linked_list_descriptor_free(&(*cll)->d);
    free(*cll);
    *cll = NULL;
}

void circular_linked_list_print(CircularLinkedList cll){
    if(cll) cll->d->fprint(stdout, cll);
}

void circular_linked_list_fprint(FILE * file, CircularLinkedList cll){
    CircularLinkedList tmp;
    if(!cll) return;
    tmp = cll->next;
    cll->d->cell_fprint(file, cll); printf(", ");
    while(tmp != cll){
        tmp->d->cell_fprint(file, tmp); printf(", ");
        tmp = tmp->next;
    }
}

static void _circular_linked_list_to_dot(CircularLinkedList ll, FILE * file){
    CircularLinkedList tmp;
    tmp = ll;
    while(tmp->next != ll){
        fprintf(file, "  n%p [label=\"", (void *) tmp);
        tmp->d->cell_fprint(file, tmp);
        fprintf(file, "\"]\n");
        fprintf(file, " n%p -> n%p\n", (void *) tmp, (void *) tmp->next);
        tmp = tmp->next;
    }
    fprintf(file, "  n%p [label=\"", (void *) tmp);
    tmp->d->cell_fprint(file, tmp);
    fprintf(file, "\"]\n");
    fprintf(file, " n%p -> n%p\n", (void *) tmp, (void *) tmp->next);
}

void circular_linked_list_to_dot(CircularLinkedList ll, const char * dest_path){
    FILE * file;
    if(!ll) return;
    file = fopen(dest_path, "w");
    if(!file)
        printf("File can't be opened\n");
    fprintf(file, "digraph {\n"
                  "rankdir=\"LR\";\n"
                  "node [shape=square , height=.1, rank = same, color=\"#918d8d\"]\n"
    );
    _circular_linked_list_to_dot(ll, file);
    fprintf(file, "}\n");
    fclose(file);
}
