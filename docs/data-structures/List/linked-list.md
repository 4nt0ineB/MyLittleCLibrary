

```c 
CircularLinkedList *list = new_circular_linked_list(float_m);
circular_linked_list_append(list, new_float(1.2f));  
circular_linked_list_append(list, new_float(2.5f));  
circular_linked_list_append(list, new_float(3.8f));
circular_linked_list_free(&list); 
```


### Insertion

##### Append
```c
circular_linked_list_append(l, new_float(2.5f));
circular_linked_list_append(l, new_float(1.2f));
/* [2.5, 1.2] */
```

##### Prepend
```c
circular_linked_list_prepend(l, new_float(2.5f));
circular_linked_list_prepend(l, new_float(1.2f));
/* [1.2, 2.5] */
```


### Searching
##### Search
```c
Filter *filter = new_filter(1);
filter->conditions[0] = new_condition(int_filter, new_int(5), EQ, int_free);
circular_linked_list_search(list, filter);
```
##### Search all
```c
ArrayList *filtered;
Filter *filter = new_filter(1);
filter->conditions[0] = new_condition(int_filter, new_int(5), EQ, int_free);
filtered = circular_linked_list_search_all(list, filter);
```

### Extraction

##### Pop
```c
circular_linked_list_pop(l);
```
##### Shift
```c
circular_linked_list_shift(l);
```

##### Exctract
```c
void *data;
Filter *filter = new_filter(1);
filter->conditions[0] = new_condition(int_filter, new_int(5), EQ, int_free);
data = circular_linked_list_extract(list, filter);
```
##### Extract all
```c
ArrayList *filtered;
Filter *filter = new_filter(1);
filter->conditions[0] = new_condition(int_filter, new_int(5), EQ, int_free);
filtered = circular_linked_list_extract_all(list, filter);
```

### Deletion
##### Remove
```c
Filter *filter = new_filter(1);
filter->conditions[0] = new_condition(int_filter, new_int(5), EQ, int_free);
circular_linked_list_remove(list, filter);
```
##### Remove all
```c
Filter *filter = new_filter(1);
filter->conditions[0] = new_condition(int_filter, new_int(5), EQ, int_free);
circular_linked_list_remove_all(list, filter);
```

### Free
##### Clear
```c
circular_linked_list_w(&list, int_free);
```
```c
circular_linked_list_clear(&list);
```
##### Free
```c
circular_linked_list_free_w(&list, int_free);
```
```c
circular_linked_list_quick_sort(&list);
```

### To dot
```c
circular_linked_list_to_dot(list, "linkedlist.dot");
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