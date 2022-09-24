/*
 *   This file is part of the MLCL Library
 *   Copyrleft 2022 Antoine Bastos
 *   SPDX-License-Identifier: Apache-2.0
 */

#ifndef MYLITTLECLIBRARY_MLCL_ALL_tests_H
#define MYLITTLECLIBRARY_MLCL_ALL_tests_H

#include "core/MLCL_TypeDescriptor_test.h"
/* Timer */
#include "../time/MLCL_Timer.h"

/* List */
#include "data-structures/Lists/MLCL_List_test.h"
#include "data-structures/Lists/MLCL_ArrayList_test.h"
#include "data-structures/Lists/MLCL_LinkedList_test.h"
#include "data-structures/Lists/MLCL_CircularLinkedList_test.h"
#include "data-structures/Lists/MLCL_DoubleLinkedList_test.h"
#include "data-structures/Lists/MLCL_CircularDoubleLinkedList_test.h"
/* Trees */
#include "data-structures/Trees/MLCL_BinarySearchTree_test.h"
#include "data-structures/Trees/MLCL_AVLTree_test.h"
#include "data-structures/Trees/MLCL_TernarySearchTree_test.h"
#include "data-structures/Trees/MLCL_BKTree_test.h"
/* Stack */
#include "data-structures/Stack/MLCL_Stack_test.h"
/* Queue */
#include "data-structures/Queue/MLCL_Queue_test.h"
/* Heap */
#include "data-structures/Heap/MLCL_BinaryHeap_test.h"


int run_all_tests();

#endif /* MYLITTLECLIBRARY_MLCL_ALL_tests_H */
