/*
 *   This file is part of the MLCL Library.
 *
 *   Copyright (C) 2022 Antoine Bastos
 *
 *   This Library is free software under the terms of
 *   the MIT license.
 */

#include <stdio.h>
#include <time.h>

#include "MLCL.h"

int int_rand(int a, int b){
    return (rand() % (b + 1 - a)) + a;
}

float float_rand(float min, float max){
    return min + (rand() / (float) RAND_MAX) * (max - min);
}

int main(){
    run_all_tests();
    /*LinkedList tmp;
    int i;
    float x;
    x = 5.f;
    tmp = new_linked_list("b", new_type_descriptor(char_manifest));
    x = 10.f;
    for(i = 0; i < 20; i++)
        tmp->d->append(&tmp, &i);
    ll_to_dot(tmp, "./test.dot");
    tmp->d->free(&tmp);*/
    printf("\n");
    return 0;
}