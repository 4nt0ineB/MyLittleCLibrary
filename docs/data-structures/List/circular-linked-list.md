### Circular linked list

```c
int i;
CircularLinkedList *list = new_circular_linked_list(int_m);

for(i = 0; i < 5; i++)
    circular_linked_list_append(list, new_int(i)); 

circular_linked_list_free(&list);    
``` 

### Insertion

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

### Searching
##### Search
```c
Filter *filter = new_filter(1);
filter->conditions[0] = new_condition(int_filter, new_int(5), EQ, int_free);
linked_list_search(list, filter);
```
##### Search all
```c
ArrayList *filtered;
Filter *filter = new_filter(1);
filter->conditions[0] = new_condition(int_filter, new_int(5), EQ, int_free);
filtered = linked_list_search_all(list, filter);
```

### Extraction
##### Exctract
```c
void *data;
Filter *filter = new_filter(1);
filter->conditions[0] = new_condition(int_filter, new_int(5), EQ, int_free);
data = linked_list_extract(list, filter);
```
##### Extract all
```c
ArrayList *filtered;
Filter *filter = new_filter(1);
filter->conditions[0] = new_condition(int_filter, new_int(5), EQ, int_free);
filtered = linked_list_extract_all(list, filter);
```

### Deletion
##### Remove
```c
Filter *filter = new_filter(1);
filter->conditions[0] = new_condition(int_filter, new_int(5), EQ, int_free);
linked_list_remove(list, filter);
```
##### Remove all
```c
Filter *filter = new_filter(1);
filter->conditions[0] = new_condition(int_filter, new_int(5), EQ, int_free);
linked_list_remove_all(list, filter);
```

### Free
##### Clear
```c
linked_list_w(&list, int_free);
```
```c
linked_list_clear(&list);
```
##### Free
```c
linked_list_free_w(&list, int_free);
```
```c
linked_list_quick_sort(&list);
```

### To dot
```c
linked_list_to_dot(list, "linkedlist.dot");
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