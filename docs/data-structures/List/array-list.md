
### Array list

```c 
int i; 
ArrayList *list = new_array_list(int_m);   

for(i = 0; i < 5; i++)  
    array_list_append(list, new_int(i));
    
array_list_free(&list);  
```   

#### Sorting

##### Bubble sort
```c
array_list_bubble_sort(list, int_lt);
```

##### Insertion sort
```c
array_list_insertion_sort(list, int_lt);
```

##### Selection sort
```c
array_list_selection_sort(list, int_lt);
```

##### Merge sort
```c
array_list_merge_sort(list, int_lt);
```

##### Quick Sort
```c
array_list_quick_sort(list, int_lt);
```

#### To dot
```c
array_list_to_dot(list, "arraylist.dot");
```

=== "Visualization"

    ```dot
    digraph {
    
        node [shape=record, fontcolor=black, fontsize=14, width=4.75, fixedsize=true];
        values [label="0 | 1 | 2 | 3 | 4"];
    }
    ```

=== "dot"

    ``` dot
    digraph {
    
        node [shape=record, fontcolor=black, fontsize=14, width=4.75, fixedsize=true];
        values [label="0 | 1 | 2 | 3 | 4"];
    }
    ```
