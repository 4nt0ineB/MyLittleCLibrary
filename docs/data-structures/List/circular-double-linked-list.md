### Circular double linked list

```c
int i;
CircularDoubleLinkedList *list = new_double_linked_list(int_m);

for(i = 0; i < 5; i++)
    circular_double_linked_list_append(list, new_int(i));

circuluar_double_linked_list_free(&list);

```

#### To dot
```c
circuluar_double_linked_list_to_dot(list, "circulardoublelinkedlist.dot");
```


=== "Visualization"

    ```dot
    digraph {
        rankdir="LR";
        node [shape=square , height=.1, rank = same]
        n0x55ff3bbcf360 [label="0"]
        n0x55ff3bbcf360 -> n0x55ff3bbcf3a0
        n0x55ff3bbcf3a0 -> n0x55ff3bbcf360
        n0x55ff3bbcf3a0 [label="1"]
        n0x55ff3bbcf3a0 -> n0x55ff3bbcf3e0
        n0x55ff3bbcf3e0 -> n0x55ff3bbcf3a0
        n0x55ff3bbcf3e0 [label="2"]
        n0x55ff3bbcf3e0 -> n0x55ff3bbcf420
        n0x55ff3bbcf420 -> n0x55ff3bbcf3e0
        n0x55ff3bbcf420 [label="3"]
        n0x55ff3bbcf420 -> n0x55ff3bbcf460
        n0x55ff3bbcf460 -> n0x55ff3bbcf420
        n0x55ff3bbcf460 [label="4"]
        n0x55ff3bbcf460 -> n0x55ff3bbcf360
        n0x55ff3bbcf360 -> n0x55ff3bbcf460
    }
    ```
=== "dot"

    ``` dot
    digraph {
        rankdir="LR";
        node [shape=square , height=.1, rank = same]
        n0x55ff3bbcf360 [label="0"]
        n0x55ff3bbcf360 -> n0x55ff3bbcf3a0
        n0x55ff3bbcf3a0 -> n0x55ff3bbcf360
        n0x55ff3bbcf3a0 [label="1"]
        n0x55ff3bbcf3a0 -> n0x55ff3bbcf3e0
        n0x55ff3bbcf3e0 -> n0x55ff3bbcf3a0
        n0x55ff3bbcf3e0 [label="2"]
        n0x55ff3bbcf3e0 -> n0x55ff3bbcf420
        n0x55ff3bbcf420 -> n0x55ff3bbcf3e0
        n0x55ff3bbcf420 [label="3"]
        n0x55ff3bbcf420 -> n0x55ff3bbcf460
        n0x55ff3bbcf460 -> n0x55ff3bbcf420
        n0x55ff3bbcf460 [label="4"]
        n0x55ff3bbcf460 -> n0x55ff3bbcf360
        n0x55ff3bbcf360 -> n0x55ff3bbcf460
    }
    ```