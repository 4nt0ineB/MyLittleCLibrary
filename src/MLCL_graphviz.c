/*
 *   This file is part of the MLCL Library.
 *   Antoine Bastos 2022
 *
 *   This Library is free software under the terms of
 *   the MIT license.
 */

#include "../include/MLCL_graphviz.h"


static void _ll_to_dot(LinkedList ll, FILE * file){
    if(!ll) return;
    while(ll){
        fprintf(file, "  n%p [label=\"", (void *) ll);
        ll->d->type_descriptor->fprint(file, ll->data);
        fprintf(file, "\" color=\"#918d8d\"]\n");
        if(ll->next)
            fprintf(file, " n%p -> n%p\n", (void *) ll, (void *) ll->next);
        ll = ll->next;
    }
}

void ll_to_dot(LinkedList ll, const char * dest_path){
    FILE * file;
    if(!ll) return;
    file = fopen(dest_path, "w");
    if(!file)
        printf("Couldn't open a file\n");
    fprintf(file, "digraph {\n"
                  "rankdir=\"LR\";\n"
                  "splines=ortho;\n"
                  "node [shape=square , height=.1, rank = same]\n"
                  );
    _ll_to_dot(ll, file);
    fprintf(file, "}\n");
    fclose(file);
}


/*

 digraph {

    ## set direction of graph to be left-->right
    rankdir="LR";
    splines=ortho;

    ## make boxes instead of ellipses
    node [shape=square , height=.1  rank = same]

    ## should enforce nodes to be horizontally aligned
    ## is not working, though...
    rank=same;

     edge [tailclip=false , arrowtail = dot , dir=both];

  */