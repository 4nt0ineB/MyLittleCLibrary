/*
 *   This file is part of the MLCL Library
 *   Antoine Bastos 2022
 *   SPDX-License-Identifier: Apache-2.0
 */

#include "../../../../include/_tests/data-structures/Stack/MLCL_Stack_test.h"
#include "../../../../include/data-structures/Stack/MLCL_Stack.h"
#include "../../../../include/_tests/MLCL_exceptions.h"

int run_all_stack_tests(){
    printf("▒▒▒ Running all Stack tests \n");
    MLCL_TEST(test_stack_add)
    MLCL_TEST(test_stack_pop)
    return 1;
}

int test_stack_add(){
    Stack *stack;
    stack = new_stack(int_m);
    if(!stack)
        MLCL_ERR(1, MLCL_ERR_ALLOC)
    stack_add(stack, new_int(1));
    stack_add(stack, new_int(2));
    stack_add(stack, new_int(3));
    if((* (int *) stack->s.circular_double_linked_list->head->data) != 3)
        MLCL_ERR(2, MLCL_ERR_TRUE)
    stack_free(&stack);
    return 1;
}

int test_stack_pop(){
    Stack *stack;
    void * tmp;
    stack = new_stack(int_m);
    if(!stack)
        MLCL_ERR(1, MLCL_ERR_ALLOC)
    stack_add(stack, new_int(1));
    stack_add(stack, new_int(2));
    stack_add(stack, new_int(3));
    tmp = stack_pop(stack);
    if((* (int *) tmp) != 3)
        MLCL_ERR(2, MLCL_ERR_TRUE)
    free(tmp);
    stack_free(&stack);
    return 1;
}
