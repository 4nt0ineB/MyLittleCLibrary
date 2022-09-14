/*
 *   This file is part of the MLCL Library
 *   Copyrleft 2022 Antoine Bastos
 *   SPDX-License-Identifier: Apache-2.0
 */

#include "../../../include/data-structures/Heap/MLCL_BinaryHeap.h"
#include <assert.h>

BinaryHeap * new_binary_heap(BINARY_HEAP_ORDER order, void (*type_manifest) (TypeDescriptor *)){
    BinaryHeap * heap;
    heap = (BinaryHeap *) malloc(sizeof(BinaryHeap));
    if(!heap) return NULL;
    heap->type = order;
    heap->list = new_array_list(type_manifest);
    heap->td = new_type_descriptor(type_manifest);
    if(!heap->list || !heap->td){
        binary_heap_free(&heap);
        return NULL;
    }
    return heap;
}

int binary_heap_cmp_data(const BinaryHeap *self, const void * x, const void * y){
    if(!self) return 0;
    switch (self->type) {
        case MIN_HEAP:
            return self->td->cmp(x, y) != 1;
        case MAX_HEAP:
            return self->td->cmp(x, y) != -1;
        default:
            return 0;
    }
}

int array_list_is_heap(const BinaryHeap *self){
    int i;
    if(!self) return 0;
    for(i = 1; i < self->list->count; i++){
        if(binary_heap_cmp_data(self, self->list->array[i], self->list->array[(i - 1) / 2]))
            return 0;
    }
    return 1;
}

int binary_heap_get_child_index(const BinaryHeap *self, int i){
    if((2 * i + 1) >= self->list->count)
        return -1;
    if((2 * i + 2) == self->list->count)
        return 2 * i + 1;
    if(binary_heap_cmp_data(self, self->list->array[2 * i + 2], self->list->array[2 * i + 1]))
        return (2 * i + 2);
    return (2 * i + 1);
}

int binary_heap_swap(BinaryHeap *self, int i, const void *data, char shallow_copy){
    int child;
    if(!self || i > self->list->count) return 0;

    if(i > 0 && !binary_heap_cmp_data(self, self->list->array[(i - 1) / 2], data)) {
        self->list->array[i] = self->list->array[(i - 1) / 2];
        return binary_heap_swap(self, (i - 1) / 2, data, shallow_copy);
    }else{
        child = binary_heap_get_child_index(self, i);
        if(child > -1 && !binary_heap_cmp_data(self, data, self->list->array[child])){
            self->list->array[i] = self->list->array[child];
            return binary_heap_swap(self, child, data, shallow_copy);
        }
    }

    /* we overwrite the data at index */
    if(!shallow_copy)
        self->list->array[i] = (void *) data; /* !  copy ?  !*/
    else
        self->list->array[i] = (void *) data;
    return 1;
}

void binary_heap_add(BinaryHeap *self, const void *data){
    if(!self) return;
    /* We make sure there is enough space */
    if(!array_list_make_space(self->list))
        return;
    if(binary_heap_swap(self, self->list->count, (void *) data, 0))
        self->list->count++; /* increase length */
}

void * binary_heap_pop(BinaryHeap *self){
    void * tmp;
    if(!self) return NULL;
    tmp = self->list->array[0];
    if(binary_heap_swap(self, 0, self->list->array[self->list->count-1], 1)){
        self->list->count--;
        self->list->array[self->list->count] = NULL;
        array_list_update_space(self->list);
    }
    return tmp;
}

void binary_heap_clear(BinaryHeap *self, void (*data_free) (void *)){
    if(!self) return;
    array_list_empty(self->list, data_free);
}

void binary_heap_free(BinaryHeap **self){
    if(!*self) return;
    array_list_free(&(*self)->list);
    binary_heap_clear(*self, (*self)->td->data_free);
    type_descriptor_free(&(*self)->td);
    free(*self);
    *self = NULL;
}
