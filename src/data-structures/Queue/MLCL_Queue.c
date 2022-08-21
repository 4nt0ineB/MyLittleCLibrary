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
    Queue * q;
    if(!type_manifest) return NULL;
    q = (Queue *) malloc(sizeof(Queue));
    if(!q) return NULL;
    q->l = (List *) new_list(CIRCULAR_DOUBLE_LINKED_LIST, type_manifest);
    if(!q->l) return NULL;
    /* Methods */
    q->add = queue_add;
    q->pop = queue_pop;
    q->peek = queue_peek;
    q->is_empty = queue_is_empty;
    q->free = queue_free;
    return q;
}

int queue_add(Queue * q, const void * data){
    if(!q) return 0;
    if(!q->l) return 0;
    q->l->append(q->l, data);
    return 1;
}

void * queue_peek(const Queue *q){
    if(!q) return NULL;
    if(!q->l) return NULL;
    return q->l->head_peek(q->l);
}

void * queue_pop(Queue * q){
    if(!q) return NULL;
    if(!q->l) return NULL;
    return q->l->shift(q->l);
}

int queue_is_empty(const Queue *q){
    if(!q) return 1;
    if(!q->l) return 1;
    return q->l->is_empty(q->l);
}

void queue_free(Queue **q){
    if(!*q) return;
    if((*q)->l)
        (*q)->l->free(&(*q)->l);
    free(*q);
    *q = NULL;
}