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

#ifndef MYLITTLECLIBRARY_MLCL_LIST_H
#define MYLITTLECLIBRARY_MLCL_LIST_H

#include "MLCL_ArrayList.h"
#include "MLCL_LinkedList.h"
#include "MLCL_CircularLinkedList.h"
#include "MLCL_DoubleLinkedList.h"
#include "MLCL_CircularDoubleLinkedList.h"

/**
 * @enum Available list types
 */
typedef enum e_list_type {
    ARRAY_LIST,
    LINKED_LIST,
    CIRCULAR_LINKED_LIST,
    DOUBLE_LINKED_LIST,
    CIRCULAR_DOUBLE_LINKED_LIST
} LIST_TYPE;


/**
 * Interface of lists for basic usage
 */
typedef struct s_list{
    LIST_TYPE type; /**< Type of list implementation of the list */
    void (*type_manifest) (TypeDescriptor *); /**< type_manifest stored to be able to realloc a list struct of the same type*/

    union {
        ArrayList * array_list;
        LinkedList linked_list;
        CircularLinkedList circular_linked_list;
        DoubleLinkedList double_linked_list;
        CircularDoubleLinkedList circular_double_linked_list;
    } s; /**< The pointer to the list structure implementation */

    int (*length) (const struct s_list *);
    int (*is_empty) (const struct s_list *);
    int (*append) (struct s_list *, const void *);
    int (*prepend) (struct s_list *, const void *);
    void * (*head_peek) (const struct s_list *);
    void * (*tail_peek) (const struct s_list *);
    void * (*pop) (struct s_list *);
    void * (*shift) (struct  s_list *);
    void (*print) (const struct s_list *);
    void (*fprint) (FILE *, const struct s_list *);
    void (*to_dot) (const struct s_list *, const char *);

    char prefix;
    char suffix;

    void (*free) (struct s_list **);
    int (*check_init_) (struct s_list *, const void *);

} List;

List * new_list(LIST_TYPE list_type, void (*type_manifest) (TypeDescriptor *));
int list_append(List *l, const void *data);
int list_prepend(List *l, const void *data);
void * list_head_peek(const List *l);
void * list_tail_peek(const List *l);
void * list_pop(List *l);
void * list_shift(List *l);
int list_is_empty(const List *l);
int list_length(const List *l);
void list_free(List **l);
void list_print (const List *l);
void list_fprint (FILE * stream, const List *l);
void list_to_dot(const List *l, const char * path);

/**
 * @brief Init the list with data if empty and return 1, else return 0.
 * @param l
 * @param data
 * @return
 */
int list_check_init_(List *l, const void * data);


#endif /* MYLITTLECLIBRARY_MLCL_LIST_H */
