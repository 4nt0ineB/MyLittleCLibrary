/*   Movie.h */ 

#ifndef __MLCL_TEST_MOVIE_H__
#define __MLCL_TEST_MOVIE_H__

#include "../MLCL/MLCL.h"
#include "Person.h"
#include "stdlib.h"
#include "string.h"

typedef struct {
    short year;
    short minutes;
    char * title;
    
    Person *director;
    List *cast; /* a list of Person (let's say pointers)*/ 
} Movie;

Movie * new_movie(char *title, short year);
void movie_m(TypeDescriptor *td);
int movie_cmp(const void *x, const void *y);
int movie_eq(const void *x, const void *y);
int movie_lt(const void *x, const void *y);
int movie_le(const void *x, const void *y);
int movie_gt(const void *x, const void *y);
int movie_ge(const void *x, const void *y);
void movie_print(const void * x);
void movie_fprint(const void *x, FILE *stream);
void movie_free(void *x);

#endif /* __MLCL_TEST_MOVIE_H__ */