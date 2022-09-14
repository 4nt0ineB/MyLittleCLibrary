### Ternary Search Tree (Lexical Tree)

<div style="text-align: center;">
```mermaid
flowchart TB
    F --> B --- a --- r --- f1(\0)
    F --- o2(o) --- o1(o) --- f(\0)
    f(\0) --- nul1( )
    f(\0) --> l --- f2(\0)
    F --- nul( )
```
</div>


```c
TernarySearchTree *tree = new_ternary_search_tree();

ternary_search_tree_add(tree, "Foo");
ternary_search_tree_add(tree, "Bar");
ternary_search_tree_add(tree, "Fool");

ternary_search_tree_free(&tree);
```