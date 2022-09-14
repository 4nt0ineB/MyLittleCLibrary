### Ternary Search Tree (Lexical Tree)

```c
TernarySearchTree *tree = new_ternary_search_tree();

ternary_search_tree_add(tree, "Foo");
ternary_search_tree_add(tree, "Bar");
ternary_search_tree_add(tree, "Fool");

ternary_search_tree_free(&tree);
```

#### To dot
```c
ternary_search_tree_to_dot(list, "tst.dot");
```

=== "Visualisation"

    ```dot
        digraph tree {
        graph [ splines=true]
        node [shape=circle,height=.1]
        
        
        n0x55f181e2ed60 [label="F"]
        n0x55f181e2ed60:w -> n0x55f181e2ebc0:c [color="#ab2222"]
        n0x55f181e2ebc0 [label="B"]
        n0x55f181e2ebc0:s -> n0x55f181e2ee30:c  
        n0x55f181e2ee30 [label="a"]
        n0x55f181e2ee30:s -> n0x55f181e2ee60:c  
        n0x55f181e2ee60 [label="r"]
        n0x55f181e2ee60:s -> n0x55f181e2ee90:c  
        n0x55f181e2ee90 [label="0"]
        n0x55f181e2ed60:s -> n0x55f181e2e750:c  
        n0x55f181e2e750 [label="o"]
        n0x55f181e2e750:s -> n0x55f181e2ed90:c  
        n0x55f181e2ed90 [label="o"]
        n0x55f181e2ed90:s -> n0x55f181e2ed30:c  
        n0x55f181e2ed30 [label="0"]
        n0x55f181e2ed30:e -> n0x55f181e2eec0:c [color="#2257ab"]
        n0x55f181e2eec0 [label="l"]
        n0x55f181e2eec0:s -> n0x55f181e2eef0:c  
        n0x55f181e2eef0 [label="0"]
        
        }
    ```

=== "dot"

    ```
        digraph tree {
        graph [ splines=true]
        node [shape=circle,height=.1]
        
        
        n0x55f181e2ed60 [label="F"]
        n0x55f181e2ed60:w -> n0x55f181e2ebc0:c [color="#ab2222"]
        n0x55f181e2ebc0 [label="B"]
        n0x55f181e2ebc0:s -> n0x55f181e2ee30:c  
        n0x55f181e2ee30 [label="a"]
        n0x55f181e2ee30:s -> n0x55f181e2ee60:c  
        n0x55f181e2ee60 [label="r"]
        n0x55f181e2ee60:s -> n0x55f181e2ee90:c  
        n0x55f181e2ee90 [label="0"]
        n0x55f181e2ed60:s -> n0x55f181e2e750:c  
        n0x55f181e2e750 [label="o"]
        n0x55f181e2e750:s -> n0x55f181e2ed90:c  
        n0x55f181e2ed90 [label="o"]
        n0x55f181e2ed90:s -> n0x55f181e2ed30:c  
        n0x55f181e2ed30 [label="0"]
        n0x55f181e2ed30:e -> n0x55f181e2eec0:c [color="#2257ab"]
        n0x55f181e2eec0 [label="l"]
        n0x55f181e2eec0:s -> n0x55f181e2eef0:c  
        n0x55f181e2eef0 [label="0"]
        
        }
    ```