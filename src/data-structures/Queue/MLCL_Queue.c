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

#include "../../../include/data-structures/Queue/MLCL_Queue.h"

Queue * new_queue(void (*type_manifest) (TypeDescriptor *)){
    return new_list(CIRCULAR_DOUBLE_LINKED_LIST, type_manifest);
}

int queue_add(Queue *self, void *data){
    return list_append(self, data);
}

void * queue_peek(const Queue *self){
    return list_head_peek(self);
}

void * queue_pop(Queue *self){
    return list_shift(self);
}

int queue_is_empty(const Queue *self){
    return !list_length(self);
}

void queue_free(Queue **self){
    list_free(self);
}
