
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

## Purpose 
I started to make this lib because, during a C project I was bored to reimplement same data structures over again
for different objects. I was convinced there must exist a way to juste simply write generic data structures.

But while working on it I realized few things:
- Genericity need abstraction. And the more you want a user to get rid of types manipulation
  the more abstraction you'll need and the bigger the lib will be - and thus much more work.
- More abstraction mean lower performance

But hey I knew it. Tough it's quite interesting to experiment these limitation with a practical example.

Two quotes from computer scientists I read online illustrate the idea.

“Any problem in computer science can be solved by adding another layer of abstraction.” - David Wheeler

“Any performance problem in computer science can be solved by removing a layer of abstraction.” - Dave Clark

So, I think this lib could be ok to use for small projects or to visualize some data structures, while learning C
but not much more.

### Roadmap/todo list
[Dashboard](https://github.com/users/cydaw6/projects/1)



Antoine Bastos 2022 - Apache-2.0 licensed