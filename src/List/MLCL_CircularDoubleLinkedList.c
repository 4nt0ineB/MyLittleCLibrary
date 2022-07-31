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

#include "../../include/List/MLCL_CircularDoubleLinkedList.h"
#include "../../include/List/MLCL_DoubleLinkedList.h"



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
        dlld->add_ = circular_double_linked_list_add_;
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

DoubleLinkedCell * new_circular_double_linked_list(const void * data, void (*type_manifest) (TypeDescriptor *)){
    CircularDoubleLinkedListDescriptor * cdlld;
    if(!type_manifest) return NULL;
    if((cdlld = circular_double_linked_list_descriptor()))
        cdlld->type_descriptor = new_type_descriptor(type_manifest);
    return circular_double_linked_list_builder(data, cdlld);
}

int circular_double_linked_list_add_(CircularDoubleLinkedList * cll, const void * data, int (*cmp) (const void *, const void *)){
    DoubleLinkedCell * new_cell;
    DoubleLinkedCell * tmp;
    if(!*cll) return 0;
    /* Prepend */
    if(cmp(data, (*cll)->data))
        return (*cll)->d->prepend(cll, data);
    /* Insert */
    if(!(new_cell = double_linked_list_builder(data, (*cll)->d)))
        return 0;
    tmp = (*cll)->next;
    while(tmp != *cll){
        if(cmp(data, (*cll)->data)){
            new_cell->next = tmp->next;
            tmp->next->prev = new_cell;
            tmp->next = new_cell;
            (*cll)->d->length++;
            return 1;
        }
        tmp = tmp->next;
    }
    /* after "last" cell */
    new_cell->next = tmp->next;
    tmp->next->prev = new_cell;
    tmp->next = new_cell;
    (*cll)->d->length++;
    return 1;
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
    if(cdll) cdll->d->fprint(stdout, cdll);
}

void circular_double_linked_list_fprint(FILE * stream, CircularDoubleLinkedList cdll){
    CircularDoubleLinkedList tmp;
    if(!cdll) return;
    tmp = cdll->next;
    cdll->d->cell_fprint(stream, cdll);printf(", ");
    while(tmp != cdll){
        tmp->d->cell_fprint(stream, tmp);printf(", ");
        tmp = tmp->next;
    }
}

static void _circular_double_linked_list_to_dot(CircularDoubleLinkedList cdll, FILE * stream){
    CircularDoubleLinkedList tmp;
    tmp = cdll;
    while(tmp->next != cdll){
        fprintf(stream, "  n%p [label=\"", (void *) tmp);
        tmp->d->cell_fprint(stream, tmp);
        fprintf(stream, "\"]\n");
        fprintf(stream, " n%p -> n%p\n", (void *) tmp, (void *) tmp->next);
        fprintf(stream, " n%p -> n%p\n", (void *) tmp->next, (void *) tmp);
        tmp = tmp->next;
    }
    fprintf(stream, "  n%p [label=\"", (void *) tmp);
    tmp->d->cell_fprint(stream, tmp);
    fprintf(stream, "\"]\n");
    fprintf(stream, " n%p -> n%p\n", (void *) tmp, (void *) tmp->next);
    fprintf(stream, " n%p -> n%p\n", (void *) tmp->next, (void *) tmp);
}

void circular_double_linked_list_to_dot(CircularDoubleLinkedList cdll, const char * dest_path){
    FILE * stream;
    if(!cdll) return;
    stream =fopen(dest_path, "w");
    if(!stream)
        printf("File can't be opened\n");
    fprintf(stream, "digraph {\n"
                  "rankdir=\"LR\";\n"
                  "splines=ortho;\n"
                  "node [shape=square , height=.1, rank = same, color=\"#918d8d\"]\n"
    );
    _circular_double_linked_list_to_dot(cdll, stream);
    fprintf(stream, "}\n");
    fclose(stream);
}
