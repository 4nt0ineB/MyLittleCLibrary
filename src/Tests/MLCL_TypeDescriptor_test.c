/*
 *   This file is part of the MLCL Library.
 *   Antoine Bastos 2022
 *
 *   This Library is free software under the terms of
 *   the MIT license.
 */

#include "../../include/Tests/MLCL_TypeDescriptor_test.h"
#include "../../include/MLCL_basic_types.h"
#include "../../include/Tests/MLCL_exceptions.h"

int run_all_type_descriptor_tests(){
    printf("|> Running all TypeDescriptor tests <|\n");
    MLCL_TEST(test_new_int_descriptor);
    return 1;
}

int test_new_int_descriptor(){
    TypeDescriptor * td;
    int x, y;
    printf("- test_new_int_descriptor: ");
    x = 1;
    y = 2;
    td = new_type_descriptor(int_manifest);
    if(!td) MLCL_ERR(1, MLCL_ERR_ALLOC);
    if(!td->cmp(&x, &y)) MLCL_ERR(2, MLCL_ERR_EQ);
    type_descriptor_free(&td);
    return 1;
}