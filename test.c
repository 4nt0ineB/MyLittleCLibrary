
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
    list->d->print(list);


    x = 64;
    printf("\n64 in list ? %s\n", list->d->search(list, &x) ? "Yes" : "No");
    x = 67;
    list->d->prepend(&list, &x);
    list->d->print(list);

    list->d->del(&list, &x);
    printf("MAIN nouv addr: %p\n", (void *) list);
    list->d->print(list);


    printf("\nzz");
    return 0;
}