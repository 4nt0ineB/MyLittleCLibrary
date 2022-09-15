### BK Tree

```c
BKTree *tree = new_bk_tree();

bk_tree_add(tree, "Foo");
bk_tree_add(tree, "Bar");
bk_tree_add(tree, "Fool");
bk_tree_add(tree, "Fox");

bk_tree_free(&tree);
```

#### Fuzzy search

#### To dot
```c
bk_tree_to_dot(list, "bktree.dot");
```

=== "Visualization"

    ```dot
    digraph tree {
        n0x55a93b7d2350 [label="Foo"]
        n0x55a93b7d2350 -> n0x55a93b7d23a0 [color="#2257ab", label=" 3 "]
        n0x55a93b7d23a0 [label="Bar"]
        n0x55a93b7d23d0 [label="Fool"]
        n0x55a93b7d2350 -> n0x55a93b7d23d0 [color="#2257ab", label=" 1 "]
        n0x55a93b7d23d0 [label="Fool"]
        n0x55a93b7d23d0 -> n0x55a93b7d2480 [color="#2257ab", label=" 2 "]
        n0x55a93b7d2480 [label="Fox"]
    }
    ```

=== "dot"

    ``` dot
    digraph tree {
        n0x55a93b7d2350 [label="Foo"]
        n0x55a93b7d2350 -> n0x55a93b7d23a0 [color="#2257ab", label=" 3 "]
        n0x55a93b7d23a0 [label="Bar"]
        n0x55a93b7d23d0 [label="Fool"]
        n0x55a93b7d2350 -> n0x55a93b7d23d0 [color="#2257ab", label=" 1 "]
        n0x55a93b7d23d0 [label="Fool"]
        n0x55a93b7d23d0 -> n0x55a93b7d2480 [color="#2257ab", label=" 2 "]
        n0x55a93b7d2480 [label="Fox"]
    }
    ```