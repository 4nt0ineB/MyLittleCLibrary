# MyLittleCLibrary
A C library gathering things I learnt in college. It's a C toolbox to faster implement things for my homework.

This library is made with the idea of having shorthand use of certain structures,
but it is not meant to be a performance model. 
It is for me a comfort for not having to reinvent the wheel every time. 
A custom structure fitting to your need will ever be more efficient as unwanted 
and heavy abstraction will be reduced, besides you'll know how it works. 
Word to the wise: probably carry some bad conceptions or bugs ; use at your own risk.

The way I have coded things don't allow to have different types in a list, for example. 
You can have a list of int, a list of char, a list of what ever type you made, 
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
