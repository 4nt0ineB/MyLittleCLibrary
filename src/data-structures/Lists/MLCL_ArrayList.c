/*
 *   This file is part of the MLCL Library
 *   Copyrleft 2022 Antoine Bastos
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
    list->length = 0;
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
    if(self->size == self->length){
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
    n_blocks = self->length / ARRAY_LIST_BLOCK_SIZE;
    if(self->length % ARRAY_LIST_BLOCK_SIZE != 0) n_blocks++;
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
    self->array[self->length] = data;
    self->length++;
    if(!data && !self->array[self->length]) return 0;
    return 1;
}

int array_list_insert(ArrayList *self, int i, void *data){
    int j;
    if(!self) return 0;
    array_list_make_space(self);
    self->length++;
    for(j = self->length; j > i; j--){
        self->array[j] = self->array[j - 1];
    }
    self->array[i] = data;
    return 1;
}

int array_list_assign_i(ArrayList *self, int i, void *data){
    if(!self) return 0;
    if(i < 0 || i > self->length) return 0;
    if(!array_list_make_space(self)) {
        return 0;
    }
    if(i == self->length){
        self->array[i] = data;
        self->length++;
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
    if(self->length <= 0) return NULL;
    tmp = self->array[index];
    for(i = index; i < self->length - 1; i++){
        self->array[i] = self->array[i + 1];
    }
    self->length--;
    array_list_update_space(self);
    return tmp;
}

void * array_list_pop(ArrayList *self){
    void * tmp;
    if(!self) return NULL;
    if(self->length <= 0) return NULL;
    tmp = self->array[self->length - 1];
    self->array[self->length - 1] = NULL;
    self->length--;
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
static int array_list_search_(void **array, int length, Filter *filter, int * r_index){
    int i;
    if(!*array || !filter) return 0;
    for(i = 0; i < length; i++){
        if(filter_evaluate(filter, array[i])){
            if(r_index) *r_index = i;
            return 1;
        }
    }
    return 0;
}

int array_list_search(ArrayList *self, Filter *filter, int *r_index){
    if(!self) return 0;
    return array_list_search_(self->array, self->length, filter, r_index);
}

static int array_list_search_all_(void **array, int length, Filter *filter, ArrayList *r_list){
    int i, n;
    if(!*array) return 0;
    n = 0;
    for(i = 0; i < length; i++){
        if(filter_evaluate(filter, array[i])){
            array_list_append(r_list, new_int(i));
            n++;
        }
    }
    return n;
}

ArrayList * array_list_search_all(ArrayList *self, Filter *filter){
    ArrayList *list_of_index;
    if(!self || !filter) return NULL;
    list_of_index = new_array_list(self->td->manifest);
    if(!list_of_index) return NULL;
    array_list_search_all_(self->array, self->length, filter, list_of_index);
    if(list_of_index->length == 0)
        array_list_free(&list_of_index);
    return list_of_index;
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
    int mid, head1, head2, test;
    if(!*l) return 0;
    head1 = 0;
    head2 = length - 1;
    while(head1 <= head2){
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
    }
    if(cmp(l[head1], data) == 0){
        if(r_index) *r_index = head1;
        return 1;
    }
    return 0;
}

int array_list_binary_search(ArrayList *self, const void *data, int * r_index){
    if(!self) return 0;
    return array_list_binary_search_(self->array, self->length - 1, data, self->td->cmp, r_index);
}

void * array_list_extract(ArrayList *self, Filter *filter){
    int i;
    if(!self || !filter) return NULL;
    for(i = 0; i < self->length; i++)
        if(filter->evaluate(filter, self->array[i]))
            return array_list_pop_i(self, i);
    return NULL;
}

ArrayList * array_list_extract_all(ArrayList *self, Filter *filter){
    ArrayList *filtered_data;
    int i;
    if(!self || !filter) return NULL;
    filtered_data = new_array_list(self->td->manifest);
    /* On all data, evaluate the filter,
     if it doesn't pass, extract it with pop_i then add it to the list */
    for(i = 0; i < self->length; i++)
        if(filter->evaluate(filter, self->array[i])){
            array_list_append(filtered_data, array_list_pop_i(self, i));
            /* we just removed a data, so we decrement
             the iterator because we don't want to miss the next data
             that just shifted to the current index */
            i--;
        }
    if(filtered_data->length == 0)
        array_list_free(&filtered_data);
    return filtered_data;
}

int array_list_remove_w(ArrayList *self, Filter *filter, void (*data_free) (void *)){
    void *data;
    if(!self || !filter) return 0;
    data = array_list_extract(self, filter);
    if(data){
        if(data_free) data_free(data);
        return 1;
    }
    return 0;
}
int array_list_remove(ArrayList *self, Filter *filter){
    return array_list_remove_w(self, filter, self->td->data_free);
}
int array_list_remove_all_w(ArrayList *self, Filter *filter, void (*data_free) (void *)) {
    int n = 0;
    ArrayList *filtered_data;
    if (!self || !filter) return n;
    filtered_data = array_list_extract_all(self, filter);
    if (filtered_data){
        n = filtered_data->length;
        if(data_free)
            array_list_free_w(&filtered_data, data_free);
    }
    return n;
}
int array_list_remove_all(ArrayList *self, Filter *filter){
    return array_list_remove_all_w(self, filter, self->td->data_free);
}

int array_list_is_sorted(const ArrayList *self, int (*cmp) (const void *, const void *)){
    int i;
    if(!self) return 1;
    if(self->length <= 1) return 1;
    for(i = 0; i < self->length - 1; i++)
        if(cmp(self->array[i], self->array[i + 1]) != 1)
            return 0;
    return 1;
}

void array_list_bubble_sort(ArrayList *self, int (*cmp) (const void *, const void *)){
    int i, j;
    void * tmp;
    if(!self) return;
    for(i = 0; i < self->length - 1; i++){
        for(j = self->length - 1; j > i; j--){
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
    for(i = 0; i < self->length; i++){
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
    for(i = 0; i < self->length - 1; i++){
        i_min = min = i;
        /* Find the index of the min */
        for(j = i_min; j < self->length; j++)
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
            head1++;
            head2--;
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
    array_list_quick_sort_(self->array, 0, self->length - 1, cmp);
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

static void _array_list_merge_sort(void **l, int start, int end, int (*cmp) (const void *, const void *)){
    int mid;

    if(!l) return;
    if(start >= end) return;
    mid = (start + end) / 2;

    _array_list_merge_sort(l, start, mid, cmp);
    _array_list_merge_sort(l, mid + 1, end, cmp);


    _array_list_merge_sort_merge(l, start, mid, end, cmp);

}

void array_list_merge_sort(ArrayList *self, int (*cmp) (const void *, const void *)){
    _array_list_merge_sort(self->array, 0, self->length - 1, cmp);
}

void array_list_print_i(const ArrayList  *self, int i) {
    array_list_fprint_i(self, stdout, i);
}

void array_list_fprint_i(const ArrayList *self, FILE *stream, int i) {
    if(i < 0 || i >= self->length)
        return;
    self->td->fprint(self->array[i], stream);
}

void array_list_print(const ArrayList  *self){
    array_list_fprint(self, stdout);
}

void array_list_fprint(const ArrayList *self, FILE *stream){
    int i;
    if(!self) return;
    if(self->length <= 0) return;
    for(i = 0; i < self->length - 1; i++){
        self->td->fprint(self->array[i], stream);
        fprintf(stream, "%s", self->separator);
    }
    self->td->fprint(self->array[i], stream);
}

void array_list_empty(ArrayList *self, void (*data_free) (void *)){
    int i;
    if(!self) return;
    /* Free the elements */
    if(data_free){
        if(self->array && self->length){
            for (i = 0; i < self->length; ++i) {
                if(self->array[i])
                    data_free(self->array[i]);
            }
        }
    }
    free(self->array);
    /* Init */
    self->array = (void **) calloc(ARRAY_LIST_BLOCK_SIZE, sizeof(void *));
    self->length = 0;
    self->size = ARRAY_LIST_BLOCK_SIZE;
}

void array_list_free_w(ArrayList **self, void (*data_free) (void *)){
    if(!*self) return;
    array_list_empty(*self, (*self)->td->data_free);
    type_descriptor_free(&(*self)->td);
    free((*self)->array);
    free(*self);
    *self = NULL;
}

void array_list_free(ArrayList **self){
    if(!*self) return;
    array_list_free_w(self, (*self)->td->data_free);
}

void array_list_to_dot_(const ArrayList *self, FILE *stream){
    int i;
    if(!stream || !self) return;
    fprintf(stream, "digraph {\n"
            "\n"
            "    node [shape=record, fontcolor=black, fontsize=14, width=4.75, fixedsize=true];\n");
    fprintf(stream, "  values [label=\"");
    for(i = 0; i < self->length - 1; i++){
        array_list_fprint_i(self, stream, i);
        fprintf(stream, " | ");
    }
    array_list_fprint_i(self, stream, self->length - 1);
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
