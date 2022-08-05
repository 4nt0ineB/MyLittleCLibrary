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
  */

#include "../../include/_Tests/MLCL_TypeDescriptor_test.h"
#include "../../include/MLCL_basic_types.h"
#include "../../include/_Tests/MLCL_exceptions.h"

int run_all_type_descriptor_tests(){
    printf("▒▓ Running all TypeDescriptor tests\n");
    MLCL_TEST(test_new_int_descriptor, "test_new_int_descriptor")
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