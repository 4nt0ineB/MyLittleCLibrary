### Circular double linked list

<div style="text-align: center;">
```mermaid  
flowchart  LR  
 0 <--> 1
 1 <--> 2
 2 <--> 3
 3 <--> 4
 4 <--> 0
```
</div>

```c
int x;
CircularDoubleLinkedList *list = new_double_linked_list(int_m);

for(i = 0; i < 5; i++)
circuluar_double_linked_list_append(list, new_int(i);

circuluar_double_linked_list_free(&list);

```

#### To dot
```c
circuluar_double_linked_list_to_dot(list, "circulardoublelinkedlist.dot");
```