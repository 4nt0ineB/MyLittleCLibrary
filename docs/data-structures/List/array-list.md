
### Array list

<div style="text-align: center;">
[ 0 ][ 1 ][ 2 ][ 3 ][ 4 ]
</div>

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