

#include "../MLCL/MLCL.h"
#include "string.h"
#include "../include/Movie.h"
#include "../include/Person.h"


#include "../MLCL/MLCL.h"
#include "../include/Movie.h"
#include "../include/Person.h"


int main(){

    List *movies;
    Movie *movie;

    movies = new_list(LINKED_LIST, movie_m);



    /**** Tron 1982 ****/
    movie = new_movie("Tron", 1982);

    /* The director */
    movie->director = new_person(new_str("Steven"), new_str("Lisberger"));

    /* The cast */
    list_append(movie->cast, new_person(new_str("Jeff"), new_str("Bridges")));    
    list_append(movie->cast, new_person(new_str("Bruce"), new_str("Broxleitner")));
    list_append(movie->cast, new_person(new_str("Cindy"), new_str("Morgan")));
    list_append(movie->cast, new_person(new_str("Dan"), new_str("Shor")));
    list_append(movie->cast, new_person(new_str("David"), new_str("Warner")));

    /* Append Tron to the movies list */
    list_prepend(movies, movie);



    /**** Tron legacy ****/
    movie = new_movie("Tron legacy", 2010);

    /* The director */
    movie->director = new_person(new_str("Joseph"), new_str("Kosinski"));

    /* The cast */
    list_append(movie->cast, new_person(new_str("Garett"), new_str("Hedlund")));    
    list_append(movie->cast, new_person(new_str("Olivia"), new_str("Wilde")));
    list_append(movie->cast, new_person(new_str("Jeff"), new_str("Bridges")));
    list_append(movie->cast, new_person(new_str("Bruce"), new_str("Broxleitner")));
    list_append(movie->cast, new_person(new_str("Beau"), new_str("Garrett")));

    /* Append Tron legacy to the movies list */
    list_prepend(movies, movie);

    /* Sort this list (as defined in movie_cmp, by title)  */
    linked_list_merge_sort(movies->s.linked_list, movie_lt);
    list_print(movies);

    /*  Let's search for a movie */
    {
        Filter *filter;
        filter = new_filter(1);
        filter->bfilters[0] = new_bfilter(movie_bfilter_title, new_str("Tron"), EQ, str_free);
        printf("Valide ? %d\n", filter->evaluate(filter, movies->s.linked_list->head->data));
        filter_free(&filter);
    }

    printf("\n");
	return 0;
}
