/*
 *   This file is part of the MLCL Library
 *   Copyrleft 2022 Antoine Bastos
 *   SPDX-License-Identifier: Apache-2.0
 */

#ifndef MYLITTLECLIBRARY_MLCL_LOGIC_H
#define MYLITTLECLIBRARY_MLCL_LOGIC_H

typedef enum comparison_predicate_t {
    EQ, NEQ, LT, LE, GT, GE
} comparison_predicate_t;

int logic_cmp(int cmp_return, comparison_predicate_t cmp_predicate);

#endif /* MYLITTLECLIBRARY_MLCL_LOGIC_H */
