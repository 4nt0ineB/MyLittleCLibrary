/*
 *   This file is part of the MLCL Library.
 *   Antoine Bastos 2022
 *
 *   This Library is free software under the terms of
 *   the MIT license.
 */

#ifndef MYLITTLECLIBRARY_MLCL_EXCEPTIONS_H
#define MYLITTLECLIBRARY_MLCL_EXCEPTIONS_H

#include <stdio.h>

#define MLCL_TEST(result) {if(result()){printf(" ok\n");}else{return 0;}}
#define MLCL_ERR(id, msg) {printf("\n\t[%d]: " msg "\n", id); return 0;}
#define MLCL_OK() {printf("\tok\n");}
#define MLCL_ERR_ALLOC "Allocation failed."
#define MLCL_ERR_EQ "Should be equal."
#define MLCL_ERR_NEQ "Shouldn't be equal."
#define MLCL_ERR_VAL "Not the expected value."
#define MLCL_ERR_TRUE "Should be true."
#define MLCL_ERR_FALSE "Should be false."

#endif /* MYLITTLECLIBRARY_MLCL_EXCEPTIONS_H */
