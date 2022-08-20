
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

void movie_m(TypeDescriptor * td){  
    assert(td);
    td->data_size = sizeof(Movie);  
    td->manifest = movie_m;  
    td->cmp = movie_cmp;  
    td->print = movie_print;  
    td->fprint = movie_fprint;  
    td->copy = movie_copy;  
    td->free_data = movie_free;  
    td->eq = movie_eq;  
    td->lt = movie_lt;  
    td->le = movie_le;  
    td->gt = movie_gt;
    td->ge = movie_ge;  
}  
  
int movie_cmp(const void * x, const void * y){  
	return strcmp(((Movie *) x)->title, ((Movie *) y)->title); /* We choose that sorting - by default - will be made on the title */
}  
  
int movie_eq(const void * x, const void * y){  
	return movie_cmp(x, y) == 0;
}  
  
int movie_lt(const void * x, const void * y){  
	return movie_cmp(x, y) < 0;
}  
  
int movie_le(const void * x, const void * y){  
	return movie_cmp(x, y) <= 0;
}  
  
int movie_gt(const void * x, const void * y){  
	return movie_cmp(x, y) > 0;
}  
  
int movie_ge(const void * x, const void * y){  
	return movie_cmp(x, y) >= 0;
}  
  
void movie_print(const void * x){  
	movie_fprint(stdout, x);  
}  
  
void movie_fprint(FILE * stream, const void * x){  
	if(!x)  fprintf(stream, "Null");  
  fprintf(stream, "%c",  *(char *) x);  
}  
  
void * movie_copy(const void * data){  
	void *alloc_data;  
	size_t data_size;  
	data_size = sizeof(char);  
	alloc_data = calloc(1, data_size);  
	if(!alloc_data) return NULL;
	/* copy content */
	alloc_data->title = (char *) malloc(sizeof(char) * (strlen((Movie *)->title) + 1));
	strcpy(alloc_data->title, (Movie *)->title);
	
	/* We choose to just copy the pointer to the person */	
	alloc_data->director = (Movie *)->director; 
    alloc_data->year = (Movie *)->year;
    alloc_data->minutes	= (Movie *)->minutes;
    
    /* We alloc a new list but pointers are copied from the source */
    alloc_data->cast = (Movie *)->cast->shallow_copy((Movie *)->cast); 
    
	return alloc_data;
}  
  
void movie_free(void ** x){  
	if(!*x) return;
	free((Movie *)->title);
	(Movie *)->cast->shallow_free((Movie *)->cast);
	free(*x);
	*x = NULL;
}

/* 
    Related functions of the Movie struct...
*/

/*    
	By making your own type_manifest you will be able to use your custom Type through
	the lib's implemented structures. Like so:    
*/
 
int main(){  
 LinkedList l;  
 Movie movie1, movie2;
 
 movie1 = new_movie("Tron", 1982);
 l = new_linked_list(&movie1, movie_m);     
 
 movie2 = new_movie("Tron Legacy", 2010);
 l->d->prepend(&l, &movie2);
 l->d->print(l);
 
 /*  [Tron legacy, Tron]  */
 
 l->d->free(&tmp);  
 return 0;
}
```