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

#ifndef MYLITTLECLIBRARY_MLCL_QUEUE_H
#define MYLITTLECLIBRARY_MLCL_QUEUE_H

#include "../Lists/MLCL_List.h"

typedef struct s_queue {
    List *l;
    int (*add) (struct s_queue *, const void *);
    void * (*peek) (const struct s_queue *);
    void * (*pop) (struct s_queue *);
    int (*is_empty) (const struct s_queue *);
    void (*free) (struct s_queue **);
} Queue;

Queue * new_queue(void (*type_manifest) (TypeDescriptor *));
int queue_add(Queue *q, const void * data);
void * queue_peek(const Queue *q);
void * queue_pop(Queue * q);
int queue_is_empty(const Queue *q);
void queue_free(Queue **q);

#endif /* MYLITTLECLIBRARY_MLCL_QUEUE_H */
