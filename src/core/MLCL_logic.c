/*
 *   This file is part of the MLCL Library
 *   Antoine Bastos 2022
 *   SPDX-License-Identifier: Apache-2.0
 */

#include "../../include/core/MLCL_logic.h"

int logic_cmp(int cmp_return, comparison_predicate_t cmp_predicate){
    switch (cmp_predicate) {
        case NEQ:
            return cmp_return != 0;
        case EQ:
            return cmp_return == 0;
        case LT:
            return cmp_return < 0;
        case LE:
            return cmp_return <= 0;
        case GT:
            return cmp_return > 0;
        case GE:
            return cmp_return >= 0;
        default:
            return 0;
    }
}