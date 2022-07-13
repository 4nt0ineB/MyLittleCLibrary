/*
 *   This file is part of the MLCL Library.
 *   Antoine Bastos 2022
 *
 *   This Library is free software under the terms of
 *   the MIT license.
 */

#include "../include/MLCL_CircularDoubleLinkedList.h"
#include "../include/MLCL_DoubleLinkedList.h"



DoubleLinkedCell * circular_double_linked_list_builder(const void * data, CircularDoubleLinkedListDescriptor * descriptor){
    DoubleLinkedCell * dlc;
    if((dlc = double_linked_list_builder(data, descriptor))){
        /* Circular */
        dlc->next = dlc;
        dlc->prev = dlc;
    }
    return dlc;
}

CircularDoubleLinkedListDescriptor * circular_double_linked_list_descriptor(){
    DoubleLinkedListDescriptor * dlld;
    if((dlld = double_linked_list_descriptor())){
        /* Override affected function */
        dlld->prepend = circular_double_linked_list_prepend;
        dlld->append = circular_double_linked_list_append;
        dlld->free = circular_double_linked_list_free;
        dlld->search = circular_double_linked_list_search;
        dlld->shift = circular_double_linked_list_shift;
        dlld->pop = circular_double_linked_list_pop;
        dlld->print = circular_double_linked_list_print;
        dlld->fprint = circular_double_linked_list_fprint;
        dlld->to_dot = circular_double_linked_list_to_dot;
    }
    return dlld;
}

DoubleLinkedCell * new_circular_double_linked_list(const void * data, TypeDescriptor * type_descriptor){
    CircularDoubleLinkedListDescriptor * cdlld;
    if(!type_descriptor) return NULL;
    if((cdlld = circular_double_linked_list_descriptor()))
        cdlld->type_descriptor = type_descriptor;
    return circular_double_linked_list_builder(data, cdlld);
}

int circular_double_linked_list_prepend(CircularDoubleLinkedList * cdll, const void * data){
    DoubleLinkedCell * cell;
    CircularDoubleLinkedList tmp;
    if(!*cdll)
        return 0;
    if(!(cell = double_linked_list_builder(data, (*cdll)->d)))
        return 0;
    /* Save the head */
    tmp = *cdll;
    /* Change the head */
    *cdll = cell;
    /* Link prev save cell to new head */
    tmp->prev->next = cell;
    /* link the head to previous head */
    cell->prev = tmp->prev;
    tmp->prev = cell;
    cell->next = tmp;
    cell->d->length++;
    return 1;
}

int circular_double_linked_list_append(CircularDoubleLinkedList * cdll, const void * data){
    DoubleLinkedCell * cell;
    if(!*cdll)
        return 0;
    if(!(cell = double_linked_list_builder(data, (*cdll)->d)))
        return 0;
    cell->prev = (*cdll)->prev;
    cell->next = *cdll;
    (*cdll)->prev->next = cell;
    (*cdll)->prev = cell;
    cell->d->length++;
    return 1;
}

CircularDoubleLinkedList circular_double_linked_list_search(CircularDoubleLinkedList cdll, const void * data){
    CircularDoubleLinkedList tmp;
    if(!cdll) return 0;
    if(!cdll->d->type_descriptor->cmp(cdll->data, data))
        return cdll;
    tmp = cdll->next;
    while(tmp->next != cdll){
        if(!tmp->d->type_descriptor->cmp(tmp->data, data))
            return tmp;
        tmp = tmp->next;
    }
    return NULL;
}

void * circular_double_linked_list_shift(CircularDoubleLinkedList * cdll){
    DoubleLinkedCell * tmp;
    void * data;
    if(!cdll) return NULL;
    tmp = *cdll;
    data = tmp->data;
    *cdll = tmp->next;
    (*cdll)->prev = tmp->prev;
    tmp->prev->next = *cdll;


    tmp->next = tmp->prev = NULL;
    tmp->d->length--;
    if(tmp->d->length == 0){
        double_linked_list_descriptor_free(&tmp->d);
        *cdll = NULL;
    }
    free(tmp);
    return data;
}

void * circular_double_linked_list_pop(CircularDoubleLinkedList * cdll){
    if(!*cdll) return NULL;
    return (*cdll)->d->extract(&(*cdll)->prev);
}


void circular_double_linked_list_free(CircularDoubleLinkedList * cdll){
    CircularDoubleLinkedList tmp;
    CircularDoubleLinkedList tmp_2;
    if(!*cdll) return;
    tmp = (*cdll)->next;
    while(tmp != *cdll){
        tmp_2 = tmp->next;
        tmp->d->type_descriptor->free_data(&tmp->data);
        free(tmp);
        tmp = tmp_2;
    }
    (*cdll)->d->type_descriptor->free_data(&(*cdll)->data);
    double_linked_list_descriptor_free(&(*cdll)->d);
    free(*cdll);
    *cdll = NULL;
}

void circular_double_linked_list_print(CircularDoubleLinkedList cdll){
    circular_double_linked_list_fprint(stdout, cdll);
}

void circular_double_linked_list_fprint(FILE * file, CircularDoubleLinkedList cdll){
    CircularDoubleLinkedList tmp;
    if(!cdll) return;
    tmp = cdll->next;
    cdll->d->cell_fprint(file, cdll);printf(", ");
    while(tmp != cdll){
        tmp->d->cell_fprint(file, tmp);printf(", ");
        tmp = tmp->next;
    }
}

static void _circular_double_linked_list_to_dot(CircularDoubleLinkedList cdll, FILE * file){
    CircularDoubleLinkedList tmp;
    tmp = cdll;
    while(tmp->next != cdll){
        fprintf(file, "  n%p [label=\"", (void *) tmp);
        tmp->d->cell_fprint(file, tmp);
        fprintf(file, "\"]\n");
        fprintf(file, " n%p -> n%p\n", (void *) tmp, (void *) tmp->next);
        fprintf(file, " n%p -> n%p\n", (void *) tmp->next, (void *) tmp);
        tmp = tmp->next;
    }
    fprintf(file, "  n%p [label=\"", (void *) tmp);
    tmp->d->cell_fprint(file, tmp);
    fprintf(file, "\"]\n");
    fprintf(file, " n%p -> n%p\n", (void *) tmp, (void *) tmp->next);
    fprintf(file, " n%p -> n%p\n", (void *) tmp->next, (void *) tmp);
}

void circular_double_linked_list_to_dot(CircularDoubleLinkedList cdll, const char * dest_path){
    FILE * file;
    if(!cdll) return;
    file = fopen(dest_path, "w");
    if(!file)
        printf("Couldn't open a file\n");
    fprintf(file, "digraph {\n"
                  "rankdir=\"LR\";\n"
                  "splines=ortho;\n"
                  "node [shape=square , height=.1, rank = same, color=\"#918d8d\"]\n"
    );
    _circular_double_linked_list_to_dot(cdll, file);
    fprintf(file, "}\n");
    fclose(file);
}
