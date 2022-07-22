/*
 *   This file is part of the MLCL Library.
 *   Antoine Bastos 2022
 *
 *   This Library is free software under the terms of
 *   the MIT license.
 *
 *    ____    ____           _____     _  _     _   __            ______   _____     _  __
 *   |_   \  /   _|         |_   _|   (_)/ |_  / |_[  |         .' ___  | |_   _|   (_)[  |
 *     |   \/   |   _   __    | |     __`| |-'`| |-'| | .---.  / .'   \_|   | |     __  | |.--.  _ .--.  ,--.  _ .--. _   __
 *     | |\  /| |  [ \ [  ]   | |   _[  || |   | |  | |/ /__\\ | |          | |   _[  | | '/'`\ [ `/'`\]`'_\ :[ `/'`\| \ [  ]
 *    _| |_\/_| |_  \ '/ /   _| |__/ || || |,  | |, | || \__., \ `.___.'\  _| |__/ || | |  \__/ || |    // | |,| |    \ '/ /
 *   |_____||_____[\_:  /   |________[___]__/  \__/[___]'.__.'  `.____ .' |________[___|__;.__.'[___]   \'-;__[___] [\_:  /
 *                \__.'                                                                                             \__.'
*/

#ifndef MYLITTLECLIBRARY_MLCL_H
#define MYLITTLECLIBRARY_MLCL_H

#include "include/MLCL_TypeDescriptor.h"
#include "include/MLCL_basic_types.h"
/* List */
#include "include/List/MLCL_LinkedList.h"
#include "include/List/MLCL_CircularLinkedList.h"
#include "include/List/MLCL_DoubleLinkedList.h"
#include "include/List/MLCL_CircularDoubleLinkedList.h"
/* Tree */
#include "include/Tree/MLCL_BinarySearchTree.h"

/*****************
    Tests
*****************/
#include "include/_Tests/MLCL_all_tests.h"
#include "include/_Tests/MLCL_exceptions.h"
#include "include/_Tests/MLCL_TypeDescriptor_test.h"
/* List */
#include "include/_Tests/List/MLCL_LinkedList_test.h"
#include "include/_Tests/List/MLCL_CircularLinkedList_test.h"
#include "include/_Tests/List/MLCL_DoubleLinkedList_test.h"
#include "include/_Tests/List/MLCL_CircularDoubleLinkedList_test.h"
/* Tree */
#include "include/_Tests/Tree/MLCL_BinarySearchTree_test.h"

#endif /* MYLITTLECLIBRARY_MLCL_H */
