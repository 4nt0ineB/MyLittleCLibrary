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

#include "../../include/Heap/MLCL_BinaryHeap.h"
#include <assert.h>

BinaryHeap * binary_heap_builder(BINARY_HEAP_ORDER order, BinaryHeapDescriptor * descriptor){
    BinaryHeap * h;
    assert(descriptor);
    if(!(h = (BinaryHeap *) malloc(sizeof(BinaryHeap))))
        return NULL;
    h->type = order;
    if(!(h->l = new_array_list(descriptor->type_descriptor->manifest))){
        binary_heap_free(&h);
        return NULL;
    }
    h->d = descriptor;
    return h;
}

BinaryHeapDescriptor * binary_heap_descriptor(){
    BinaryHeapDescriptor * bhd;
    bhd = (BinaryHeapDescriptor *) malloc(sizeof(BinaryHeapDescriptor));
    if(!bhd) return NULL;
    /* methods */
    bhd->cmp_data = binary_heap_cmp_data;
    bhd->free = binary_heap_free;
    return bhd;
}

BinaryHeap * new_binary_heap(BINARY_HEAP_ORDER order, void (*type_manifest) (TypeDescriptor *)){
    BinaryHeapDescriptor * bhd;
    assert(type_manifest);
    if(!(bhd = binary_heap_descriptor()))
        return NULL;
    if(!(bhd->type_descriptor = new_type_descriptor(type_manifest)))
        return NULL;
    return binary_heap_builder(order, bhd);
}

int binary_heap_cmp_data(const BinaryHeap *h, const void * x, const void * y){
    if(!h) return 0;
    switch (h->type) {
        case MIN_HEAP:
            return h->l->d->type_descriptor->cmp(x, y) != 1;
        case MAX_HEAP:
            return h->l->d->type_descriptor->cmp(x, y) != -1;
        default:
            return 0;
    }
}

int array_list_is_heap(const BinaryHeap *h){
    int i;
    if(!h) return 0;
    for(i = 1; i < h->l->count; i++){
        if(h->d->cmp_data(h, h->l->array[i], h->l->array[(i - 1) / 2]))
            return 0;
    }
    return 1;
}

int binary_heap_get_child_index(const BinaryHeap *h, int i){
    if((2 * i + 1) >= h->l->count)
        return -1;
    if((2 * i + 2) == h->l->count)
        return 2 * i + 1;
    if(h->d->cmp_data(h, h->l->array[2 * i + 2], h->l->array[2 * i + 1]))
        return (2 * i + 2);
    return (2 * i + 1);
}

int binary_heap_swap(BinaryHeap *h, int i, const void * data, char shallow_copy){
    int child;
    if(!h || i > h->l->count) return 0;

    if(i > 0 && !h->d->cmp_data(h, h->l->array[(i - 1) / 2], data)) {
        h->l->array[i] = h->l->array[(i - 1) / 2];
        return binary_heap_swap(h, (i - 1) / 2, data, shallow_copy);
    }else{
        child = binary_heap_get_child_index(h, i);
        if(child > -1 && !h->d->cmp_data(h, data, h->l->array[child])){
            h->l->array[i] = h->l->array[child];
            return binary_heap_swap(h, child, data, shallow_copy);
        }
    }

    /* We make sure there is enough space */
    if(!h->l->d->make_space(h->l))
        return 0;
    /* we overwrite the data at index */
    h->l->array[i] = h->l->d->type_descriptor->copy(data);
    return 1;
}

void binary_heap_add(BinaryHeap *h, const void * data){
    if(!h) return;
    if(binary_heap_swap(h, h->l->count, data, 0))
        h->l->count++; /* increase length */
}

void * binary_heap_pop(BinaryHeap *h){
    void * tmp;
    if(!h) return NULL;
    tmp = h->l->array[0];
    if(binary_heap_swap(h, 0, h->l->array[h->l->count-1], 1)){
        h->l->count--;
        h->l->d->update_space(h->l);
    }
    return tmp;
}

void binary_heap_free_descriptor(BinaryHeapDescriptor **bhd){
    if(!*bhd) return;
    if((*bhd)->type_descriptor)
        type_descriptor_free(&(*bhd)->type_descriptor);
    free(*bhd);
    *bhd = NULL;
}

void binary_heap_free(BinaryHeap **h){
    if(!*h) return;
    if((*h)->l){
        (*h)->l->d->free(&(*h)->l);
    }
    if((*h)->d)
        binary_heap_free_descriptor(&(*h)->d);
    free(*h);
    *h = NULL;
}