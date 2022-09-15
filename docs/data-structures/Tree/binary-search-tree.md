
### Binary search tree

```c  
BinarySearchTree *tree = new_binary_search_tree(int_m);

binary_search_tree_add(tree, new_int(6));    
binary_search_tree_add(tree, new_int(8));  
binary_search_tree_add(tree, new_int(1));
binary_search_tree_add(tree, new_int(3));
binary_search_tree_add(tree, new_int(2));

binary_search_tree_free(&tree);  
```  

#### To dot
```c
binary_search_tree_to_dot(tree, "bst.dot");
```

=== "Visualization"
    
    ```dot
    digraph tree {
        node [shape=record , height=.1 ]
        edge [tailclip=false , arrowtail = dot , dir=both];
        n0x55a7757fd350 [label="<left> | <value> 6 | <right>"]
        n0x55a7757fd350:left:c -> n0x55a7757fd3d0:valeur [color=red];
        n0x55a7757fd3d0 [label="<left> | <value> 1 | <right>"]
        n0x55a7757fd3d0:right:c -> n0x55a7757fd410:valeur [color=blue];
        n0x55a7757fd410 [label="<left> | <value> 3 | <right>"]
        n0x55a7757fd410:left:c -> n0x55a7757fd450:valeur [color=red];
        n0x55a7757fd450 [label="<left> | <value> 2 | <right>"]
        n0x55a7757fd350:right:c -> n0x55a7757fd390:valeur [color=blue];
        n0x55a7757fd390 [label="<left> | <value> 8 | <right>"]
    }

    ```

=== "dot"

    ``` dot
    digraph tree {
        node [shape=record , height=.1 ]
        edge [tailclip=false , arrowtail = dot , dir=both];
        n0x55a7757fd350 [label="<left> | <value> 6 | <right>"]
        n0x55a7757fd350:left:c -> n0x55a7757fd3d0:valeur [color=red];
        n0x55a7757fd3d0 [label="<left> | <value> 1 | <right>"]
        n0x55a7757fd3d0:right:c -> n0x55a7757fd410:valeur [color=blue];
        n0x55a7757fd410 [label="<left> | <value> 3 | <right>"]
        n0x55a7757fd410:left:c -> n0x55a7757fd450:valeur [color=red];
        n0x55a7757fd450 [label="<left> | <value> 2 | <right>"]
        n0x55a7757fd350:right:c -> n0x55a7757fd390:valeur [color=blue];
        n0x55a7757fd390 [label="<left> | <value> 8 | <right>"]
    }

    ```