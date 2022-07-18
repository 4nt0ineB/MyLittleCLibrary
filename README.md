# MyLittleCLibrary
A C library gathering things I learned in college. It's a C toolbox to implement things faster for my homework.

[![workflow](https://github.com/cydaw6/MyLittleCLibrary/actions/workflows/c-cpp.yml/badge.svg)](https://github.com/cydaw6/MyLittleCLibrary/actions/workflows/c-cpp.yml)
[![License](https://img.shields.io/badge/License-MIT-blue)](#license)
[![MLCL  -  Read the Docs](https://img.shields.io/badge/MLCL_-_Read_the_Docs-347deb?logo=Read+the+Docs)](https://cydaw6.github.io/MyLittleCLibrary/html/index.html)



## Motivation

The idea of this library is to have shorthand use of certain structures.
It is a useful tool that allows me not to reinvent the wheel every time. 
A custom structure fitted to your needs will be more efficient because unwanted 
and heavy abstractions would be reduced, besides you'll know how it works. 
Word to the wise: it probably carries bugs and flaws.

The way I have coded things don't allow to have different types in a list, for example. 
~~You can have a list of int, a list of char, a list of whatever type you make, 
but you can't have a list of int and float etc., like Python. I could have done that, 
but I didn't think about it at the beginning.-
However, I think it keeps things clean, more efficient, and the C spirit.~~
Edit: In fact, you can, by creating an abstract type for all types...

The lib was made with those flags:
```bash
-ansi -pedantic -Wall -O2
```

### Credits
doxygen-awesome-css - github.com/jothepro
