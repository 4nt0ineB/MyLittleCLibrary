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

#include "../../../include/_Tests/Queue/MLCL_Queue_test.h"
#include "../../../include/Queue/MLCL_Queue.h"
#include "../../../include/_Tests/MLCL_exceptions.h"
#include "../../../include/MLCL_basic_types.h"


int run_all_queue_tests(){
    printf("▒▒▒ Running all Queue tests ▒▒▒\n");
    MLCL_TEST(test_queue_add, "test_queue_add")
    MLCL_TEST(test_queue_pop, "test_queue_pop")
    return 1;
}

int test_queue_add(){
    Queue *q;
    int x;

    q = new_queue(int_m);

    if(!q)
        MLCL_ERR(1, MLCL_ERR_ALLOC)
    x = 1;

    q->add(q, &x);
    x = 2;
    q->add(q, &x);
    x = 3;
    q->add(q, &x);

    if((* (int *) q->l->s.circular_double_linked_list->data) != 1)
        MLCL_ERR(2, MLCL_ERR_TRUE)

    q->free(&q);
    return 1;
}

int test_queue_pop(){
    Queue *q;
    int x;
    void * tmp;

    q = new_queue(int_m);

    if(!q)
        MLCL_ERR(1, MLCL_ERR_ALLOC)

    x = 1;
    q->add(q, &x);
    x = 2;
    q->add(q, &x);
    x = 3;
    q->add(q, &x);

    tmp = q->pop(q);

    if((* (int *) tmp) != 1)
        MLCL_ERR(2, MLCL_ERR_TRUE)

    free(tmp);

    q->free(&q);
    return 1;
}