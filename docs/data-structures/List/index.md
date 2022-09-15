### List
The list interface provides basic methods for the different list implementation

A circular linked list of strings:

```c  
List *list = new_list(LINKED_LIST, str_m);  
  
list_append(list, new_str("hell"));  
list_append(list, new_str"shell"));  
list_append(list, new_str"Foo"));  
list_append(list, new_str"bar"));  
list_append(list, new_str"Bubble"));  
    
l_free(&list);  
```  

#### Limitation
Some of the list implementation have specific methods, other don't. So you will have to understand how structs are shaped. For example if you want to benefit of the sorting methods of the *ArrayList* through the *List* interface, you would do:

```c  
list = new_list(ARRAY_LIST, int_m);  
...  
array_list_merge_sort(list->s.array_list);  
```  
You will notice that here we access the *ArrayList* implementation through the **s** (for "structure") field, depending on the type of implementation we set to create the *List*.

#### Methods
[Header file](https://github.com/cydaw6/MyLittleCLibrary/blob/main/include/Lists/MLCL_List.h)