/*
 *   This file is part of the MLCL Library
 *   Copyright 2022 Antoine Bastos
 *   SPDX-License-Identifier: Apache-2.0
 */

#include "../../../include/data-structures/Lists/MLCL_ArrayList.h"
#include <assert.h>
#include <string.h>

ArrayList * new_array_list(void (*type_manifest) (TypeDescriptor *)){
    ArrayList * list;
    if(!type_manifest) return NULL;
    list = (ArrayList *) malloc(sizeof(ArrayList));
    if(!list) return NULL;
    list->array = (void **) calloc(ARRAY_LIST_BLOCK_SIZE, sizeof(void *));
    list->count = 0;
    list->size = ARRAY_LIST_BLOCK_SIZE;
    strcpy(list->separator, ", ");
    list->td = new_type_descriptor(type_manifest);
    if(!list->td){
        array_list_free(&list);
    }
    return list;
}

int array_list_make_space(ArrayList *self){
    if(!self) return 0;
    if(self->size == self->count){
        void ** tmp;
        tmp = (void **) realloc(self->array,
                                (self->size + ARRAY_LIST_BLOCK_SIZE) * sizeof(void *));
        if(!tmp) return 0;
        self->size += ARRAY_LIST_BLOCK_SIZE;
        self->array = tmp;
    }
    return 1;
}

int array_list_update_space(ArrayList *self){
    int n_blocks;
    if(!self) return 0;
    n_blocks = self->count / ARRAY_LIST_BLOCK_SIZE;
    if(self->count % ARRAY_LIST_BLOCK_SIZE != 0) n_blocks++;
    if((self->size / ARRAY_LIST_BLOCK_SIZE) - n_blocks >= ARRAY_LIST_MAX_EMPTY_BLOCKS){
        int new_size;
        void ** tmp;
        new_size = n_blocks * ARRAY_LIST_BLOCK_SIZE + ARRAY_LIST_BLOCK_SIZE;
        if(!(tmp = (void **) realloc(self->array, new_size * sizeof(void *))))
            return 0;
        self->size = new_size;
        self->array = tmp;
    }
    return 1;
}

int array_list_append(ArrayList *self, void *data){
    if(!self) return 0;
    if(!array_list_make_space(self)) {
        return 0;
    }
    self->array[self->count] = data;
    self->count++;
    if(!data && !self->array[self->count]) return 0;
    return 1;
}

int array_list_insert(ArrayList *self, int i, void *data){
    int j;
    if(!self) return 0;
    array_list_make_space(self);
    self->count++;
    for(j = self->count; j > i; j--){
        self->array[j] = self->array[j - 1];
    }
    self->array[i] = data;
    return 1;
}

int array_list_assign_i(ArrayList *self, int i, void *data){
    if(!self) return 0;
    if(i < 0 || i > self->count) return 0;
    if(!array_list_make_space(self)) {
        return 0;
    }
    if(i == self->count){
        self->array[i] = data;
        self->count++;
    }else{
        self->td->data_free(self->array[i]);
        self->array[i] = data;
    }
    return 1;
}

void * array_list_pop_i(ArrayList *self, int index){
    int i;
    void * tmp;
    if(!self) return NULL;
    if(self->count <= 0) return NULL;
    tmp = self->array[index];
    for(i = index; i < self->count - 1; i++){
        self->array[i] = self->array[i + 1];
    }
    self->count--;
    array_list_update_space(self);
    return tmp;
}

void * array_list_pop(ArrayList *self){
    void * tmp;
    if(!self) return NULL;
    if(self->count <= 0) return NULL;
    tmp = self->array[self->count - 1];
    self->array[self->count - 1] = NULL;
    self->count--;
    array_list_update_space(self);
    return tmp;
}

/**
 *
 * @param l
 * @param length
 * @param data
 * @param cmp must return 1 or 0
 * @param res
 * @return
 */
static int array_list_search_(void **l, int length, const void *data, int (*filter) (const void *, const void *), int * r_index){
    int i;
    if(!*l) return 0;
    for(i = 0; i < length; i++){
        if(filter(l[i], data)){
            if(r_index) *r_index = i;
            return 1;
        }
    }
    return 0;
}

int array_list_search(ArrayList *self, const void *data, int (*filter) (const void *, const void *), int *r_index){
    if(!self) return 0;
    return array_list_search_(self->array, self->count, data, filter, r_index);
}


/**
 * @brief
 * @param l
 * @param length
 * @param data
 * @param cmp must return -1, 0, 1
 * @return
 */
static int array_list_binary_search_(void **l, int length, const void *data, int (*cmp) (const void *, const void *), int * r_index){
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
            if(r_index) *r_index = mid;
            return 1;
        }
        i++;
    }
    if(cmp(l[head1], data) == 0){
        if(r_index) *r_index = head1;
        return 1;
    }
    return 0;
}

int array_list_binary_search(ArrayList *self, const void *data, int * r_index){
    if(!self) return 0;
    return array_list_binary_search_(self->array, self->count - 1, data, self->td->cmp, r_index);
}

int array_list_is_sorted(const ArrayList *self, int (*cmp) (const void *, const void *)){
    int i;
    if(!self) return 1;
    if(self->count <= 1) return 1;
    for(i = 0; i < self->count - 1; i++)
        if(cmp(self->array[i], self->array[i + 1]) != 1)
            return 0;
    return 1;
}

void array_list_bublle_sort(ArrayList *self, int (*cmp) (const void *, const void *)){
    int i, j;
    void * tmp;
    if(!self) return;
    for(i = 0; i < self->count - 1; i++){
        for(j = self->count - 1; j > i; j--){
            if(cmp(self->array[j], self->array[j - 1]) == 1){
                tmp = self->array[j - 1];
                self->array[j - 1] = self->array[j];
                self->array[j] = tmp;
            }
        }
    }
}

void array_list_insertion_sort(ArrayList *self, int (*cmp) (const void *, const void *)){
    int i, j;
    void * tmp;
    if(!self) return;
    for(i = 0; i < self->count; i++){
        tmp = self->array[i];
        j = i;
        while(j > 0 && cmp(tmp, self->array[j - 1]) == 1){
            self->array[j] = self->array[j - 1];
            j--;
        }
        self->array[j] = tmp;
    }
}

void array_list_selection_sort(ArrayList *self, int (*cmp) (const void *, const void *)){
    int i, i_min;
    int min, j;
    void * tmp;
    if(!self) return;
    for(i = 0; i < self->count - 1; i++){
        i_min = min = i;
        /* Find the index of the min */
        for(j = i_min; j < self->count; j++)
            if(cmp(self->array[j], self->array[min]) == 1)
                i_min = min = j;
        /* Switch values */
        tmp = self->array[i];
        self->array[i] = self->array[i_min];
        self->array[i_min] = tmp;
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

void array_list_quick_sort(ArrayList *self, int (*cmp) (const void *, const void *)){
    if(!self) return;
    array_list_quick_sort_(self->array, 0, self->count - 1, cmp);
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

void array_list_merge_sort(ArrayList *self, int (*cmp) (const void *, const void *)){
    _array_list_merge_sort(self->array, 0, self->count - 1, cmp);
}

void array_list_print_i(const ArrayList  *self, int i) {
    array_list_fprint_i(self, stdout, i);
}

void array_list_fprint_i(const ArrayList *self, FILE *stream, int i) {
    if(i < 0 || i >= self->count)
        return;
    self->td->fprint(stream, self->array[i]);
}

void array_list_print(const ArrayList  *self){
    array_list_fprint(self, stdout);
}

void array_list_fprint(const ArrayList *self, FILE * stream){
    int i;
    if(!self) return;
    if(self->count <= 0) return;
    for(i = 0; i < self->count - 1; i++){
        self->td->fprint(stream, self->array[i]);
        fprintf(stream, "%s", self->separator);
    }
    self->td->fprint(stream, self->array[i]);
}

void array_list_empty(ArrayList *self, void (*data_free) (void *)){
    int i;
    if(!self) return;
    /* Free the elements */
    if(self->array){
        for (i = 0; i < self->count; ++i) {
            if(self->array[i] && data_free)
                data_free(self->array[i]);
        }
    }
    free(self->array);
    /* Init */
    self->array = (void **) calloc(ARRAY_LIST_BLOCK_SIZE, sizeof(void *));
    self->count = 0;
    self->size = ARRAY_LIST_BLOCK_SIZE;
}

void array_list_free(ArrayList **self){
    if(!*self) return;
    array_list_empty(*self, (*self)->td->data_free);
    type_descriptor_free(&(*self)->td);
    free((*self)->array);
    free(*self);
    *self = NULL;
}

void array_list_to_dot_(const ArrayList *self, FILE *stream){
    int i;
    if(!stream || !self) return;
    fprintf(stream, "digraph {\n"
            "\n"
            "    node [shape=record, fontcolor=black, fontsize=14, width=4.75, fixedsize=true];\n");
    fprintf(stream, "  values [label=\"");
    for(i = 0; i < self->count - 1; i++){
        array_list_fprint_i(self, stream, i);
        fprintf(stream, " | ");
    }
    array_list_fprint_i(self, stream, self->count - 1);
    fprintf(stream, "\"];\n}");
}

void array_list_to_dot(const ArrayList *self, const char *path){
    FILE * file;
    if(!path) return;
    if(!(file = fopen(path, "w")))
        return;
    array_list_to_dot_(self, file);
    fclose(file);
}
