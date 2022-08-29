
### Binary search tree

<div style="text-align: center;">
```mermaid
flowchart TB
    6 --> 1
    1 --- e0( )
	1 --> 3
	6 --> 8
	8 --- e1( )
	8 --- e2( )
```
</div>

```c  
BinarySearchTree *tree = new_binary_search_tree(int_m);

binary_search_tree_add(tree, new_int(6));    
binary_search_tree_add(tree, new_int(8));  
binary_search_tree_add(tree, new_int(1));
binary_search_tree_add(tree, new_int(3));

binary_search_free(&tree);  
```  


### AVL tree

<div style="text-align: center;">
```mermaid
flowchart TB
    6 --> 2
    2 --> 1
	2 --> 3
	6 --> 8
	8 --- e1( )
	8 --- e2( )
```
</div>

```c  
AVLTree *tree = new_avl_tree(int_m);

binary_search_tree_add(tree, new_int(6));    
binary_search_tree_add(tree, new_int(8));  
binary_search_tree_add(tree, new_int(1));
binary_search_tree_add(tree, new_int(3));
binary_search_tree_add(tree, new_int(2));

binary_search_free(&tree);  
``` 

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

### BK Tree

<div style="text-align: center;">
```mermaid
flowchart TB
    Foo -- 1 --> Fool -- 2 --> Fox
    Foo -- 3 --> Bar
```
</div>


```c
BKTree *tree = new_bk_tree();

bk_tree_add(tree, "Foo");
bk_tree_add(tree, "Bar");
bk_tree_add(tree, "Fool");
bk_tree_add(tree, "Fox");

bk_tree_free(&tree);
```

#### Fuzzy search