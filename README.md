# MyLittleCLibrary
A C library gathering things I learned in college. It's a C toolbox to implement things faster for my homework.

![workflow](https://github.com/cydaw6/MyLittleCLibrary/actions/workflows/c-cpp.yml/badge.svg)

## Motivation

The idea of this library is to have shorthand use of certain structures,
but it is not meant to be a performance model. 
It is a useful tool that allows me not to reinvent the wheel every time. 
A custom structure fitted to your needs will be more efficient because unwanted 
and heavy abstractions would be reduced, besides you'll know how it works. 
Word to the wise: it probably carries bugs and flaws.

The way I have coded things don't allow to have different types in a list, for example. 
You can have a list of int, a list of char, a list of whatever type you make, 
but you can't have a list of int and float etc., like Python. I could have done that, 
but I didn't think about it at the beginning. 
However, I think it keeps things clean, more efficient, and the C spirit.

The lib was made with those flags:
```bash
-ansi -pedantic -Wall -O2
```

## Credits
doxygen-awesome-css - github.com/jothepro

To me:
https://franckh.developpez.com/tutoriels/outils/doxygen/
