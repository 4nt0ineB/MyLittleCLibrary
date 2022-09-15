### Double linked list

```c 
int i;
DoubleLinkedList *list = new_double_linked_list(int_m);  

for(i = 0; i < 5; i++)
    double_linked_list_append(list, new_int(i)); 
    
double_linked_list_free(&list);
```

#### To dot
```c
double_linked_list_to_dot(list, "doublelinkedlist.dot");
```

=== "Visualization"

    ```dot
    digraph {
        rankdir="LR";
        splines=ortho;
        node [shape=square , height=.1, rank = same]
        n0x5634bd90c360 [label="0"]
        n0x5634bd90c360 -> n0x5634bd90c3a0
        n0x5634bd90c3a0 -> n0x5634bd90c360
        n0x5634bd90c3a0 [label="1"]
        n0x5634bd90c3a0 -> n0x5634bd90c3e0
        n0x5634bd90c3e0 -> n0x5634bd90c3a0
        n0x5634bd90c3e0 [label="2"]
        n0x5634bd90c3e0 -> n0x5634bd90c420
        n0x5634bd90c420 -> n0x5634bd90c3e0
        n0x5634bd90c420 [label="3"]
        n0x5634bd90c420 -> n0x5634bd90c460
        n0x5634bd90c460 -> n0x5634bd90c420
        n0x5634bd90c460 [label="4"]
    }
    ```

=== "dot"

    ``` dot
    digraph {
        rankdir="LR";
        splines=ortho;
        node [shape=square , height=.1, rank = same]
        n0x5634bd90c360 [label="0"]
        n0x5634bd90c360 -> n0x5634bd90c3a0
        n0x5634bd90c3a0 -> n0x5634bd90c360
        n0x5634bd90c3a0 [label="1"]
        n0x5634bd90c3a0 -> n0x5634bd90c3e0
        n0x5634bd90c3e0 -> n0x5634bd90c3a0
        n0x5634bd90c3e0 [label="2"]
        n0x5634bd90c3e0 -> n0x5634bd90c420
        n0x5634bd90c420 -> n0x5634bd90c3e0
        n0x5634bd90c420 [label="3"]
        n0x5634bd90c420 -> n0x5634bd90c460
        n0x5634bd90c460 -> n0x5634bd90c420
        n0x5634bd90c460 [label="4"]
    }
    ```