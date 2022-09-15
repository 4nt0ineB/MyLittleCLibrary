### Circular linked list

```c
int i;
CircularLinkedList *list = new_circular_linked_list(int_m);

for(i = 0; i < 5; i++)
    circular_linked_list_append(list, new_int(i)); 

circular_linked_list_free(&list);    
``` 

#### To dot
```c
circular_linked_list_to_dot(list, "circularlinkedlist.dot");
```



=== "Visualization"

    ```dot
    digraph {
        rankdir="LR";
        node [shape=square , height=.1, rank = same]
        n0x555693692360 [label="0"]
        n0x555693692360 -> n0x5556936923a0
        n0x5556936923a0 [label="1"]
        n0x5556936923a0 -> n0x5556936923e0
        n0x5556936923e0 [label="2"]
        n0x5556936923e0 -> n0x555693692420
        n0x555693692420 [label="3"]
        n0x555693692420 -> n0x555693692460
        n0x555693692460 [label="4"]
        n0x555693692460 -> n0x555693692360
    }
    ```

=== "dot"

    ``` dot
    digraph {
        rankdir="LR";
        node [shape=square , height=.1, rank = same]
        n0x555693692360 [label="0"]
        n0x555693692360 -> n0x5556936923a0
        n0x5556936923a0 [label="1"]
        n0x5556936923a0 -> n0x5556936923e0
        n0x5556936923e0 [label="2"]
        n0x5556936923e0 -> n0x555693692420
        n0x555693692420 [label="3"]
        n0x555693692420 -> n0x555693692460
        n0x555693692460 [label="4"]
        n0x555693692460 -> n0x555693692360
    }
    ```