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

#include "../../include/List/MLCL_ArrayList.h"
#include <assert.h>

ArrayListDescriptor * array_list_descriptor(){
    ArrayListDescriptor * ald;
    ald = (ArrayListDescriptor *) malloc(sizeof(ArrayListDescriptor));
    if(!ald) return NULL;
    /*ll_descriptor->add = linked_list_add_;*/
    /*al_d->ordered_add = linked_list_ordered_add;
    ald->reverse_ordered_add = linked_list_reverse_ordered_add;
    ald->append = linked_list_append;
    ald->prepend = linked_list_prepend;
    ald->insert = linked_list_insert;
    ald->search = linked_list_search;
    ald->remove = linked_list_remove;
    ald->shift = linked_list_shift;
    ald->pop = linked_list_pop;*/
    ald->append = array_list_append;
    ald->print_at = array_list_print_at;
    ald->print = array_list_print;
    ald->fprint_at = array_list_fprint_at;
    ald->fprint = array_list_fprint;
    ald->free = array_list_free;
    /*al_d->cell_free = linked_list_cell_free;

    al_d->to_dot = linked_list_to_dot;*/
    /* Held type */
    ald->type_descriptor = NULL;
    return ald;
}

ArrayList * array_list_builder(ArrayListDescriptor * descriptor){
    ArrayList * al;
    assert(descriptor);
    if(!(al = (ArrayList *) malloc(sizeof(ArrayList))))
        return NULL;
    al->array = (void **) calloc(ARRAY_LIST_BLOCK_SIZE, sizeof(void *));
    al->count = 0;
    al->size = ARRAY_LIST_BLOCK_SIZE;
    al->d = descriptor;
    return al;
}

ArrayList * new_array_list(void (*type_manifest) (TypeDescriptor *)){
    ArrayListDescriptor * ald;
    assert(type_manifest);
    if(!(ald = array_list_descriptor()))
        return NULL;
    if(!(ald->type_descriptor = new_type_descriptor(type_manifest)))
        return NULL;
    return array_list_builder(ald);
}

static int array_list_make_space(ArrayList *l){
    if(!l) return 0;
    if(l->size == l->count){
        void ** tmp;
        tmp = (void **) realloc(l->array,
                                (l->size + ARRAY_LIST_BLOCK_SIZE) * sizeof(void *));
        if(!tmp) return 0;
        l->size += ARRAY_LIST_BLOCK_SIZE;
        l->array = tmp;
    }
    return 1;
}

/*static int array_list_update_space(ArrayList *l){
    int n_blocks;
    if(!l) return 0;
    n_blocks = l->count / ARRAY_LIST_BLOCK_SIZE;
    if(l->count % ARRAY_LIST_BLOCK_SIZE != 0) n_blocks++;
    if((l->size / ARRAY_LIST_BLOCK_SIZE) - n_blocks >= ARRAY_LIST_MAX_EMPTY_BLOCKS){
        int new_size;
        void ** tmp;
        new_size = n_blocks * ARRAY_LIST_BLOCK_SIZE + ARRAY_LIST_BLOCK_SIZE;
        if(!(tmp = (void **) realloc(l->array, new_size * sizeof(void *))))
            return 0;
        l->size = new_size;
        l->array = tmp;
    }
    return 1;
}*/

int array_list_append(ArrayList *l, const void * data){
    if(!l) return 0;
    if(!array_list_make_space(l)) {
        return 0;
    }
    l->array[l->count] = l->d->type_descriptor->copy(data);
    l->count++;
    if(!data && !l->array[l->count]) return 0;
    return 1;
}

void array_list_print_at(const ArrayList  *l, int i) {
    l->d->fprint_at(stdout, l, i);
}

void array_list_fprint_at(FILE * file, const ArrayList  *l, int i) {
    if(i < 0 || i >= l->count)
        return;
    l->d->type_descriptor->fprint(file, l->array[i]);
}

void array_list_print(const ArrayList  *l){
    l->d->fprint(stdout, l);
}

void array_list_fprint(FILE * file, const ArrayList * l){
    int i;
    fprintf(file, "[");
    for(i = 0; i < l->count - 1; i++){
        l->d->type_descriptor->fprint(file, l->array[i]);fprintf(file, ", ");
    }
    l->d->type_descriptor->fprint(file, l->array[i]);
    fprintf(file, "]");
}

void array_list_free_descriptor(ArrayListDescriptor ** ald){
    if(!*ald) return;
    if((*ald)->type_descriptor)
        type_descriptor_free(&(*ald)->type_descriptor);
    free(*ald);
    *ald = NULL;
}

void array_list_free(ArrayList ** l){
    int i;
    if(!*l) return;
    if((*l)->array){
        for (i = 0; i < (*l)->count; ++i) {
            if((*l)->array[i])
                (*l)->d->type_descriptor->free_data(&(*l)->array[i]);
        }
    }
    free((*l)->array);
    if((*l)->d->type_descriptor)
        array_list_free_descriptor(&(*l)->d);
    free(*l);
    *l = NULL;
}