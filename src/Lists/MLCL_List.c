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

#include "../../include/Lists/MLCL_List.h"


List * new_list(LIST_TYPE list_type, void (*type_manifest) (TypeDescriptor *)){
    List * l;

    if(!(l = (List *) malloc(sizeof (List))))
        return NULL;

    l->type = list_type;
    l->type_manifest = type_manifest;

    /* methods */
    l->length = list_length;
    l->is_empty = list_is_empty;
    l->append = list_append;
    l->head_peek = list_head_peek;
    l->tail_peek = list_tail_peek;
    l->print = list_print;
    l->fprint = list_fprint;
    l->free = list_free;
    l->check_init_ = list_check_init_;
    l->pop = list_pop;
    l->shift = list_shift;

    switch (list_type) {
        case ARRAY_LIST:
            l->s.array_list = NULL;
            break;

        case LINKED_LIST:
            l->s.linked_list = NULL;
            break;

        case CIRCULAR_LINKED_LIST:
            l->s.circular_linked_list = NULL;
            break;

        case DOUBLE_LINKED_LIST:
            l->s.double_linked_list = NULL;
            break;

        case CIRCULAR_DOUBLE_LINKED_LIST:
            l->s.circular_double_linked_list = NULL;
            break;

        default:
            return NULL;
    }

    return l;
}

int list_length(const List *l){
    if(!l) return 0;
    if(l->is_empty(l)) return 0;
    switch (l->type) {
        case ARRAY_LIST:
            return l->s.array_list->count;

        case LINKED_LIST:
            return  l->s.linked_list->d->length;

        case CIRCULAR_LINKED_LIST:
            return l->s.circular_linked_list->d->length;

        case DOUBLE_LINKED_LIST:
            return l->s.double_linked_list->d->length;

        case CIRCULAR_DOUBLE_LINKED_LIST:
            return l->s.circular_double_linked_list->d->length;
    }
    return 0;
}

int list_check_init_(List *l, const void * data){
    if(!l) return 0;
    if(l->is_empty(l)){

        switch (l->type) {
            case ARRAY_LIST:
                l->s.array_list = new_array_list(l->type_manifest);
                if(l->s.array_list)
                    return l->s.array_list->d->append(l->s.array_list, data);
                return 0;

            case LINKED_LIST:
                return (l->s.linked_list = new_linked_list(data, l->type_manifest)) != NULL;

            case CIRCULAR_LINKED_LIST:
                return (l->s.circular_linked_list = new_circular_linked_list(data, l->type_manifest)) != NULL;

            case DOUBLE_LINKED_LIST:
                return (l->s.double_linked_list = new_double_linked_list(data, l->type_manifest)) != NULL;

            case CIRCULAR_DOUBLE_LINKED_LIST:
                return (l->s.circular_double_linked_list = new_circular_double_linked_list(data, l->type_manifest)) != NULL;

            default:
                return 0;
        }
    }
    return 0;
}

int list_is_empty(const List *l){
    if(!l) return 1;
    switch (l->type) {
        case ARRAY_LIST:

            if(l->s.array_list == NULL)
                return 1;
            else if(l->s.array_list->count == 0)
                return 1;
            else
                return 0;

        case LINKED_LIST:
            return l->s.linked_list == NULL;

        case CIRCULAR_LINKED_LIST:
            return l->s.circular_linked_list == NULL;

        case DOUBLE_LINKED_LIST:
            return l->s.double_linked_list == NULL;

        case CIRCULAR_DOUBLE_LINKED_LIST:
            return l->s.circular_double_linked_list == NULL;

        default:
            return 1;
    }
}

int list_append(List *l, const void *data){
    if(!l) return 0;
    if(l->check_init_(l, data))
        return 1;
    switch (l->type) {
        case ARRAY_LIST:
            return l->s.array_list->d->append(l->s.array_list, data);

        case LINKED_LIST:
            return l->s.linked_list->d->append(&l->s.linked_list, data);

        case CIRCULAR_LINKED_LIST:
            return l->s.circular_linked_list->d->append(&l->s.circular_linked_list, data);

        case DOUBLE_LINKED_LIST:
            return l->s.double_linked_list->d->append(&l->s.double_linked_list, data);

        case CIRCULAR_DOUBLE_LINKED_LIST:
            return l->s.circular_double_linked_list->d->append(&l->s.circular_double_linked_list, data);
    }
    return 0;
}

void * list_head_peek(const List *l){
    if(!l) return 0;
    switch (l->type) {
        case ARRAY_LIST:
            if(l->s.array_list->count)
            return l->s.array_list->array[0];

        case LINKED_LIST:
            return l->s.linked_list->data;

        case CIRCULAR_LINKED_LIST:
            return l->s.circular_linked_list->data;

        case DOUBLE_LINKED_LIST:
            return l->s.double_linked_list->data;

        case CIRCULAR_DOUBLE_LINKED_LIST:
            return l->s.circular_double_linked_list->data;
    }
    return NULL;
}

void * list_tail_peek(const List *l){
    if(!l) return 0;
    switch (l->type) {
        case ARRAY_LIST:
            if(l->s.array_list->count)
                return l->s.array_list->array[l->s.array_list->count - 1];

        case LINKED_LIST:
            assert(1 == 0);
            return l->s.linked_list;

        case CIRCULAR_LINKED_LIST:
            assert(1 == 0);
            return l->s.circular_linked_list;

        case DOUBLE_LINKED_LIST:
            assert(1 == 0);
            return l->s.double_linked_list;

        case CIRCULAR_DOUBLE_LINKED_LIST:
            return l->s.circular_double_linked_list->prev;
    }
    return NULL;
}


int list_prepend(List *l, const void *data){
    if(!l) return 0;
    if(l->check_init_(l, data))
        return 1;
    switch (l->type) {
        case ARRAY_LIST:
            return l->s.array_list->d->insert(l->s.array_list, 0, data);

        case LINKED_LIST:
            return l->s.linked_list->d->prepend(&l->s.linked_list, data);

        case CIRCULAR_LINKED_LIST:
            return l->s.circular_linked_list->d->prepend(&l->s.circular_linked_list, data);

        case DOUBLE_LINKED_LIST:
            return l->s.double_linked_list->d->prepend(&l->s.double_linked_list, data);

        case CIRCULAR_DOUBLE_LINKED_LIST:
            return l->s.circular_double_linked_list->d->prepend(&l->s.circular_double_linked_list, data);
    }
    return 0;
}

void * list_pop(List *l){
    if(!list_is_empty(l)) return NULL;
    switch (l->type) {
        case ARRAY_LIST:
            return l->s.array_list->d->pop(l->s.array_list);

        case LINKED_LIST:
            return l->s.linked_list->d->pop(&l->s.linked_list);

        case CIRCULAR_LINKED_LIST:
            return l->s.circular_linked_list->d->pop(&l->s.circular_linked_list);

        case DOUBLE_LINKED_LIST:
            return l->s.double_linked_list->d->pop(&l->s.double_linked_list);

        case CIRCULAR_DOUBLE_LINKED_LIST:
            return l->s.circular_double_linked_list->d->pop(&l->s.circular_double_linked_list);

            default:
            return NULL;
    }
}

void * list_shift(List *l){
    if(!list_is_empty(l)) return NULL;
    switch (l->type) {
        case ARRAY_LIST:
            return l->s.array_list->d->pop_i(l->s.array_list, 0);

        case LINKED_LIST:
            return l->s.linked_list->d->shift(&l->s.linked_list);

        case CIRCULAR_LINKED_LIST:
            return l->s.circular_linked_list->d->shift(&l->s.circular_linked_list);

        case DOUBLE_LINKED_LIST:
            return l->s.double_linked_list->d->shift(&l->s.double_linked_list);

        case CIRCULAR_DOUBLE_LINKED_LIST:
            return l->s.circular_double_linked_list->d->shift(&l->s.circular_double_linked_list);

        default:
            return NULL;
    }
}

void list_free(List **l){
    if(!*l) return;
    if((*l)->is_empty(*l)) {
        free(*l);
        *l = NULL;
        return;
    }
    switch ((*l)->type) {
        case ARRAY_LIST:
            (*l)->s.array_list->d->free(&(*l)->s.array_list);
            break;

        case LINKED_LIST:
            (*l)->s.linked_list->d->free(&(*l)->s.linked_list);
            break;

        case CIRCULAR_LINKED_LIST:
            (*l)->s.circular_linked_list->d->free(&(*l)->s.circular_linked_list);
            break;

        case DOUBLE_LINKED_LIST:
            (*l)->s.double_linked_list->d->free(&(*l)->s.double_linked_list);
            break;

        case CIRCULAR_DOUBLE_LINKED_LIST:
            (*l)->s.circular_double_linked_list->d->free(&(*l)->s.circular_double_linked_list);
            break;
    }
    free(*l);
    *l = NULL;
}

void list_print (const List *l){
    if(!l) return;
    l->fprint(stdout, l);
}

void list_fprint (FILE * stream, const List *l){
    if(!l) return;
    switch (l->type) {
        case ARRAY_LIST:
            l->s.array_list->d->fprint(stream, l->s.array_list);
            break;

        case LINKED_LIST:
            l->s.linked_list->d->fprint(stream, l->s.linked_list);
            break;

        case CIRCULAR_LINKED_LIST:
            l->s.circular_linked_list->d->fprint(stream, l->s.circular_linked_list);
            break;

        case DOUBLE_LINKED_LIST:
            l->s.double_linked_list->d->fprint(stream, l->s.double_linked_list);
            break;

        case CIRCULAR_DOUBLE_LINKED_LIST:
            l->s.circular_double_linked_list->d->fprint(stream, l->s.circular_double_linked_list);
            break;
    }
}




/*


switch (type) {
    case ARRAY_LIST:

        break;
    case LINKED_LIST:

        break;
    case CIRCULAR_LINKED_LIST:

        break;
    case DOUBLE_LINKED_LIST:

        break;
    case CIRCULAR_DOUBLE_LINKED_LIST:

        break;

    default:
        return NULL;
}



*/
