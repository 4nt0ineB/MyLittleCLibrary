project(MLCL)
cmake_minimum_required(VERSION 3.23)

add_library(MLCL STATIC
        src/core/Filter
        src/core/Filter/MLCL_Filter.c
        src/core/MLCL_logic.c
        src/core/MLCL_TypeDescriptor.c
        src/core/MLCL_primitive_types.c
        src/data-structures
        src/data-structures/Heap
        src/data-structures/Heap/MLCL_BinaryHeap.c
        src/data-structures/Stack
        src/data-structures/Stack/MLCL_Stack.c
        src/data-structures/Trees
        src/data-structures/Trees/MLCL_BinarySearchTree.c
        src/data-structures/Trees/MLCL_AVLTree.c
        src/data-structures/Trees/MLCL_BKTree.c
        src/data-structures/Trees/MLCL_TernarySearchTree.c
        src/data-structures/Queue
        src/data-structures/Queue/MLCL_Queue.c
        src/data-structures/Lists
        src/data-structures/Lists/MLCL_LinkedList.c
        src/data-structures/Lists/MLCL_DoubleLinkedList.c
        src/data-structures/Lists/MLCL_ArrayList.c
        src/data-structures/Lists/MLCL_CircularLinkedList.c
        src/data-structures/Lists/MLCL_List.c
        src/data-structures/Lists/MLCL_CircularDoubleLinkedList.c
        src/_tests
        src/_tests/MLCL_all_tests.c
        src/_tests/data-structures
        src/_tests/data-structures/Heap
        src/_tests/data-structures/Heap/MLCL_BinaryHeap_test.c
        src/_tests/data-structures/Stack
        src/_tests/data-structures/Stack/MLCL_Stack_test.c
        src/_tests/data-structures/Trees
        src/_tests/data-structures/Trees/MLCL_BinarySearchTree_test.c
        src/_tests/data-structures/Trees/MLCL_BKTree_test.c
        src/_tests/data-structures/Trees/MLCL_TernarySearchTree_test.c
        src/_tests/data-structures/Trees/MLCL_AVLTree_test.c
        src/_tests/data-structures/Queue
        src/_tests/data-structures/Queue/MLCL_Queue_test.c
        src/_tests/data-structures/Lists
        src/_tests/data-structures/Lists/MLCL_List_test.c
        src/_tests/data-structures/Lists/MLCL_CircularLinkedList_test.c
        src/_tests/data-structures/Lists/MLCL_CircularDoubleLinkedList_test.c
        src/_tests/data-structures/Lists/MLCL_ArrayList_test.c
        src/_tests/data-structures/Lists/MLCL_LinkedList_test.c
        src/_tests/data-structures/Lists/MLCL_DoubleLinkedList_test.c
        src/_tests/core
        src/_tests/core/MLCL_TypeDescriptor_test.c
        src/time
        src/time/MLCL_Timer.c
        src/utils
        src/utils/MLCL_utils.c
        )


# CMake instructions to test using the static lib

set(APP_EXE mylibtest)

add_executable(${APP_EXE} test.c)

target_link_libraries(${APP_EXE}  MLCL)