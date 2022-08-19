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

#include "../include/MLCL_utils.h"
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#define MIN3(a, b, c) ((a) < (b) ? ((a) < (c) ? (a) : (c)) : ((b) < (c) ? (b) : (c)))

unsigned short lfsr = 0xACE1u;
unsigned bit;

unsigned mlcl_unsigned_rand(){
    bit  = ((lfsr >> 0) ^ (lfsr >> 2) ^ (lfsr >> 3) ^ (lfsr >> 5) ) & 1;
    return lfsr =  (lfsr >> 1) | (bit << 15);
}

int int_rand(int a, int b){
    return (rand() % (b + 1 - a)) + a;
}

float float_rand(float min, float max){
    return min + (rand() / (float) RAND_MAX) * (max - min);
}

int proper_modulo(int a, int b) {
    int mod;
    assert(b != 0);
    mod = a % b;
    return mod >= 0 ? mod : mod + b;
}


int mlcl_levenshtein(const char *s1, const char *s2){
    unsigned int len1, len2;
    unsigned int i, j;
    int result;
    unsigned int **mat;

    len1 = strlen(s1);
    len2 = strlen(s2);

    mat = (unsigned int **) malloc(sizeof(int*) * (len2 + 1));
    for(j = 0; j <= len2; j++)
        mat[j] = (unsigned int *) malloc(sizeof(int) * (len1 + 1));
    mat[0][0] = 0;
    /* init */
    for (i = 1; i <= len2; i++)
        mat[i][0] = mat[i-1][0] + 1;
    for (j = 1; j <= len1; j++)
        mat[0][j] = mat[0][j-1] + 1;
    /* fill */
    for (i = 1; i <= len2; i++)
        for (j = 1; j <= len1; j++)
            mat[i][j] = MIN3(mat[i-1][j] + 1, mat[i][j-1] + 1, mat[i-1][j-1] + (s1[j-1] == s2[i-1] ? 0 : 1));

    /* Save result */
    result = (int) mat[len2][len1];
    /* Free array */
    for(j = 0; j <= len2; j++)
        free(mat[j]);
    free(mat);

    return result;
}