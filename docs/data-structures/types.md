
##  Type manifest

###  What's that

All the structures are linked to a *TypeDescriptor*, an interface required to manipulate the data they are carrying.

It requires (for now), few things:
- the size of the type you want to use
- some functions to print the data
- a function to free the data and another one to copy the data  (deep or not, you decide if you make your own)
- some comparison functions

The *TypeDescriptor* gets those through a type manifest which handle specific functions of the type to be manipulated.  
Its like defining you own type in Python (\_\_str__, \_\_eq__, \_\_lt__, etc...).

When making new structures you passes the manifest of the type you want them to carry :
```c
ArrayList l = new_array_list(int_m); 
/* Voilà, you have got a brand new array list of int */
```
### Define your own type

Let say you implemented a Movie structure. You can take example on the basic types, and can do as follows:

```c  
/*   Movie.h */ 
 
typedef struct {
    short year;
    short minutes;
    char * title;
    
    Person *director;
    List *cast; /* a list of Person */
} Movie;

/* ... */

/*   Movie.c */ 

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
    free(movie->title);
    free(x);
}

/* 
    Related functions of the Movie struct...
*/
```

Then you will be able to use the Movie struct in all the data structures.

```c
int main(){  
    
 LinkedList movies;
 
 l = new_linked_list(movie_m);
 
 linked_list_prepend(movies, new_movie("Tron", 1982));
 linked_list_prepend(movies, new_movie("Tron: Legacy", 2010));
 
 linked_list_print(movies); 
 /*  [Tron legacy, Tron]  */
 
 
 linked_list_free(&movies);  
 
 return 0;
}
```