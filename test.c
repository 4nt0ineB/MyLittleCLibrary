/*
 *   This file is part of the MLCL Library.
 *
 *   Copyright (C) 2022 Antoine Bastos
 *
 *   This Library is free software under the terms of
 *   the MIT license.
 */

#include "MLCL.h"

/*int int_rand(int a, int b){
    return (rand() % (b + 1 - a)) + a;
}

float float_rand(float min, float max){
    return min + (rand() / (float) RAND_MAX) * (max - min);
}*/

int main(){
    /*DoubleLinkedList tmp;
    int i, x;
    x = 5;
    tmp = new_double_linked_list(&x, int_manifest);
    x = 10;
    for(i = 0; i < 20; i++)
        tmp->d->append(&tmp, &i);
    tmp->d->to_dot(tmp, "./test.dot");
    tmp->d->free(&tmp);*/
    return !run_all_tests();

}