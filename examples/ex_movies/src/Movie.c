
#include "../include/Movie.h"
#include "../MLCL/include/core/Filter/MLCL_Filter.h"

Movie * new_movie(char *title, short year){
    Movie *movie;
    if(!title) return NULL;
    movie = (Movie *) malloc(sizeof(Movie));
    movie->cast = new_list(ARRAY_LIST, person_m);
    if(!movie->cast){
        movie_free(movie);
        return NULL;
    }
    movie->title = title;
    movie->year = year;
    return movie;
}

void movie_m(TypeDescriptor *td){  
    assert(td);
    td->data_size = sizeof(Movie);  
    td->manifest = movie_m;  
    td->cmp = movie_cmp;  
    td->print = movie_print;  
    td->fprint = movie_fprint;  
    td->copy = NULL;  
    td->data_free = movie_free;  
    td->eq = movie_eq;  
    td->lt = movie_lt;  
    td->le = movie_le;  
    td->gt = movie_gt;
    td->ge = movie_ge;  
}  
  
int movie_cmp(const void *x, const void *y){  
    /* Sorting will be made on title by default */
	return strcmp(((Movie *) x)->title, ((Movie *) y)->title);
}  
  
int movie_eq(const void *x, const void *y){  
	return movie_cmp(x, y) == 0;
}  
  
int movie_lt(const void *x, const void *y){  
	return movie_cmp(x, y) < 0;
}  
  
int movie_le(const void *x, const void *y){  
	return movie_cmp(x, y) <= 0;
}  
  
int movie_gt(const void *x, const void *y){  
	return movie_cmp(x, y) > 0;
}  
  
int movie_ge(const void *x, const void *y){  
	return movie_cmp(x, y) >= 0;
}  
  
void movie_print(const void * x){  
	movie_fprint(x, stdout);  
}  
  
void movie_fprint(const void *x, FILE *stream){  
    Movie *movie;
    if(!x) return;
    movie = (Movie *) x;
    fprintf(stream, "%s (%hd)",  movie->title, movie->year);
}  

void movie_free(void *x){  
	Movie *movie;
    if(!x) return;
    movie = (Movie *) x;
    list_free(&movie->cast);
    person_free(movie->director);
    printf("HEY\n");
    free(movie->title);
    free(x);
}

/* Filters */

int movie_filter_title(void *self, void *field_value, comparison_predicate_t cmp_predicate){
    Movie *movie;
    if(!self || !field_value) return 0;
    movie = (Movie *) self;
    return logic_cmp(strcmp(movie->title, field_value), cmp_predicate);
}
