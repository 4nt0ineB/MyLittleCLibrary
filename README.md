
# My Little C Library
A static ANSI C library gathering things I learned in college, to implement things faster for my homework and projects.

[![workflow](https://github.com/cydaw6/MyLittleCLibrary/actions/workflows/c-cpp.yml/badge.svg)](https://github.com/cydaw6/MyLittleCLibrary/actions/workflows/c-cpp.yml)
[![License](https://img.shields.io/badge/License-GPL-blue)](#license)
[![MLCL  -  Read the Docs](https://img.shields.io/badge/MLCL_-_Doc-347deb?logo=Read+the+Docs)](https://cydaw6.github.io/MyLittleCLibrary)


An example with a small *Movie* structure ([see here](https://github.com/cydaw6/MyLittleCLibrary/blob/main/examples/ex_movies/src/Main.c)):
```c

LinkedList *movies = new_list(LINKED_LIST, movie_m);
Movie *movie = new_movie("Tron", 1982);

/* The director */
movie->director = new_person(new_str("Steven"), new_str("Lisberger"));

/* The cast */
list_append(movie->cast, new_person(new_str("Jeff"), new_str("Bridges")));
list_append(movie->cast, new_person(new_str("Bruce"), new_str("Broxleitner")));
list_append(movie->cast, new_person(new_str("Cindy"), new_str("Morgan")));
list_append(movie->cast, new_person(new_str("Dan"), new_str("Shor")));
list_append(movie->cast, new_person(new_str("David"), new_str("Warner")));

list_prepend(movies, movie);

array_list_merge_sort(movie->s.array_list, person_lt);
list_print(movie->cast);

list_free(&movies)
```