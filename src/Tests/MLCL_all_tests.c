/*
 *   This file is part of the MLCL Library.
 *   Antoine Bastos 2022
 *
 *   This Library is free software under the terms of
 *   the MIT license.
 */

#include "../../include/Tests/MLCL_all_tests.h"
#include <stdio.h>

int run_all_tests(){
    printf("<::::::::[MLCL]::::::::>\n");
    if(!run_all_type_descriptor_tests())
        return 0;
    if(!run_all_linked_list_tests())
        return 0;
    if(!run_all_circular_linked_list_tests())
        return 0;
    /*if(!run_all_double_linked_list_tests())
        return 0;*/
    printf("All tests successfully passed.\n");
    printf("<::::::::::::::::::::::>\n");
    return 1;
}