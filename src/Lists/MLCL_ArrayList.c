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

#include "../../include/Lists/MLCL_ArrayList.h"
#include <assert.h>
#include <string.h>

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
    */

    ald->append = array_list_append;
    ald->insert = array_list_insert;
    ald->assign_i = array_list_assign_i;
    ald->pop = array_list_pop;
    ald->pop_i = array_list_pop_i;
    ald->search = array_list_search;
    ald->binary_search = array_list_binary_search;
    /* Sort */
    ald->is_sorted = array_list_is_sorted;
    ald->bublle_sort = array_list_bublle_sort;
    ald->selection_sort = array_list_selection_sort;
    ald->insertion_sort = array_list_insertion_sort;
    ald->quick_sort = array_list_quick_sort;
    ald->merge_sort = array_list_merge_sort;
    ald->make_space = array_list_make_space;
    ald->update_space = array_list_update_space;
    /* Print */
    ald->print_i = array_list_print_i;
    ald->print = array_list_print;
    ald->fprint_i = array_list_fprint_i;
    ald->fprint = array_list_fprint;
    ald->to_dot_ = array_list_to_dot_;
    ald->to_dot = array_list_to_dot;
    ald->free = array_list_free;

    /* al_d->to_dot = linked_list_to_dot; */
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

int array_list_make_space(ArrayList *l){
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

int array_list_update_space(ArrayList *l){
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
}

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

int array_list_insert(ArrayList *l, int i, const void * data){
    int j;
    if(!l) return 0;
    l->d->make_space(l);
    l->count++;
    for(j = l->count; j > i; j--){
        l->array[j] = l->array[j - 1];
    }
    l->array[i] = l->d->type_descriptor->copy(data);
    return 1;
}

int array_list_assign_i(ArrayList *l, int i, const void * data){
    if(!l) return 0;
    if(i < 0 || i > l->count) return 0;
    if(!array_list_make_space(l)) {
        return 0;
    }
    if(i == l->count){
        l->array[i] = l->d->type_descriptor->copy(data);
        l->count++;
    }else{
        l->d->type_descriptor->free_data(l->array[i]);
        l->array[i] = l->d->type_descriptor->copy(data);
    }
    return 1;
}

void * array_list_pop_i(ArrayList *l, int index){
    int i;
    void * tmp;
    if(!l) return NULL;
    if(l->count <= 0) return NULL;
    tmp = l->array[index];
    for(i = index; i < l->count - 1; i++){
        l->array[i] = l->array[i + 1];
    }
    l->count--;
    array_list_update_space(l);
    return tmp;
}

void * array_list_pop(ArrayList *l){
    void * tmp;
    if(!l) return NULL;
    if(l->count <= 0) return NULL;
    tmp = l->array[l->count - 1];
    l->array[l->count - 1] = NULL;
    l->count--;
    array_list_update_space(l);
    return tmp;
}

/**
 *
 * @param l
 * @param length
 * @param data
 * @param cmp must return -1, 0, 1
 * @param res
 * @return
 */
static int array_list_search_(void **l, int length, const void *data, int (*cmp) (const void *, const void *), int * res){
    int i;
    if(!*l) return 0;
    for(i = 0; i < length; i++){
        if(cmp(data, l[i]) == 0){
            if(res) *res = i;
            return 1;
        }
    }
    return 0;
}

int array_list_search(ArrayList *l, const void *data, int * res){
    if(!l) return -1;
    return array_list_search_(l->array, l->count, data, l->d->type_descriptor->cmp, res);
}


/**
 * @brief
 * @param l
 * @param length
 * @param data
 * @param cmp must return -1, 0, 1
 * @return
 */
static int array_list_binary_search_(void **l, int length, const void *data, int (*cmp) (const void *, const void *), int * res){
    int mid, head1, head2, test, i;
    if(!*l) return 0;
    head1 = 0;
    head2 = length - 1;
    i = 0;
    while(i != 5 && head1 <= head2){
        mid = (head1 + head2) / 2;
        test = cmp(data, l[mid]);
        if(test == 1){
            head1 = mid + 1;
        }else if(test == -1){
            head2 = mid - 1;
        }else{
            if(res) *res = mid;
            return 1;
        }
        i++;
    }
    if(cmp(l[head1], data) == 0){
        if(res) *res = head1;
        return 1;
    }
    return 0;
}

int array_list_binary_search(ArrayList *l, const void *data, int * res){
    if(!l) return -1;
    return array_list_binary_search_(l->array, l->count - 1, data, l->d->type_descriptor->cmp, res);
}

int array_list_is_sorted(const ArrayList *l, int (*cmp) (const void *, const void *)){
    int i;
    if(!l) return 1;
    if(l->count <= 1) return 1;
    for(i = 0; i < l->count - 1; i++)
        if(cmp(l->array[i], l->array[i + 1]) != 1)
            return 0;
    return 1;
}

void array_list_bublle_sort(ArrayList *l, int (*cmp) (const void *, const void *)){
    int i, j;
    void * tmp;
    if(!l) return;
    for(i = 0; i < l->count - 1; i++){
        for(j = l->count - 1; j > i; j--){
            if(cmp(l->array[j], l->array[j - 1]) == 1){
                tmp = l->array[j - 1];
                l->array[j - 1] = l->array[j];
                l->array[j] = tmp;
            }
        }
    }
}

void array_list_insertion_sort(ArrayList *l, int (*cmp) (const void *, const void *)){
    int i, j;
    void * tmp;
    if(!l) return;
    for(i = 0; i < l->count; i++){
        tmp = l->array[i];
        j = i;
        while(j > 0 && cmp(tmp, l->array[j - 1]) == 1){
            l->array[j] = l->array[j - 1];
            j--;
        }
        l->array[j] = tmp;
    }
}

void array_list_selection_sort(ArrayList *l, int (*cmp) (const void *, const void *)){
    int i, i_min;
    int min, j;
    void * tmp;
    if(!l) return;
    for(i = 0; i < l->count - 1; i++){
        i_min = min = i;
        /* Find the index of the min */
        for(j = i_min; j < l->count; j++)
            if(cmp(l->array[j], l->array[min]) == 1)
                i_min = min = j;
        /* Switch values */
        tmp = l->array[i];
        l->array[i] = l->array[i_min];
        l->array[i_min] = tmp;
    }
}

static int partition(void ** l, int start, int end, int (*cmp) (const void *, const void *)){
    int head1, head2;
    void * tmp;

    head1 = start + 1;
    head2 = end;

    while (head1 <= head2){

        while (head1 <= head2 && cmp(l[start], l[head1]) != 1)
            head1++;


        while (cmp(l[start], l[head2]) == 1){
            head2--;
        }

        if(head1 < head2){
            tmp = l[head1];
            l[head1] = l[head2];
            l[head2] = tmp;
            head1 ++;
            head2 --;
        }
    }
    tmp = l[start];
    l[start] = l[head2];
    l[head2] = tmp;
    return head2;
}

void array_list_quick_sort_(void ** l, int start, int end, int (*cmp) (const void *, const void *)){
    int pivot;
    if(!l) return;
    if(start >= end) return;
    /* partition between start and end*/
    pivot = partition(l, start, end, cmp);
    /* Sort between start and pivot */
    array_list_quick_sort_(l, start, pivot - 1, cmp);
    /* Sort between pivot and end */
    array_list_quick_sort_(l, pivot + 1, end, cmp);
}

void array_list_quick_sort(ArrayList *l, int (*cmp) (const void *, const void *)){
    if(!l) return;
    array_list_quick_sort_(l->array, 0, l->count - 1, cmp);
}


static void _array_list_merge_sort_merge(void ** l, int start, int mid, int end, int (*cmp) (const void *, const void *)){
    void ** tmp_array;
    int head1, head2, i_tmp;

    if(!*l) return;

    tmp_array = (void **) malloc((end - start + 1) * sizeof(void *));
    if(!tmp_array) return;
    head1 = start;
    head2 = mid + 1;
    i_tmp = 0;


    /* Sorted copy while no part is empty */
    while(head1 <= mid && head2 <= end){
        if(cmp(l[head1], l[head2])){
            tmp_array[i_tmp] = l[head1];
            head1++;
        }else{
            tmp_array[i_tmp] = l[head2];
            head2++;
        }
        i_tmp++;
    }

    /* Copy remaining values */
    if(head1 > mid){
        while(head2 <= end){
           tmp_array[i_tmp] = l[head2];
           head2++;
           i_tmp++;
        }
    }else{
        while(head1 <= mid){
            tmp_array[i_tmp] = l[head1];
            head1++;
            i_tmp++;
        }
    }

    memcpy(l + start, tmp_array, sizeof(void *) * (end - start + 1));
    free(tmp_array);
}

static void _array_list_merge_sort(void ** l, int start, int end, int (*cmp) (const void *, const void *)){
    int mid;
    if(!l) return;
    if(start >= end) return;
    mid = (start + end) / 2;
    _array_list_merge_sort(l, start, mid - 1, cmp);
    _array_list_merge_sort(l, mid + 1, end, cmp);
    _array_list_merge_sort_merge(l, start, mid, end, cmp);
}

void array_list_merge_sort(ArrayList *l, int (*cmp) (const void *, const void *)){
    _array_list_merge_sort(l->array, 0, l->count - 1, cmp);
}

void array_list_print_i(const ArrayList  *l, int i) {
    l->d->fprint_i(stdout, l, i);
}

void array_list_fprint_i(FILE * stream, const ArrayList  *l, int i) {
    if(i < 0 || i >= l->count)
        return;
    l->d->type_descriptor->fprint(stream, l->array[i]);
}

void array_list_print(const ArrayList  *l){
    l->d->fprint(stdout, l);
}

void array_list_fprint(FILE * stream, const ArrayList * l){
    int i;
    if(!l) return;
    if(l->count <= 0) return;
    for(i = 0; i < l->count - 1; i++){
        l->d->type_descriptor->fprint(stream, l->array[i]);fprintf(stream, "%s", l->d->type_descriptor->separator);
    }
    l->d->type_descriptor->fprint(stream, l->array[i]);
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


void array_list_to_dot_(const ArrayList *l, FILE * stream){
    int i;
    if(!stream || !l) return;
    fprintf(stream, "digraph {\n"
            "\n"
            "    node [shape=record, fontcolor=black, fontsize=14, width=4.75, fixedsize=true];\n");
    fprintf(stream, "  values [label=\"");
    for(i = 0; i < l->count - 1; i++){
        array_list_fprint_i(stream, l, i);
        fprintf(stream, " | ");
    }
    array_list_fprint_i(stream, l, l->count - 1);
    fprintf(stream, "\"];\n}");
}

void array_list_to_dot(const ArrayList *l, const char * path){
    FILE * file;
    if(!path) return;
    if(!(file = fopen(path, "w")))
        return;
    array_list_to_dot_(l, file);
    fclose(file);
}
