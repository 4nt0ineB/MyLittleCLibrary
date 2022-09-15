
### Linked list

```c 
LinkedList *list = new_linked_list(float_m);

linked_list_append(list, new_float(1.2f));  
linked_list_append(list, new_float(2.5f));  
linked_list_append(list, new_float(3.8f));

linked_list_free(&list); 
```


#### Add

##### Append
```c
linked_list_append(l, new_float(2.5f));
linked_list_append(l, new_float(1.2f));
/* [2.5, 1.2] */
```

##### Prepend
```c
linked_list_prepend(l, new_float(2.5f));
linked_list_prepend(l, new_float(1.2f));
/* [1.2, 2.5] */
```

#### Sorting

##### Merge sort
```c
linked_list_merge_sort(list, int_lt);
```

#### To dot
```c
linked_list_to_dot(list, "linkedlist.dot");
```

=== "Visualization"

    ```dot
    digraph {
        rankdir="LR";
        splines=ortho;
        node [shape=square , height=.1, rank = same]
          n0x556fa1c6a360 [label="1.20" color="#000000"]
         n0x556fa1c6a360 -> n0x556fa1c6a3a0
          n0x556fa1c6a3a0 [label="2.50" color="#000000"]
         n0x556fa1c6a3a0 -> n0x556fa1c6a3e0
          n0x556fa1c6a3e0 [label="3.80" color="#000000"]
    }
    ```

=== "dot"

    ``` dot
    digraph {
        rankdir="LR";
        splines=ortho;
        node [shape=square , height=.1, rank = same]
        n0x556fa1c6a360 [label="1.20" color="#000000"]
        n0x556fa1c6a360 -> n0x556fa1c6a3a0
        n0x556fa1c6a3a0 [label="2.50" color="#000000"]
        n0x556fa1c6a3a0 -> n0x556fa1c6a3e0
        n0x556fa1c6a3e0 [label="3.80" color="#000000"]
    }
    ```