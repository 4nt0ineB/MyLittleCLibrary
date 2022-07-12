/*
 *   This file is part of the MLCL Library.
 *   Antoine Bastos 2022
 *
 *   This Library is free software under the terms of
 *   the MIT license.
 */

#ifndef MYLITTLECLIBRARY_MLCL_GRAPHVIZ_H
#define MYLITTLECLIBRARY_MLCL_GRAPHVIZ_H

#include "MLCL_basic_types.h"
#include "MLCL_TypeDescriptor.h"
#include "MLCL_LinkedList.h"
#include "MLCL_CircularLinkedList.h"
#include "MLCL_DoubleLinkedList.h"

#include <stdio.h>

/*static void mlcl_make_dot_file(const char * dest_path);*/

static void _ll_to_dot(LinkedList ll, FILE * file);

void ll_to_dot(LinkedList ll, const char * dest_path);
#endif /* MYLITTLECLIBRARY_MLCL_GRAPHVIZ_H */
