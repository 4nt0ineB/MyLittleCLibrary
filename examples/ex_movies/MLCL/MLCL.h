/*
 *   This file is part of the MLCL Library
 *   Copyleft 2022 Antoine Bastos
 *   SPDX-License-Identifier: Apache-2.0
 *
 *    ____    ____           _____     _  _     _   __            ______   _____     _  __
 *   |_   \  /   _|         |_   _|   (_)/ |_  / |_[  |         .' ___  | |_   _|   (_)[  |
 *     |   \/   |   _   __    | |     __`| |-'`| |-'| | .---.  / .'   \_|   | |     __  | |.--.  _ .--.  ,--.  _ .--. _   __
 *     | |\  /| |  [ \ [  ]   | |   _[  || |   | |  | |/ /__\\ | |          | |   _[  | | '/'`\ [ `/'`\]`'_\ :[ `/'`\| \ [  ]
 *    _| |_\/_| |_  \ '/ /   _| |__/ || || |,  | |, | || \__., \ `.___.'\  _| |__/ || | |  \__/ || |    // | |,| |    \ '/ /
 *   |_____||_____[\_:  /   |________[___]__/  \__/[___]'.__.'  `.____ .' |________[___|__;.__.'[___]   \'-;__[___] [\_:  /
 *                \__.'                                                                                             \__.'
 *
*/

#ifndef MYLITTLECLIBRARY_MLCL_H
#define MYLITTLECLIBRARY_MLCL_H

/* core */
#include "include/core/MLCL_TypeDescriptor.h"
#include "include/core/MLCL_primitive_types.h"
#include "include/core/MLCL_logic.h"
#include "include/core/Filter/MLCL_Filter.h"

/* List */
#include "include/data-structures/Lists/MLCL_ArrayList.h"
#include "include/data-structures/Lists/MLCL_LinkedList.h"
#include "include/data-structures/Lists/MLCL_CircularLinkedList.h"
#include "include/data-structures/Lists/MLCL_DoubleLinkedList.h"
#include "include/data-structures/Lists/MLCL_CircularDoubleLinkedList.h"
#include "include/data-structures/Lists/MLCL_List.h"

/* Stack */
#include "include/data-structures/Stack/MLCL_Stack.h"

/* Queue */
#include "include/data-structures/Queue/MLCL_Queue.h"

/* Heap */
#include "include/data-structures/Heap/MLCL_BinaryHeap.h"

/* Trees */
#include "include/data-structures/Trees/MLCL_BinarySearchTree.h"
#include "include/data-structures/Trees/MLCL_TernarySearchTree.h"
#include "include/data-structures/Trees/MLCL_AVLTree.h"
#include "include/data-structures/Trees/MLCL_BKTree.h"

/* Timer */
#include "include/time/MLCL_Timer.h"

/*****************
    Tests
*****************/
#include "include/_tests/MLCL_exceptions.h"
#include "include/_tests/MLCL_all_tests.h"
#include "include/_tests/core/MLCL_TypeDescriptor_test.h"

/* List */
#include "include/_tests/data-structures/Lists/MLCL_ArrayList_test.h"
#include "include/_tests/data-structures/Lists/MLCL_LinkedList_test.h"
#include "include/_tests/data-structures/Lists/MLCL_CircularLinkedList_test.h"
#include "include/_tests/data-structures/Lists/MLCL_DoubleLinkedList_test.h"
#include "include/_tests/data-structures/Lists/MLCL_CircularDoubleLinkedList_test.h"

/* Trees */
#include "include/_tests/data-structures/Trees/MLCL_BinarySearchTree_test.h"
#include "include/_tests/data-structures/Trees/MLCL_AVLTree_test.h"

/* Stack */
#include "include/_tests/data-structures/Stack/MLCL_Stack_test.h"

/* Queue */
#include "include/_tests/data-structures/Queue/MLCL_Queue_test.h"

/* Heap */
#include "include/_tests/data-structures/Heap/MLCL_BinaryHeap_test.h"

#endif /* MYLITTLECLIBRARY_MLCL_H */
