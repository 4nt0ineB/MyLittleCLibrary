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

#include "../../../include/data-structures/Lists/MLCL_List.h"
#include "../../../include/core/MLCL_TypeDescriptor.h"
#include <string.h>


List * new_list(LIST_TYPE list_type, void (*type_manifest) (TypeDescriptor *)){
    List *list;

    if(!(list = (List *) calloc(1, sizeof (List))))
        return NULL;

    list->type = list_type;
    list->type_manifest = type_manifest;

    list->prefix = '[';
    list->suffix = ']';

    switch (list->type) {
        case ARRAY_LIST:
            list->s.array_list = new_array_list(list->type_manifest);
            break;

        case LINKED_LIST:
            list->s.linked_list = new_linked_list(list->type_manifest);
            break;

        case CIRCULAR_LINKED_LIST:
            list->s.circular_linked_list = new_circular_linked_list(list->type_manifest);
            break;

        case DOUBLE_LINKED_LIST:
            list->s.double_linked_list = new_double_linked_list(list->type_manifest);
            break;

        case CIRCULAR_DOUBLE_LINKED_LIST:
            list->s.circular_double_linked_list = new_circular_double_linked_list(list->type_manifest);
            break;

        default:
            list_free(&list);
    }

    return list;
}

int list_length(const List *self){
    if(!self) return 0;
    if(!list_length(self)) return 0;
    switch (self->type) {
        case ARRAY_LIST:
            return self->s.array_list->count;

        case LINKED_LIST:
            return  self->s.linked_list->length;

        case CIRCULAR_LINKED_LIST:
            return self->s.circular_linked_list->length;

        case DOUBLE_LINKED_LIST:
            return self->s.double_linked_list->length;

        case CIRCULAR_DOUBLE_LINKED_LIST:
            return self->s.circular_double_linked_list->length;
    }
    return 0;
}

int list_append(List *self, void *data){
    if(!self) return 0;
    switch (self->type) {
        case ARRAY_LIST:
            return array_list_append(self->s.array_list, data);

        case LINKED_LIST:
            return linked_list_append(self->s.linked_list, data);

        case CIRCULAR_LINKED_LIST:
            return circular_linked_list_append(self->s.circular_linked_list, data);

        case DOUBLE_LINKED_LIST:
            double_linked_list_append(self->s.double_linked_list, data);

        case CIRCULAR_DOUBLE_LINKED_LIST:
            return circular_double_linked_list_append(self->s.circular_double_linked_list, data);
    }
    return 0;
}

void * list_head_peek(const List *self){
    if(!self) return 0;
    switch (self->type) {
        case ARRAY_LIST:
            if(self->s.array_list->count)
            return self->s.array_list->array[0];

        case LINKED_LIST:
            return self->s.linked_list->head->data;

        case CIRCULAR_LINKED_LIST:
            return self->s.circular_linked_list->head->data;

        case DOUBLE_LINKED_LIST:
            return self->s.double_linked_list->head->data;

        case CIRCULAR_DOUBLE_LINKED_LIST:
            return self->s.circular_double_linked_list->head->data;
    }
    return NULL;
}

void * list_tail_peek(const List *self){
    if(!self) return 0;
    switch (self->type) {
        case ARRAY_LIST:
            if(self->s.array_list->count)
                return self->s.array_list->array[self->s.array_list->count - 1];

        case LINKED_LIST:
            assert(1 == 0);
            return self->s.linked_list;

        case CIRCULAR_LINKED_LIST:
            assert(1 == 0);
            return self->s.circular_linked_list;

        case DOUBLE_LINKED_LIST:
            assert(1 == 0);
            return self->s.double_linked_list;

        case CIRCULAR_DOUBLE_LINKED_LIST:
            return self->s.circular_double_linked_list->head->prev;
    }
    return NULL;
}


int list_prepend(List *self, void *data){
    if(!self) return 0;
    switch (self->type) {
        case ARRAY_LIST:
            return array_list_insert(self->s.array_list, 0, data);

        case LINKED_LIST:
            return linked_list_prepend(self->s.linked_list, data);

        case CIRCULAR_LINKED_LIST:
            return circular_linked_list_prepend(self->s.circular_linked_list, data);

        case DOUBLE_LINKED_LIST:
            return double_linked_list_prepend(self->s.double_linked_list, data);

        case CIRCULAR_DOUBLE_LINKED_LIST:
            return circular_double_linked_list_prepend(self->s.circular_double_linked_list, data);
    }
    return 0;
}

void * list_pop(List *self){
    if(!list_length(self)) return NULL;
    switch (self->type) {
        case ARRAY_LIST:
            return array_list_pop(self->s.array_list);

        case LINKED_LIST:
            return linked_list_pop(self->s.linked_list);

        case CIRCULAR_LINKED_LIST:
            return circular_linked_list_pop(self->s.circular_linked_list);

        case DOUBLE_LINKED_LIST:

            return double_linked_list_pop(self->s.double_linked_list);

        case CIRCULAR_DOUBLE_LINKED_LIST:
            return circular_double_linked_list_pop(self->s.circular_double_linked_list);

            default:
            return NULL;
    }
}

void * list_shift(List *self){
    if(!list_length(self)) return NULL;
    switch (self->type) {
        case ARRAY_LIST:
            return array_list_pop_i(self->s.array_list, 0);

        case LINKED_LIST:
            return linked_list_shift(self->s.linked_list);

        case CIRCULAR_LINKED_LIST:
            return circular_linked_list_shift(self->s.circular_linked_list);

        case DOUBLE_LINKED_LIST:
            return double_linked_list_shift(self->s.double_linked_list);

        case CIRCULAR_DOUBLE_LINKED_LIST:
            return circular_double_linked_list_shift(self->s.circular_double_linked_list);

        default:
            return NULL;
    }
}

void list_free(List **self){
    if(!*self) return;
    if(!list_length(*self)) {
        free(*self);
        *self = NULL;
        return;
    }
    switch ((*self)->type) {
        case ARRAY_LIST:
            array_list_free(&(*self)->s.array_list);
            break;

        case LINKED_LIST:
            linked_list_free(&(*self)->s.linked_list);
            break;

        case CIRCULAR_LINKED_LIST:
            circular_linked_list_free(&(*self)->s.circular_linked_list);
            break;

        case DOUBLE_LINKED_LIST:
            double_linked_list_free(&(*self)->s.double_linked_list);
            break;

        case CIRCULAR_DOUBLE_LINKED_LIST:
            circular_double_linked_list_free(&(*self)->s.circular_double_linked_list);
            break;
    }
    free(*self);
    *self = NULL;
}

void list_print(const List *self){
    if(!self) return;
    list_fprint(self, stdout);
}

void list_fprint_join(List *self, FILE *stream, const char separator[MLCL_SEPARATOR_LEN]){
    char seperator_tmp[MLCL_SEPARATOR_LEN];
    char *p_separator;
    char l_pref_tmp, l_suf_tmp;
    if(!self) return;
    switch (self->type) {
        case ARRAY_LIST:
            p_separator = self->s.array_list->separator;
            break;

        case LINKED_LIST:
            p_separator = self->s.linked_list->separator;
            break;

        case CIRCULAR_LINKED_LIST:
            p_separator = self->s.circular_linked_list->separator;

            break;

        case DOUBLE_LINKED_LIST:
            p_separator = self->s.double_linked_list->separator;

            break;

        case CIRCULAR_DOUBLE_LINKED_LIST:
            p_separator = self->s.circular_double_linked_list->separator;

            break;
    }
    l_pref_tmp = self->prefix;
    l_suf_tmp = self->suffix;
    /* Save separator */
    strcpy(seperator_tmp, p_separator);
    /* Write given separator */
    strcpy(p_separator, separator);
    /* Replace list prefix and suffix */
    self->prefix = '\0';
    self->suffix = '\0';
    list_fprint(self, stream);
    /* Restore all */
    strcpy(p_separator, seperator_tmp);
    self->prefix = l_pref_tmp;
    self->suffix = l_suf_tmp;
}

void list_clear(List *self, void (*data_free) (void *)){
    if(!self) return;
    if(!list_length(self)) return;
    switch (self->type) {
        case ARRAY_LIST:
            array_list_empty(self->s.array_list, data_free);
            break;

        case LINKED_LIST:
            linked_list_clear(self->s.linked_list, data_free);
            break;

        case CIRCULAR_LINKED_LIST:
            circular_linked_list_clear(self->s.circular_linked_list, data_free);
            break;

        case DOUBLE_LINKED_LIST:
            double_linked_list_clear(self->s.double_linked_list, data_free);
            break;

        case CIRCULAR_DOUBLE_LINKED_LIST:
            circular_double_linked_list_clear(self->s.circular_double_linked_list, data_free);
            break;
    }
}

void list_fprint(const List *self, FILE * stream){
    if(!self) return;
    if(self->prefix != '\0')
        fprintf(stream, "%c", self->prefix);
    switch (self->type) {
        case ARRAY_LIST:
            array_list_fprint(self->s.array_list, stream);
            break;

        case LINKED_LIST:
            linked_list_fprint(self->s.linked_list, stream);
            break;

        case CIRCULAR_LINKED_LIST:
            circular_linked_list_fprint(self->s.circular_linked_list, stream);
            break;

        case DOUBLE_LINKED_LIST:
            double_linked_list_fprint(self->s.double_linked_list, stream);
            break;

        case CIRCULAR_DOUBLE_LINKED_LIST:
            circular_double_linked_list_fprint(self->s.circular_double_linked_list, stream);
            break;
    }
    if(self->suffix != '\0')
        fprintf(stream, "%c", self->suffix);
}

void list_to_dot(const List *self, const char * path){
    if(!self) return;
    switch (self->type) {
        case ARRAY_LIST:
            array_list_to_dot(self->s.array_list, path);
            break;

        case LINKED_LIST:
            linked_list_to_dot(self->s.linked_list, path);
            break;

        case CIRCULAR_LINKED_LIST:
            circular_linked_list_to_dot(self->s.circular_linked_list, path);
            break;

        case DOUBLE_LINKED_LIST:
            double_linked_list_to_dot(self->s.double_linked_list, path);
            break;

        case CIRCULAR_DOUBLE_LINKED_LIST:
            circular_double_linked_list_to_dot(self->s.circular_double_linked_list, path);
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
