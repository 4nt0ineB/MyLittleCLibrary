# My Little C Library
A static ANSI C library gathering things I learned in college.

I started to make this lib because, during a C project I was bored to reimplement same data structures over again
for different objects. I was convinced there must exist a way to juste simply write generic data structures.

But while working on it I realized few things:
- Genericity need abstraction. And the more you want to allow users to take distance from the computer implementation 
  the more abstraction you'll need and the bigger the lib will be - leading to much more work.
- More abstraction mean lower performance

But hey I knew it. Tough it's quite interesting to experiment those limitation with a practical example.

Two quotes from computer scientists I read online perfectly illustrate the idea:

```
Any problem in computer science can be solved by adding another layer of abstraction. 
```

David Wheeler

```
Any performance problem in computer science can be solved by removing a layer of abstraction.
```
Dave Clark

So, I think this lib could be ok to use for small projects or to visualize some data structures while learning C in college,
but not when there are strict needs in time performance or memory limitation.

### Roadmap/todo list
[Dashboard](https://github.com/users/cydaw6/projects/1)

Antoine Bastos 2022 - Apache-2.0 licensed