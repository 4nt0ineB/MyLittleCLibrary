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

#include "../include/MLCL_UnionFind.h"


/*

unionfind_t * initialisation(int N){
    int i;
    unionfind_t * partition;
    partition = (unionfind_t *)malloc(sizeof(unionfind_t));
    if(partition){
        partition->taille = N;
        partition->pere = (int *) malloc(sizeof(int) * (N-1));
        partition->rang = (int *) malloc(sizeof(int) * (N-1));
        partition->nb_appels = 0;
        if(!partition->pere || !partition->rang)
            return NULL;
        for (i = 0 ; i < partition->taille ; i++) {
            partition->pere[i] = i;
            partition->rang[i] = 0;
        }
    }
    return partition;
}

int trouve_naif(unionfind_t * partition, int x){
    int i;
    assert(x >= 0 && x < partition->taille);
    if(!partition)
        return -1;
    while(partition->pere[x] != x){
        x = partition->pere[x];
        partition->nb_appels += 1;
    }
    return partition->pere[x];
}

void fusion_naif(unionfind_t * partition, int x, int y){
    assert(partition);
    assert(x >= 0 && x < partition->taille);
    assert(y >= 0 && y < partition->taille);
    int rx, ry;
    rx = trouve_naif(partition, x);
    ry = trouve_naif(partition, y);
    if(rx != ry)
        partition->pere[ry] = rx;
}

int trouve_compresse(unionfind_t * partition, int x){
    assert(partition);
    assert(x >= 0 && x < partition->taille);
    if(partition->pere[x] != x){
        partition->pere[x] = trouve_compresse(partition, partition->pere[x]);
        partition->nb_appels += 1;
    }
    return partition->pere[x];
}

void fusion_rang(unionfind_t * partition, int x, int y){
    assert(partition);
    assert(x >= 0 && x < partition->taille);
    assert(y >= 0 && y < partition->taille);
    int rx, ry;
    rx = trouve_compresse(partition, x);
    if(rx != partition->pere[y]){
        ry = trouve_compresse(partition, y);
        if(partition->rang[rx] == partition->rang[ry]){
            partition->pere[ry] = rx;
            partition->rang[rx] += 1;
        }
        if(partition->rang[rx] > partition->rang[ry])
            partition->pere[ry] = rx;
        else
            partition->pere[rx] = ry;
    }
}

int entier_alea(int a, int b){
    return (rand() % (b + 1 - a)) + a;
}

void unionfind_liberer(unionfind_t ** partition){
    if(!*partition)
        return;
    if((*partition)->pere)
        free((*partition)->pere);
    if((*partition)->rang)
        free((*partition)->rang);
    free(*partition);
    *partition = NULL;
}*/
