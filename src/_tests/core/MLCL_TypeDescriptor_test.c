/*
 *   This file is part of the MLCL Library
 *   Antoine Bastos 2022
 *   SPDX-License-Identifier: Apache-2.0
 */

#include "../../../include/_tests/core/MLCL_TypeDescriptor_test.h"
#include "../../../include/core/MLCL_primitive_types.h"
#include "../../../include/_tests/MLCL_exceptions.h"

int run_all_type_descriptor_tests(){
    printf("▒▓ Running all TypeDescriptor tests\n");
    MLCL_TEST(test_new_int_descriptor)
    return 1;
}

int test_new_int_descriptor(){
    TypeDescriptor * td;
    int x, y;x = 1;
    y = 2;
    td = new_type_descriptor(int_m);
    if(!td) MLCL_ERR(1, MLCL_ERR_ALLOC)
    if(!td->cmp(&x, &y)) MLCL_ERR(2, MLCL_ERR_EQ)
    type_descriptor_free(&td);
    return 1;
}