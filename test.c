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
    return 0;

    LinkedList list;
    int i;
    int x;
    srand(time(0));

    list = NULL;
    x = 1;
    list = new_ll(&x, new_type_descriptor(int_manifest));
    list->d->print(list);printf("\n");
    for(i = 0; i < 5; i++){
        x = 'a' + i;
        list->d->prepend(&list, &x);
    }
    list->d->print(list);printf("\n");

    x = 2;
    printf("2 in list ? %s\n", list->d->search(list, &x) ? "Yes" : "No");

    x = 2;
    printf("Add 2:\n");
    list->d->prepend(&list, &x);
    list->d->print(list);printf("\n");

    printf("2 in list ? %s\n", list->d->search(list, &x) ? "Yes" : "No");

    x = 1;
    printf("del 2:\n");
    list->d->del(&list, &x);
    list->d->print(list);printf("\n");

    x = 1;
    printf("del 1:\n");
    list->d->del(&list, &x);
    list->d->print(list);printf("\n");


    list->d->free(&list);

    printf("\n");
    return 0;
}