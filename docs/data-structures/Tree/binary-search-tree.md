
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

binary_search_tree_free(&tree);  
```  

#### To dot
```c
binary_search_tree_to_dot(list, "bst.dot");
```