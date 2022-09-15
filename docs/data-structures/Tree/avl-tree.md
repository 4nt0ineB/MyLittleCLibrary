### AVL tree

```c  
AVLTree *tree = new_avl_tree(int_m);

avl_tree_add(tree, new_int(6));    
avl_tree_add(tree, new_int(8));  
avl_tree_add(tree, new_int(1));
avl_tree_add(tree, new_int(3));
avl_tree_add(tree, new_int(2));

avl_tree_free(&tree);  
``` 

#### To dot
```c
avl_tree_to_dot(tree, "avltree.dot");
```

=== "Visualization"

    ```dot
    digraph tree {
        node [shape=record , height=.1 ]
        edge [tailclip=false , arrowtail = dot , dir=both];
        n0x55f759a67350 [label="<left> | <value> 6 | <right>"]
        n0x55f759a67350:left:c -> n0x55f759a67490:valeur [color=red];
        n0x55f759a67490 [label="<left> | <value> 2 | <right>"]
        n0x55f759a67490:left:c -> n0x55f759a673f0:valeur [color=red];
        n0x55f759a673f0 [label="<left> | <value> 1 | <right>"]
        n0x55f759a67490:right:c -> n0x55f759a67440:valeur [color=blue];
        n0x55f759a67440 [label="<left> | <value> 3 | <right>"]
        n0x55f759a67350:right:c -> n0x55f759a673a0:valeur [color=blue];
        n0x55f759a673a0 [label="<left> | <value> 8 | <right>"]
    }
    ```

=== "dot"

    ``` dot
    digraph tree {
        node [shape=record , height=.1 ]
        edge [tailclip=false , arrowtail = dot , dir=both];
        n0x55f759a67350 [label="<left> | <value> 6 | <right>"]
        n0x55f759a67350:left:c -> n0x55f759a67490:valeur [color=red];
        n0x55f759a67490 [label="<left> | <value> 2 | <right>"]
        n0x55f759a67490:left:c -> n0x55f759a673f0:valeur [color=red];
        n0x55f759a673f0 [label="<left> | <value> 1 | <right>"]
        n0x55f759a67490:right:c -> n0x55f759a67440:valeur [color=blue];
        n0x55f759a67440 [label="<left> | <value> 3 | <right>"]
        n0x55f759a67350:right:c -> n0x55f759a673a0:valeur [color=blue];
        n0x55f759a673a0 [label="<left> | <value> 8 | <right>"]
    }
    ```