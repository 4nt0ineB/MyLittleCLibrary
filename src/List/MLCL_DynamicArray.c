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

#include "../../include/List/MLCL_DynamicArray.h"
#include <assert.h>

ArrayListDescriptor * array_list_descriptor(){
    ArrayListDescriptor * al_d;
    ll_descriptor = (LinkedListDescriptor *) malloc(sizeof(LinkedListDescriptor));
    if(!ll_descriptor) return NULL;
    /*ll_descriptor->add = linked_list_add_;*/
    /*al_d->ordered_add = linked_list_ordered_add;
    al_d->reverse_ordered_add = linked_list_reverse_ordered_add;
    al_d->append = linked_list_append;
    al_d->prepend = linked_list_prepend;
    al_d->insert = linked_list_insert;
    al_d->search = linked_list_search;
    al_d->remove = linked_list_remove;
    al_d->shift = linked_list_shift;
    al_d->pop = linked_list_pop;*/
    al_d->append = array_list_append;
    al_d->print_at = array_list_print_at;
    al_d->print = array_list_print;
    al_d->fprint_at = array_list_fprint_at;
    al_d->fprint = array_list_fprint;
    al_d->free = linked_list_free;
    /*al_d->cell_free = linked_list_cell_free;

    al_d->to_dot = linked_list_to_dot;*/
    /* Held type */
    al_d->type_descriptor = NULL;
    return al_d;
}

ArrayList * array_list_builder(ArrayListDescriptor * descriptor){
    ArrayList * al;
    assert(descriptor);
    if(!(al = (ArrayList *) malloc(sizeof(ArrayList))))
        return NULL;
    al->array = (void **) calloc(ARRAY_LIST_BLOCK_SIZE, sizeof(void *));
    al->count = ARRAY_LIST_BLOCK_SIZE;
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

/*static array_list_make_space(ArrayList * l, int n){

}*/

int array_list_apppend(ArrayList * l, const void * data){
    if(!l) return 0;

    if(!data) return 0;
}

void array_list_print_at(ArrayList l, int i) {
    l->d->fprint_at(l, i);
}

void array_list_fprint_at(ArrayList l, int i) {
    if(i < 0 || i >= l->count)
        return;
    l->d->type_descriptor->fprint(file, l.array[i]);
}

void array_list_print(ArrayList l){
    l->d->fprint(stdout, l);
}

void array_list_fprint(FILE * file, ArrayList l){
    int i;
    fprintf(file, "[");
    for(i = 0; i < l->d->size - 1; i++){
        l->d->type_descriptor->fprint(file, l.array[i]);fprintf(file, ", ");
    }
    l->d->type_descriptor->fprintfile, l.array[i]);
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
                (*l)->d->type_descriptor->free(&(*l)->array[i]);
        }
    }
    if((*l)->d->type_descriptor)
        array_list_free_descriptor(&(*l)->d);
    free(*l);
    *l = NULL;
}