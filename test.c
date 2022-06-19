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

int randint(int a, int b){
    return (rand() % (b + 1 - a)) + a;
}

int main(){
    LinkedList list;
    int i, x;
    srand(time(0));

    list = NULL;
    x = 67;
    list = new_ll(&x);
    for(i = 0; i < 1; i++){
        x = randint(1, 120);
        list->d->prepend(&list, &x);
    }
    list->d->print(list);printf("\n");

    x = 64;
    printf("\n64 in list ? %s\n", list->d->search(list, &x) ? "Yes" : "No");
    x = 67;
    list->d->prepend(&list, &x);
    list->d->print(list);printf("\n");

    list->d->del(&list, &x);
    list->d->print(list);printf("\n");

    list->d->free(&list);
    printf("\n");
    return 0;
}