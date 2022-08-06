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

#include "../../../include/_Tests/Trees/MLCL_BinaryHeap_test.h"
#include "../../../include/_Tests/MLCL_exceptions.h"
#include "../../../include/MLCL_TypeDescriptor.h"
#include "../../../include/MLCL_basic_types.h"

int run_all_binary_heap_tests(){
    printf("▒▒▒ Running all BinaryHeap tests ▒▒▒\n");
    MLCL_TEST(test_binary_heap_add,
              "test_binary_heap_add")
    return 1;
}

int test_binary_heap_add(){
    BinaryHeap *h;
    int x;

    h = new_binary_heap(MAX_HEAP, int_m);

    x = 5;
    binary_heap_add(h, &x);
    x = 2;
    binary_heap_add(h, &x);
    x = 6;
    binary_heap_add(h, &x);
    x = 1;
    binary_heap_add(h, &x);
    x = 0;
    binary_heap_add(h, &x);

    h->d->free(&h);
    return 1;
}