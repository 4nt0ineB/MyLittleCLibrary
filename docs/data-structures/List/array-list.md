
```c 
int i; 
ArrayList *list = new_array_list(int_m);   

for(i = 0; i < 5; i++)  
    array_list_append(list, new_int(i));
    
array_list_free(&list);  
```   

### Insertion

##### Append
```c
array_list_append(list, new_int(5));
```
##### Prepend
```c
array_list_prepend(list, new_int(5));
```
##### Insert
```c
array_list_insert(list, 2, new_int(5));
```

### Searching
##### Search
```c
Filter *filter = new_filter(1);
filter->conditions[0] = new_condition(int_filter, new_int(5), EQ, int_free);
array_list_search(list, filter);
```
##### Search all
```c
ArrayList *filtered;
Filter *filter = new_filter(1);
filter->conditions[0] = new_condition(int_filter, new_int(5), EQ, int_free);
filtered = array_list_search_all(list, filter);
```

### Extraction
##### Pop
Remove the value of the tail
```c
void *data;
data = array_list_pop(list);
```
##### Pop index
```c
void *data;
data = array_list_pop_i(list, 5);
```
##### Extract
```c
void *data;
Filter *filter = new_filter(1);
filter->conditions[0] = new_condition(int_filter, new_int(5), EQ, int_free);
data = array_list_extract(list, filter);
```
##### Extract all
```c
ArrayList *filtered;
Filter *filter = new_filter(1);
filter->conditions[0] = new_condition(int_filter, new_int(5), EQ, int_free);
filtered = array_list_extract_all(list, filter);
```

### Deletion
##### Remove
```c
Filter *filter = new_filter(1);
filter->conditions[0] = new_condition(int_filter, new_int(5), EQ, int_free);
array_list_remove(list, filter);
```
##### Remove all
```c
Filter *filter = new_filter(1);
filter->conditions[0] = new_condition(int_filter, new_int(5), EQ, int_free);
array_list_remove_all(list, filter);
```

### Sorting

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


### Free
##### Clear
```c
array_list_clear_w(&list, int_free);
```
```c
array_list_clear(&list);
```
##### Free
```c
array_list_free_w(&list, int_free);
```
```c
array_list_quick_sort(&list);
```

### To dot
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
