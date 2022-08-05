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
/* Lists */
#include "include/Lists/MLCL_ArrayList.h"
#include "include/Lists/MLCL_LinkedList.h"
#include "include/Lists/MLCL_CircularLinkedList.h"
#include "include/Lists/MLCL_DoubleLinkedList.h"
#include "include/Lists/MLCL_CircularDoubleLinkedList.h"

#include "include/Lists/MLCL_List.h"
/* Trees */
#include "include/Trees/MLCL_BinarySearchTree.h"
#include "include/Trees/MLCL_AVLTree.h"

/*****************
    Tests
*****************/
#include "include/_Tests/MLCL_exceptions.h"
#include "include/_Tests/MLCL_all_tests.h"
#include "include/_Tests/MLCL_TypeDescriptor_test.h"
/* Lists */
#include "include/_Tests/Lists/MLCL_ArrayList_test.h"
#include "include/_Tests/Lists/MLCL_LinkedList_test.h"
#include "include/_Tests/Lists/MLCL_CircularLinkedList_test.h"
#include "include/_Tests/Lists/MLCL_DoubleLinkedList_test.h"
#include "include/_Tests/Lists/MLCL_CircularDoubleLinkedList_test.h"
/* Trees */
#include "include/_Tests/Trees/MLCL_BinarySearchTree_test.h"
#include "include/_Tests/Trees/MLCL_AVLTree_test.h"

#endif /* MYLITTLECLIBRARY_MLCL_H */
