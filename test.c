
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
    x = randint(1, 120);
    list = new_ll(&x);
    for(i = 0; i < 10; i++){
        x = randint(1, 120);
        list->d->prepend(&list, &x);
    }
    list->d->print(list);



    printf("\n");
    return 0;
}